/*
 *  ILList.cpp
 *  Argyle
 *
 *  Created by ∞ on 30/04/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "ILList.h"
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

static char ILListIdentityValue = 0;
void* const ILListClassIdentity = &ILListIdentityValue;

ILList::ILList() : ILObject() {
	this->initialize();
}

void* ILList::classIdentity() {
	return ILListClassIdentity;
}

bool ILList::equals(ILObject* o) {
	if (o->classIdentity() != this->classIdentity())
		return false;
	
	ILList* l = (ILList*) o;
	size_t count = this->count();
	if (count != l->count())
		return false;
	
	ILObject
		** objectsOne = (ILObject**) alloca(count * sizeof(void*)), 
		** objectsTwo = (ILObject**) alloca(count * sizeof(void*));
	
	this->getAllObjects(objectsOne);
	l->getAllObjects(objectsTwo);
	
	return memcmp(objectsOne, objectsTwo, count * sizeof(void*)) == 0;
}

uint64_t ILList::hash() {
	uint64_t h = ILObject::hash();
	size_t count = this->count();
	ILObject** objects = (ILObject**) alloca(count * sizeof(void*));
	
	this->getAllObjects(objects);
	size_t i; for (i = 0; i < count; i++)
		h ^= objects[i]->hash();
	
	return h;
}

ILList::ILList(ILObject* firstObject, ...) : ILObject() {
	this->initialize();
	if (!firstObject)
		return;
	
	this->addObject(firstObject);
	va_list l;
	va_start(l, firstObject);
	
	ILObject* o = va_arg(l, ILObject*);
	while (o) {
		this->addObject(o);
		o = va_arg(l, ILObject*);
	}
	
	va_end(l);
}

void ILList::initialize() {
	_content.setRetain((ILRetainFunction) &ILRetain);
	_content.setRelease((ILReleaseFunction) &ILRelease);
}

size_t ILList::count() {
	return _content.count();
}

void ILList::addObject(ILObject* o) {
	_content.insertAtEnd(o);
}

void ILList::insertObjectAtIndex(size_t i, ILObject* o) {
	if (i == _content.count() - 1)
		_content.insertAtEnd(o);
	else
		_content.insertBeforePosition(_content.positionAtIndex(i), o);
}

void ILList::removeObjectAtIndex(size_t i) {
	if (i == _content.count() - 1)
		_content.remove(_content.end());
	else
		_content.remove(_content.positionAtIndex(i));
}

ILObject* ILList::objectAtIndex(size_t i) {
	if (i == _content.count() - 1)
		return (ILObject*) _content.end()->get();
	else
		return (ILObject*) _content.positionAtIndex(i)->get();
}

void ILList::each(ILListIterationFunction f, void* context) {
	bool stop = false;
	ILLinkedListPosition* p = _content.beginning();
	
	while (p) {
		f((ILObject*) p->get(), context, &stop);
		if (stop)
			break;
		
		p = p->next();
	}
}

void ILList::getAllObjects(ILObject** objects) {
	_content.getAllValues((void**) objects);
}
