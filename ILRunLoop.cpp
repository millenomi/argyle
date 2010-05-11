/*
 *  ILRunLoop.cpp
 *  Argyle
 *
 *  Created by ∞ on 11/05/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "ILRunLoop.h"
#include <sys/time.h>
#include <pthread.h>

ILTimeInterval ILGetAbsoluteTime() {
	struct timeval tv;
	gettimeofday(&tv, NULL);
	
	ILTimeInterval i = (double) tv.tv_sec + (double) tv.tv_usec / 1000000;
	return i;
}

void ILRunLoop::addSource(ILSource* s) {
	_sources->addObject((ILObject*) s);
}

void ILRunLoop::removeSource(ILSource* s) {
	_sources->removeObject((ILObject*) s);
}


void ILRunLoop::spinForUpTo(ILTimeInterval seconds) {	
	ILTimeInterval start = ILGetAbsoluteTime();
	
	do {
		if (_sources->count() == 0)
			return;
		
		this->spin();
	} while (ILGetAbsoluteTime() - start < seconds);
}

void ILRunLoop::spin() {
	ILListIterator* eachSource = _sources->copy()->iterate();
	ILSource* s;
	
	while ((s = (ILSource*) eachSource->next())) {
		if (_sources->containsObject((ILObject*) s))
			s->performPeriodicWork();
	}
}

ILRunLoop::ILRunLoop() : ILTarget() {
	_sources = ILRetain(new ILList());
	_messageHub = NULL;
	_target = NULL;
}

ILRunLoop::~ILRunLoop() {
	ILRelease(_sources);
	ILRelease(_messageHub);
	ILRelease((ILObject*) _target);
}

ILMessageHub* ILRunLoop::currentMessageHub() {
	if (!_messageHub)
		_messageHub = ILRetain(new ILMessageHub());
	
	return _messageHub;
}

ILTarget* ILRunLoop::currentThreadTarget() {
	if (!_target)
		_target = ILRetain(new ILThreadTarget(this->currentMessageHub()));
	
	return _target;
}

// ONLY thread-safe method of this class.
void ILRunLoop::deliverMessage(ILMessage* m) {
	if (_target)
		_target->deliverMessage(m);
}

// ~~~

static pthread_key_t ILRunLoopCurrentKey;

__attribute__((constructor)) void ILRunLoopInitializeKey() {
	pthread_key_create(&ILRunLoopCurrentKey, (void (*)(void*)) &ILRelease);
}

ILRunLoop* ILRunLoop::current() {	
	ILRunLoop* r = (ILRunLoop*) pthread_getspecific(ILRunLoopCurrentKey);
	if (!r) {
		r = ILRetain(new ILRunLoop());
		pthread_setspecific(ILRunLoopCurrentKey, (const void*) r);
	}
	
	return r;
}
