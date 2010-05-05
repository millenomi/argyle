/*
 *  ILReleasePool.cpp
 *  Argyle
 *
 *  Created by ∞ on 25/04/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "ILReleasePool.h"
#include <stdlib.h>
#include <pthread.h>

pthread_key_t ILReleasePoolThreadLocalKey;
void ILReleasePoolInitThreadLocalKey() __attribute__((constructor));

void ILReleasePoolInitThreadLocalKey() {
	if (pthread_key_create(&ILReleasePoolThreadLocalKey, NULL) != 0)
		abort();
}

struct ILReleasePoolLink {
	ILObject* object;
	ILReleasePoolLink* nextLink;
};

// static ILReleasePool* topmostPool = NULL;
ILReleasePool* ILReleasePoolCurrent() {
	return (ILReleasePool*) pthread_getspecific(ILReleasePoolThreadLocalKey);
}

static void ILReleasePoolSetCurrent(ILReleasePool* pool) {
	pthread_setspecific(ILReleasePoolThreadLocalKey, (const void*) pool);
}

ILReleasePool::ILReleasePool() {
	previousPool = ILReleasePoolCurrent();
	ILReleasePoolSetCurrent(this);
	
	lastLink = NULL;
	_delegate = NULL;
}

void ILReleasePool::addObject(ILObject* o) {
	ILReleasePoolLink* link = new ILReleasePoolLink();
	link->object = o;
	link->nextLink = lastLink;
	
	lastLink = link;
}

ILReleasePool::~ILReleasePool() {
	if (_delegate)
		_delegate->willDestroyPool(this);
	
	ILReleasePoolLink* link = lastLink;
	
	while (link) {
		ILReleasePoolLink* l = link;
		
		bool willDestroy = false;
		if (_delegate) {
			_delegate->willReleaseObject(this, l->object);
			willDestroy = (l->object->retainCount() == 1);
		}
		
		ILRelease(l->object);
		
		if (_delegate && willDestroy)
			_delegate->didDestroyObject(this, l->object);
		
		link = l->nextLink;
		
		delete l;
	}
	
	ILReleasePoolSetCurrent(previousPool);
}

ILObject* ILReleaseLater(ILObject* o) {
	if (o != NULL)
		ILReleasePoolCurrent()->addObject(o);
	
	return o;
}

ILReleasePoolDelegate* ILReleasePool::delegate() {
	return _delegate;
}

void ILReleasePool::setDelegate(ILReleasePoolDelegate* delegate) {
	_delegate = delegate;
}
