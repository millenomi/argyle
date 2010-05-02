/*
 *  ILReleasePool.cpp
 *  Argyle
 *
 *  Created by ∞ on 25/04/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "ILReleasePool.h"
#include <stdlib.h>

struct ILReleasePoolLink {
	ILObject* object;
	ILReleasePoolLink* nextLink;
};

static ILReleasePool* topmostPool = NULL;

ILReleasePool::ILReleasePool() {
	previousPool = topmostPool;
	topmostPool = this;
	lastLink = NULL;
	_delegate = NULL;
}

void ILReleasePool::addObject(ILObject* o) {
	ILReleasePoolLink* link = new ILReleasePoolLink();
	link->object = o;
	link->nextLink = lastLink;
	
	lastLink = link;
}

ILReleasePool::~ILReleasePool() {
	if (_delegate)
		_delegate->willDestroyPool(this);
	
	ILReleasePoolLink* link = lastLink;
	
	while (link) {
		ILReleasePoolLink* l = link;
		
		bool willDestroy = false;
		if (_delegate) {
			_delegate->willReleaseObject(this, l->object);
			willDestroy = (l->object->retainCount() == 1);
		}
		
		ILRelease(l->object);
		
		if (_delegate && willDestroy)
			_delegate->didDestroyObject(this, l->object);
		
		link = l->nextLink;
		
		delete l;
	}
	
	topmostPool = previousPool;
}

ILReleasePool* ILCurrentReleasePool() {
	return topmostPool;
}

ILObject* ILReleaseLater(ILObject* o) {
	if (o != NULL)
		ILCurrentReleasePool()->addObject(o);
	
	return o;
}

ILReleasePoolDelegate* ILReleasePool::delegate() {
	return _delegate;
}

void ILReleasePool::setDelegate(ILReleasePoolDelegate* delegate) {
	_delegate = delegate;
}
