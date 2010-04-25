/*
 *  ILObject.h
 *  Argyle
 *
 *  Created by ∞ on 25/04/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include <stdint.h>

#ifndef ILObject_H
#define ILObject_H 1

class ILObject {
public:
	ILObject();
	virtual ~ILObject();
	
	virtual void retain();
	virtual bool release();
	virtual uint64_t retainCount();
	
	// a class identity token identifies objects of a given class — that is, each class should have one. It should be unique, like a constant string.
	virtual void* classIdentity();
	
	virtual bool equals(ILObject* o);
	
private:
	uint64_t _retainCount;
};

extern ILObject* ILRetain(ILObject* o);
extern void ILRelease(ILObject* o);

extern void* const ILObjectClassIdentity;

#endif