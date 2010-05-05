/*
 *  ILObject.cpp
 *  Argyle
 *
 *  Created by ∞ on 25/04/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "ILObject.h"
#include <iostream>

#include <pthread.h>

#include "ILReleasePool.h"

static pthread_mutex_t ILRetainReleaseMutex;
void ILRetainReleaseMutexInit() __attribute__((constructor));

void ILRetainReleaseMutexInit() {
	pthread_mutexattr_t attrs;
	pthread_mutexattr_init(&attrs);

	pthread_mutexattr_settype(&attrs, PTHREAD_MUTEX_RECURSIVE);
	
	int result = pthread_mutex_init(&ILRetainReleaseMutex, &attrs);
	if (result != 0)
		abort();
}

ILObject::ILObject() {
	_retainCount = 1;
	ILReleaseLater(this);
}
ILObject::~ILObject() {}

void ILObject::retain() {
	pthread_mutex_lock(&ILRetainReleaseMutex);
	_retainCount++;
	pthread_mutex_unlock(&ILRetainReleaseMutex);
}

bool ILObject::release() {
	pthread_mutex_lock(&ILRetainReleaseMutex);

	if (_retainCount > 1) {
		_retainCount--;
		return false;
	} else if (_retainCount == 1) {
		_retainCount = 0;
		return true;
	} else {
		std::cerr << "Overreleased object!\n";
		abort();
	}

	pthread_mutex_unlock(&ILRetainReleaseMutex);
}

uint64_t ILObject::retainCount() {
	pthread_mutex_lock(&ILRetainReleaseMutex);
	return _retainCount;
	pthread_mutex_unlock(&ILRetainReleaseMutex);
}


void* const ILObjectClassIdentity = (void*) "ILObject";

void* ILObject::classIdentity() {
	return ILObjectClassIdentity;
}


bool ILObject::equals(ILObject* o) {
	return this == o;
}

uint64_t ILObject::hash() {
	return (uint64_t) this;
}


ILObject* ILRetain(ILObject* o) {
	o->retain();
	return o;
}

void ILRelease(ILObject* o) {
	if (!o)
		return;
	
	if (o->release())
		delete o;
}

bool ILObject::canCopy() {
	return false;
}

bool ILCopiable::canCopy() {
	return true;
}
