/*
 *  ILRunLoop.cpp
 *  Argyle
 *
 *  Created by ∞ on 11/05/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "ILRunLoop.h"

void ILRunLoop::addSource(ILSource* s) {
	
}

void ILRunLoop::spin() {
	ILListIterator* eachSource = _sources->copy()->iterate();
	ILSource* s;
	
	while ((s = (ILSource*) eachSource->next())) {
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
	ILRelease(_target);
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

