/*
 *  ILData.cpp
 *  Argyle
 *
 *  Created by ∞ on 25/04/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "ILData.h"
#include <math.h>
#include <stdlib.h>
#include <string.h>

static char ILDataIdentityValue = 0;
void* const ILDataClassIdentity = &ILDataIdentityValue;

void* ILData::classIdentity() {
	return ILDataClassIdentity;
}

bool ILData::equals(ILObject* o) {
	if (o == NULL || o->classIdentity() != ILDataClassIdentity)
		return false;
	ILData* d = (ILData*) o;
	if (d->length() != this->length())
		return false;
	
	return memcmp(this->bytes(), ((ILData*)o)->bytes(), this->length()) == 0;
}

uint64_t ILData::hash() {
	uint64_t theHash = (uint64_t) ILDataClassIdentity;
	const size_t max = (_length > 256? 256 : _length);
	for (size_t i = 0; i < max; i++)
		theHash ^= _bytes[i];
	
	return theHash;
}

// ~~~

ILData::ILData(uint8_t* bytes, size_t length) : ILObject() {
	this->initialize(bytes, length, true);
}

ILData::ILData(uint8_t* bytes, size_t length, bool makeCopy) : ILObject() {
	this->initialize(bytes, length, makeCopy);
}

void ILData::initialize(uint8_t* bytes, size_t length, bool makeCopy) {
	_owns = makeCopy;
	_length = length;
	
	if (makeCopy) {
		_bytes = (uint8_t*) malloc(length);
		memcpy(_bytes, bytes, length);
	} else
		_bytes = bytes;
}

ILData::~ILData() {
	if (_owns)
		free(_bytes);
}

// ~~~

uint8_t* ILData::bytes() { return _bytes; }
size_t ILData::length() { return _length; }

// ~~~

bool ILData::canCopy() {
	return true;
}

ILData* ILData::copy() {
	return new ILData(this->bytes(), this->length());
}

// ~~~

void ILData::appendBytes(uint8_t* newBytes, size_t newBytesLength) {
	if (!_owns) {
		fprintf(stderr, "%s: Appending bytes requires a ILData instance that owns its own underlying buffer. Use ->copy() to make a copy of this ILData object before appending bytes. (This is a violation of ILData's contract and WILL be remedied in a future version of this library.)", __func__);
		abort();
	}
	
	if (newBytesLength > 0) {
		size_t newLength = _length + newBytesLength;
		_bytes = (uint8_t*) realloc(_bytes, newLength);
		
		uint8_t* newRegion = _bytes + _length;
		memcpy(newRegion, newBytes, newBytesLength);
		
		_length = newLength;
	}
}
