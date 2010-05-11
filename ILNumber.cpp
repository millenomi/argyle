/*
 *  ILNumber.cpp
 *  Argyle
 *
 *  Created by ∞ on 25/04/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "ILNumber.h"
#include <stdlib.h>

static char ILNumberIdentityValue = 0;
void* const ILNumberClassIdentity = &ILNumberIdentityValue;

void* ILNumber::classIdentity() {
	return ILNumberClassIdentity;
}

bool ILNumber::equals(ILObject* o) {
	if (o == NULL || o->classIdentity() != ILNumberClassIdentity)
		return false;
	
	ILNumber* n = (ILNumber*) o;
	
	if (this->type() != n->type())
		return false;
	
	switch (this->type()) {
		case kILNumberInt64Type:
			return this->integerValue() == n->integerValue();
		case kILNumberDoubleType:
			return this->doubleValue() == n->doubleValue();
		case kILNumberBoolType:
			return this->booleanValue() == n->booleanValue();
		default:
			return false;
	}
}

uint64_t ILNumber::hash() {
	uint64_t theHash = (int64_t) ILNumberClassIdentity;
	theHash ^= this->integerValue();
	return theHash;
}

// ~~~

ILNumber::ILNumber(int i) {
	_type = kILNumberInt64Type;
	_value.integerValue = (int64_t) i;
}

ILNumber::ILNumber(int64_t i) {
	_type = kILNumberInt64Type;
	_value.integerValue = i;
}

ILNumber::ILNumber(double i) {
	_type = kILNumberDoubleType;
	_value.doubleValue = i;
}

ILNumber::ILNumber(bool b) {
	_type = kILNumberBoolType;
	_value.booleanValue = b;
}

ILNumber::ILNumber(void* p) {
	_type = kILNumberNonretainedPointerType;
	_value.nonretainedPointerValue = p;
}

ILNumberType ILNumber::type() { return _type; }

// ~~~

int64_t ILNumber::integerValue() {
	switch (_type) {
		case kILNumberInt64Type:
			return _value.integerValue;
		case kILNumberDoubleType:
			return (int64_t) _value.doubleValue;
		case kILNumberBoolType:
			return _value.booleanValue? 1 : 0;
		case kILNumberNonretainedPointerType:
			return (intptr_t) _value.nonretainedPointerValue;
		default:
			return 0;
	}
}

double ILNumber::doubleValue() {
	switch (_type) {
		case kILNumberInt64Type:
			return (double) _value.integerValue;
		case kILNumberDoubleType:
			return _value.doubleValue;
		case kILNumberBoolType:
			return _value.booleanValue? 1.0 : 0.0;
		case kILNumberNonretainedPointerType:
			return 0.0; // pointers can't be floats.
		default:
			return 0;			
	}
}

bool ILNumber::booleanValue() {
	switch (_type) {
		case kILNumberInt64Type:
			return _value.integerValue? true : false;
		case kILNumberDoubleType:
			return _value.doubleValue? true : false;
		case kILNumberBoolType:
			return _value.booleanValue;
		case kILNumberNonretainedPointerType:
			return _value.nonretainedPointerValue? true : false;
		default:
			return 0;			
	}	
}

// ~~~

bool ILNumber::canCopy() {
	return true;
}

ILNumber* ILNumber::copy() {
	return this; // ILNumber is immutable.
}
