/*
 *  ILObject.cpp
 *  Argyle
 *
 *  Created by ∞ on 25/04/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "ILObject.h"

ILObject::ILObject() {
	_retainCount = 1;
}
ILObject::~ILObject() {}

void ILObject::retain() {
	_retainCount++;
}

bool ILObject::release() {
	if (_retainCount > 1) {
		_retainCount--;
		return false;
	} else
		return true;
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


ILObject* ILRetain(ILObject* o) {
	o->retain();
	return o;
}

void ILRelease(ILObject* o) {
	if (o->release())
		delete o;
}
