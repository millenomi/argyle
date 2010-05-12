/*
 *  ILSet.cpp
 *  Argyle
 *
 *  Created by ∞ on 12/05/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "ILSet.h"

static bool ILSetEquals(ILObject* a, ILObject* b) {
	return a == b || (a && b && a->equals(b));
}

static uint64_t ILSetHash(ILObject* o) {
	return o->hash();
}

ILSet::ILSet() {
	_content.setEquals((ILEqualsFunction) &ILSetEquals);
	_content.setRetain((ILRetainFunction) &ILPerformRetain);
	_content.setHashForValue((ILHashFunction) &ILSetHash);
}

ILSet::~ILSet() {}

void ILSet::addObject(ILObject* o) {
	_content.addValue(o);
}

void ILSet::removeObject(ILObject* o) {
	_content.removeValue(o);
}

bool ILSet::containsObject(ILObject* o) {
	return _content.containsValue(o);
}

ILIndex ILSet::count() {
	return _content.count();
}

// ~~~

class ILSetDefaultImplIterator : public ILSetIterator {
	ILSet* _set;
	ILObject** _content;
	ILIndex _count, _current;
	
public:
	ILSetDefaultImplIterator(ILSet* s, ILHash* h) {
		_set = ILRetain(s);
		_count = h->count();
		_content = (ILObject**) malloc(ILSizeOfCArrayOfObjects(_count));
		h->getAllValues((void**) _content);
		_current = 0;
	}
	
	~ILSetDefaultImplIterator() {
		free(_content);
		ILRelease(_set);
	}
	
	virtual ILObject* next() {
		if (_current >= _count)
			return NULL;
		
		ILObject* x = _content[_current];
		_current++;
		return x;
	}
};

ILSetIterator* ILSet::iterate() {
	return new ILSetDefaultImplIterator(this, &_content);
}

// ~~~

static char ILSetSomeUniquePointerValue = 0;
void* ILSetClassIdentity = &ILSetSomeUniquePointerValue;

void* ILSet::classIdentity() {
	return ILSetClassIdentity;
}

// ~~~

bool ILSet::equals(ILObject* other) {
	if (!other)
		return false;
	
	if (other->classIdentity() != ILSetClassIdentity)
		return false;
	
	ILSet* otherSet = (ILSet*) other;
	if (otherSet->count() != this->count())
		return false;
	
	ILSetIterator* i = this->iterate();
	ILObject* o;
	while ((o = i->next())) {
		if (!otherSet->containsObject(o))
			return false;
	}
	
	return true;
}

uint64_t ILSet::hash() {
	uint64_t h = (uint64_t) ILSetClassIdentity;
	ILSetIterator* i = this->iterate();
	ILObject* o;
	while ((o = i->next()))
		h ^= o->hash();
	
	return h;
}

// ~~~

bool ILSet::canCopy() {
	return true;
}

ILSet* ILSet::copy() {
	ILSet* s = new ILSet();
	ILSetIterator* i = this->iterate();
	ILObject* o;
	while ((o = i->next()))
		s->addObject(o);
	
	return s;
}
