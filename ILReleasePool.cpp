/*
 *  ILReleasePool.cpp
 *  Argyle
 *
 *  Created by ∞ on 25/04/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "ILReleasePool.h"

struct ILReleasePoolLink {
	ILObject* object;
	ILReleasePoolLink* nextLink;
};

static ILReleasePool* topmostPool = NULL;

ILReleasePool::ILReleasePool() {
	previousPool = topmostPool;
	topmostPool = this;
}

void ILReleasePool::addObject(ILObject* o) {
	ILReleasePoolLink* link = new ILReleasePoolLink();
	link->object = o;
	link->nextLink = lastLink;
	
	lastLink = link;
}

ILReleasePool::~ILReleasePool() {
	ILReleasePoolLink* link = lastLink;
	
	while (link) {
		ILReleasePoolLink* l = link;
		ILRelease(l->object);
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
