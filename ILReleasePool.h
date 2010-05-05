/*
 *  ILReleasePool.h
 *  Argyle
 *
 *  Created by ∞ on 25/04/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef ILReleasePool_H
#define ILReleasePool_H 1

#include "ILObject.h"
#include "ILReleasePoolDelegate.h"

struct ILReleasePoolLink;

// Constructing release pools is ONLY supported on the STACK.
// Release pool objects are not ILObjects, and therefore cannot be retained, released, etc.
class ILReleasePool {
public:
	ILReleasePool();
	~ILReleasePool();
	
	// You shouldn't call this directly. Instead, call ILReleaseLater().
	void addObject(ILObject* o);
	
	// Delegates can monitor what's going on in the release pool. These are mostly inteded for testing. You must ensure a delegate exists for at least as long as this pool exists.
	ILReleasePoolDelegate* delegate();
	void setDelegate(ILReleasePoolDelegate* delegate);
	
private:
	ILReleasePoolDelegate* _delegate;
	
	ILReleasePool* previousPool;
	ILReleasePoolLink* lastLink;
};


extern ILReleasePool* ILReleasePoolCurrent();
extern ILObject* ILReleaseLater(ILObject* o);

#endif
