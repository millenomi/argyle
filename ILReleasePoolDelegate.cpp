/*
 *  ILReleasePoolDelegate.cpp
 *  Argyle
 *
 *  Created by ∞ on 02/05/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "ILReleasePoolDelegate.h"

ILReleasePoolMonitor::ILReleasePoolMonitor() {
	poolIsDestroyed = false;
}

void ILReleasePoolMonitor::willReleaseObject(ILReleasePool* pool, ILObject* object) {}

void ILReleasePoolMonitor::didDestroyObject(ILReleasePool* pool, void* objectPointerValue) {
	destroyedObjects.insertAtEnd((void*)objectPointerValue);
}

void ILReleasePoolMonitor::willDestroyPool(ILReleasePool* pool) {
	poolIsDestroyed = true;
}

size_t ILReleasePoolMonitor::destroyedObjectsCount() {
	return destroyedObjects.count();
}

void ILReleasePoolMonitor::getDestroyedObjecs(void** objectPointerValues) {
	destroyedObjects.getAllValues((void**) objectPointerValues);
}

bool ILReleasePoolMonitor::objectWasDestroyed(void* object) {
	ILLinkedListPosition* p = destroyedObjects.beginning();
	while (p) {
		if (p->get() == object)
			return true;
		
		p = p->next();
	}
	
	return false;
}
