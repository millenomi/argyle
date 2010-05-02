/*
 *  ILReleasePoolDelegate.h
 *  Argyle
 *
 *  Created by ∞ on 02/05/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef ILReleasePoolDelegate_H
#define ILReleasePoolDelegate_H 1

#include "ILObject.h"
#include "ILLinkedList.h"

#include <sys/types.h>

class ILReleasePool;

class ILReleasePoolDelegate {
public:

	virtual void willReleaseObject(ILReleasePool* pool, ILObject* object) = 0;
	virtual void didDestroyObject(ILReleasePool* pool, void* objectPointerValue) = 0;
	
	virtual void willDestroyPool(ILReleasePool* pool) = 0;
	
};

class ILReleasePoolMonitor : public ILReleasePoolDelegate {
public:
	ILReleasePoolMonitor();
	
	bool poolIsDestroyed;

	void willReleaseObject(ILReleasePool* pool, ILObject* object);
	void didDestroyObject(ILReleasePool* pool, void* objectPointerValue);
	
	void willDestroyPool(ILReleasePool* pool);
	
	size_t destroyedObjectsCount();
	void getDestroyedObjecs(void** objectPointerValues);
	
	bool objectWasDestroyed(void* object);
	
private:
	ILLinkedList destroyedObjects;
};

#endif // #ifndef ILReleasePoolDelegate_H
