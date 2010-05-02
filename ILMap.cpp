/*
 *  ILMap.cpp
 *  Argyle
 *
 *  Created by ∞ on 02/05/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "ILMap.h"

// These are the values for the hash.
// The (copiable) ILObject therein is used as the key.
struct ILMapEntry {
	ILMapEntry(ILObject* k, ILObject* v) {
		key = ILRetain(k); value = ILRetain(v);
	}
	
	ILObject* key;
	ILObject* value;
};

static void ILMapEntryRelease(ILMapEntry* e) {
	ILRelease(e->key);
	ILRelease(e->value);
	delete e;
}

static uint64_t ILMapEntryHashForValue(ILMapEntry* e) {
	return e->key->hash();
}

static bool ILMapEntryHasKey(ILMapEntry* entry, ILObject* key) {
	return entry->key->equals(key);
}

static uint64_t ILMapHashForKey(ILObject* key) {
	return key->hash();
}

ILMap::ILMap() {
	this->initialize();
}

void ILMap::initialize() {
	_h.setRelease((ILReleaseFunction) &ILMapEntryRelease);
	
	_h.setHashForKey((ILHashFunction) &ILMapHashForKey);
	_h.setHashForValue((ILHashFunction) &ILMapEntryHashForValue);
	
	_h.setValueCorrespondsToKey((ILValueCorrespondsToKeyFunction) &ILMapEntryHasKey);
}

void ILMap::setValueForKey(ILCopiable* key, ILObject* value) {
	ILObject* keyCopy = key->copy();
	_h.removeValueForKey(keyCopy);
	
	ILMapEntry* e = new ILMapEntry(keyCopy, value);
	_h.addValue(e);
}

ILObject* ILMap::valueForKey(ILObject* key) {
	ILMapEntry* e = (ILMapEntry*) _h.valueForKey(key);
	return e? e->value : NULL;
}

void ILMap::removeValueForKey(ILObject* key) {
	_h.removeValueForKey(key);
}

size_t ILMap::count() {
	return _h.count();
}
