/*
 *  ILObject.cpp
 *  Argyle
 *
 *  Created by ∞ on 25/04/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "ILObject.h"
#include <stdio.h>

#include <pthread.h>
#include <stdlib.h>

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
	bool result;
	
	pthread_mutex_lock(&ILRetainReleaseMutex);

	if (_retainCount > 1) {
		_retainCount--;
		result = false;
	} else if (_retainCount == 1) {
		_retainCount = 0;
		result = true;
	} else {
		fprintf(stderr, "Overreleased object!\n");
		abort();
	}

	pthread_mutex_unlock(&ILRetainReleaseMutex);
	return result;
}

uint64_t ILObject::retainCount() {
	uint64_t rc;
	pthread_mutex_lock(&ILRetainReleaseMutex);
	rc = _retainCount;
	pthread_mutex_unlock(&ILRetainReleaseMutex);
	
	return rc;
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


ILObject* ILPerformRetain(ILObject* o) {
	if (!o)
		return NULL;
	
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
