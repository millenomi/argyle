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

class ILThreadTargetSource : public ILSource {
public:
	ILThreadTargetSource(ILThreadTarget* t) { _threadTarget = t; }
	
	ILThreadTarget* _threadTarget;
	virtual void spin();
};

ILThreadTarget::ILThreadTarget(ILTarget* t) {
	_deliveryTarget = ILRetain(t);
	_messages = (ILList*) ILRetain(new ILList());
	
	pthread_mutexattr_t attrs;
	pthread_mutexattr_init(&attrs);
	
	pthread_mutexattr_settype(&attrs, PTHREAD_MUTEX_RECURSIVE);
	
	int result = pthread_mutex_init(&_mutex, &attrs);
	if (result != 0)
		abort();
	
	_source = new ILThreadTargetSource(this);
}

ILSource* ILThreadTarget::source() {
	return _source;
}

ILThreadTarget::~ILThreadTarget() {
	pthread_mutex_destroy(&_mutex);
	ILRelease((ILObject*) _deliveryTarget);
	ILRelease(_messages);
	_source->_threadTarget = NULL;
	ILRelease(_source);
}

void ILThreadTarget::deliverMessage(ILMessage* m) {
	pthread_mutex_lock(&_mutex);
	_messages->addObject(m);
	pthread_mutex_unlock(&_mutex);
	
	if (_source->runLoop())
		_source->runLoop()->signalReady();
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

void ILThreadTargetSource::spin() {
	if (this->_threadTarget)
		this->_threadTarget->deliverPendingMessagesOnThisThread();
}
