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

#include "ILReleasePool.h"

ILObject::ILObject() {
	_retainCount = 1;
	ILReleaseLater(this);
}
ILObject::~ILObject() {}

void ILObject::retain() {
	_retainCount++;
}

bool ILObject::release() {
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
}

uint64_t ILObject::retainCount() {
	return _retainCount;
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
