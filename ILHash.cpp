/*
 *  ILHash.cpp
 *  Argyle
 *
 *  Created by ∞ on 01/05/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "ILHash.h"

ILHash::ILHash() {
	this->initialize(64);
}

ILHash::ILHash(size_t buckets) {
	this->initialize(buckets);
}

ILHash::~ILHash() {
	size_t i; for (i = 0; i < _bucketsCount; i++) {
		ILLinkedListPosition* p = _buckets[i].beginning();
		while (p) {
			this->release(p->get());
			p = p->next();
		}
	}
	
	delete [] _buckets;
}

void ILHash::initialize(size_t buckets) {
	_bucketsCount = buckets;
	_buckets = new ILLinkedList[buckets];
	
	_hashForValue = _hashForKey = NULL;
	_valueCorrespondsToKey = NULL;
	
	_retain = NULL;
	_release = NULL;
	
	_equals = NULL;
	
	_count = 0;
}

size_t ILHash::count() { return _count; }

void ILHash::addValue(void* value) {
	value = this->retain(value);
	
	uint64_t hash = this->hashForValue(value);
	size_t i = hash % _bucketsCount;
	
	ILLinkedListPosition* here = _buckets[i].beginning();
	while (here) {
		if (this->equals(here->get(), value))
			return;
		
		here = here->next();
	}
	
	_buckets[i].insertAtEnd(value);
	
	_count++;
}

bool ILHash::getBucketAndPositionForValueOrKey(void* value, void* key, ILLinkedList** bucket, ILLinkedListPosition** position) {
	uint64_t hash;
	
	if (value)
		hash = this->hashForValue(value);
	else
		hash = this->hashForKey(key);
	
	size_t i = hash % _bucketsCount;
	
	ILLinkedListPosition* p = _buckets[i].beginning();
	while (p) {
		if ((value && this->equals(p->get(), value)) ||
			(key && this->valueCorrespondsToKey(p->get(), key))) {
			if (bucket) *bucket = &_buckets[i];
			if (position) *position = p;
			return true;
		}
		
		p = p->next();
	}
	
	return false;
}

void* ILHash::valueForKey(void* key) {
	ILLinkedListPosition* position;
	if (this->getBucketAndPositionForValueOrKey(NULL, key, NULL, &position))
		return position->get();
	else
		return NULL;
}

bool ILHash::containsValueForKey(void* key) {
	return this->getBucketAndPositionForValueOrKey(NULL, key, NULL, NULL);
}

bool ILHash::containsValue(void* value) {
	return this->getBucketAndPositionForValueOrKey(value, NULL, NULL, NULL);	
}

void ILHash::removeValueForKey(void* key) {
	ILLinkedList* bucket; ILLinkedListPosition* position;
	if (this->getBucketAndPositionForValueOrKey(NULL, key, &bucket, &position)) {
		void* value = position->get();
		bucket->remove(position);
		this->release(value);
		
		_count--;
	}
}

void ILHash::removeValue(void* value) {
	ILLinkedList* bucket; ILLinkedListPosition* position;
	if (this->getBucketAndPositionForValueOrKey(value, NULL, &bucket, &position)) {
		void* value = position->get();
		bucket->remove(position);
		this->release(value);
		
		_count--;
	}
}

void ILHash::getAllValues(void** values) {
	size_t i; for (i = 0; i < _bucketsCount; i++) {
		// ARGH POINTER ARITHMETICS
		_buckets[i].getAllValues(values);
		values += _buckets[i].count();
	}
}

// Callbacks

uint64_t ILHash::hashForValue(void* value) {
	if (_hashForValue)
		return _hashForValue(value);
	else
		return (uint64_t) value;
}

uint64_t ILHash::hashForKey(void* value) {
	if (_hashForKey)
		return _hashForKey(value);
	else
		return (uint64_t) value;
}

bool ILHash::valueCorrespondsToKey(void* value, void* key) {
	if (_valueCorrespondsToKey)
		return _valueCorrespondsToKey(value, key);
	else
		return value == key;
}

void* ILHash::retain(void* value) {
	if (_retain)
		return _retain(value);
	else
		return value;
}

void ILHash::release(void* value) {
	if (_release)
		_release(value);
}

bool ILHash::equals(void* a, void* b) {
	if (_equals)
		return _equals(a, b);
	else
		return a == b;
}


void ILHash::setHashForValue(ILHashFunction h) {
	_hashForValue = h;
}

void ILHash::setHashForKey(ILHashFunction h) {
	_hashForKey = h;
}

void ILHash::setValueCorrespondsToKey(ILValueCorrespondsToKeyFunction h) {
	_valueCorrespondsToKey = h;
}

void ILHash::setEquals(ILEqualsFunction h) {
	_equals = h;
}

void ILHash::setRetain(ILRetainFunction h) {
	_retain = h;
}

void ILHash::setRelease(ILReleaseFunction h) {
	_release = h;
}

ILLinkedListPosition* ILHash::beginningOfBucketAtIndex(size_t i) {
	return _buckets[i].beginning();
}

size_t ILHash::bucketsCount() {
	return _bucketsCount;
}
