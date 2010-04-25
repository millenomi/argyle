/*
 *  ILReleasePool.h
 *  Argyle
 *
 *  Created by ∞ on 25/04/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "ILObject.h"

#ifndef ILReleasePool_H
#define ILReleasePool_H 1

struct ILReleasePoolLink;

// Constructing release pools is ONLY supported on the STACK.
// Release pool objects are not ILObjects, and therefore cannot be retained, released, etc.
class ILReleasePool {
public:
	ILReleasePool();
	~ILReleasePool();
	
	// You shouldn't call this directly. Instead, call ILReleaseLater().
	void addObject(ILObject* o);
	
private:
	ILReleasePool* previousPool;
	ILReleasePoolLink* lastLink;
};


extern ILReleasePool* ILCurrentReleasePool();
extern ILObject* ILReleaseLater(ILObject* o);

#endif
