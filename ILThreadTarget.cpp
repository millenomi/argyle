/*
 *  ILThreadTarget.cpp
 *  Argyle
 *
 *  Created by ∞ on 11/05/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "ILThreadTarget.h"
#include "ILRunLoop.h"

ILThreadTarget::ILThreadTarget(ILTarget* t) {
	_deliveryTarget = ILRetain(t);
	_messages = (ILList*) ILRetain(new ILList());
	
	pthread_mutexattr_t attrs;
	pthread_mutexattr_init(&attrs);
	
	pthread_mutexattr_settype(&attrs, PTHREAD_MUTEX_RECURSIVE);
	
	int result = pthread_mutex_init(&_mutex, &attrs);
	if (result != 0)
		abort();
}

ILThreadTarget::~ILThreadTarget() {
	pthread_mutex_destroy(&_mutex);
	ILRelease((ILObject*) _deliveryTarget);
	ILRelease(_messages);
}

void ILThreadTarget::deliverMessage(ILMessage* m) {
	pthread_mutex_lock(&_mutex);
	_messages->addObject(m);
	pthread_mutex_unlock(&_mutex);
	
	if (this->runLoop())
		this->runLoop()->signalReady();
}

void ILThreadTarget::deliverPendingMessagesOnThisThread() {
	pthread_mutex_lock(&_mutex);

	{
		ILReleasePool pool;
		ILListIterator* i = _messages->iterate();
		
		ILMessage* m;
		while ((m = (ILMessage*) i->next())) {
			_deliveryTarget->deliverMessage(m);
		}
		
		while (_messages->count() > 0)
			_messages->removeObjectAtIndex(0);
	}
	
	pthread_mutex_unlock(&_mutex);
}

void ILThreadTarget::performPeriodicWork() {
	this->deliverPendingMessagesOnThisThread();
}
