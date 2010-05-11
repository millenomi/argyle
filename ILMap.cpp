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
	ILRetain(value); // in case remove... below releases the value.
	
	ILObject* keyCopy = key->copy();
	_h.removeValueForKey(keyCopy);
	
	ILMapEntry* e = new ILMapEntry(keyCopy, value);
	_h.addValue(e);
	
	ILRelease(value);
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

void ILMap::getContent(ILObject** keys, ILObject** values) {
	if (!keys && !values)
		return;
		
	size_t count = _h.count();
	ILMapEntry** entries = (ILMapEntry**) alloca(sizeof(ILMapEntry*) * count);
	_h.getAllValues((void**) entries);
	
	size_t i; for (i = 0; i < count; i++) {
		if (keys)
			keys[i] = entries[i]->key;
		if (values)
			values[i] = entries[i]->value;
	}
}

class ILMapDefaultImplIterator : public ILMapIterator {
public:
	ILMap* _m; ILHash* _h;
	
	ILMapDefaultImplIterator(ILMap* m, ILHash* h) : ILMapIterator() {
		_m = (ILMap*) ILRetain(m);
		_h = h;
		
		bucketIndex = 0;
		current = NULL;
	}
	
	~ILMapDefaultImplIterator() {
		ILRelease(_m);
	}
	
	size_t bucketIndex;
	ILLinkedListPosition* current;
	
	virtual bool getNext(ILObject** key, ILObject** value) {
		if (bucketIndex >= _h->bucketsCount())
			return false;
		
		if (current)
			current = current->next();
		
		if (!current) {
			bucketIndex++;
			if (bucketIndex >= _h->bucketsCount())
				return false;
		}
		
		while (!current) {
			current = _h->beginningOfBucketAtIndex(bucketIndex);
			if (!current)
				bucketIndex++;
			
			if (bucketIndex >= _h->bucketsCount())
				return false;
		}
		
		ILMapEntry* e = (ILMapEntry*) current->get();
		if (key) *key = e->key;
		if (value) *value = e->value;
		return true;
	}
};

ILMapIterator* ILMap::iterate() {
	return new ILMapDefaultImplIterator(this, &_h);
}
