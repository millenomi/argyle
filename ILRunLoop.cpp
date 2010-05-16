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
#include <unistd.h>
#include <sys/select.h>
#include <math.h>
#include <iostream>

static char ILRunLoopUnusedValue = 0;
void* const ILRunLoopSignalReadyMessage = &ILRunLoopUnusedValue;

ILTargetForMethod(ILRunLoopSignalTarget, ILRunLoop, signalByDeliveringMessage);

ILTimeInterval ILGetAbsoluteTime() {
	struct timeval tv;
	gettimeofday(&tv, NULL);
	
	ILTimeInterval i = (double) tv.tv_sec + (double) tv.tv_usec / 1000000;
	return i;
}

void ILRunLoop::addSource(ILSource* s) {
	_sources->addObject((ILObject*) s);
	s->setRunLoop(this);
}

void ILRunLoop::removeSource(ILSource* s) {
	s->setRunLoop(NULL);
	_sources->removeObject((ILObject*) s);
}


void ILRunLoop::spinForUpTo(ILTimeInterval seconds) {	
	ILTimeInterval start = ILGetAbsoluteTime();

	struct timeval tv;
	tv.tv_sec = (unsigned int) floor(seconds);
	tv.tv_usec = (unsigned int) ((seconds - floor(seconds)) * 1000000.0);
	
	do {
		if (_sources->count() == 0)
			return;
		
		fd_set fds;
		FD_ZERO(&fds);
		FD_SET(_pipe[0], &fds);
		
		select(_pipe[0] + 1 /* WHYYYYY */, &fds, NULL, &fds, &tv);
		// we don't check for errors --
		// if error, then something went wrong with the pipe, which it shouldn't.
		// if timeout, it's fine -- we spin once, then quit when the while sees our time is up.
		// if the pipe has something to read, well, ok.
		
		this->spin();
	} while (ILGetAbsoluteTime() - start < seconds);
}

void ILRunLoop::signalReady() {
	const char k = '>';
	write(_pipe[1], &k, sizeof(char));
}

void ILRunLoop::signalByDeliveringMessage(ILMessage* m) {
	this->signalReady();
}

void ILRunLoop::spin() {
	ILSetIterator* eachSource = _sources->copy()->iterate();
	ILSource* s;
	
	while ((s = (ILSource*) eachSource->next())) {
		ILReleasePool pool;
		if (_sources->containsObject((ILObject*) s))
			s->performPeriodicWork();
	}
}

ILRunLoop::ILRunLoop() : ILTarget() {
	_sources = ILRetain(new ILSet());
	_messageHub = NULL;
	_target = NULL;
	
	if (pipe(_pipe) != 0) {
		std::cerr << "Error: Cannot allocate pipes for signaling.";
		abort();
	}
	
	this->currentMessageHub()->addTargetForMessagesOfKind(new ILRunLoopSignalTarget(this), ILRunLoopSignalReadyMessage, NULL);
}

ILRunLoop::~ILRunLoop() {
	ILRelease(_sources);
	ILRelease(_messageHub);
	ILRelease((ILObject*) _target);
	
	if (_pipe[0] != 0)
		close(_pipe[0]);
	if (_pipe[1] != 0)
		close(_pipe[1]);
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
