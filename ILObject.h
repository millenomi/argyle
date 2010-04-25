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
	
	// a class identity token identifies objects of a given class — that is, each class should have one. It must be a unique pointer — one that is guaranteed different for each class and can be compared with the C == operator.

	// example of producing a unique pointer:
	// static int x = 0;
	// void* const ILSomeClassIdentity = &x; // this is an appropriate class identity pointer.
	virtual void* classIdentity();

	// the default implementation returns true if the pointer value of o is equal to the pointer value of this.
	virtual bool equals(ILObject* o);
	
	// the default implementation returns the value of the 'this' pointer as an integer.
	virtual uint64_t hash();
	
private:
	uint64_t _retainCount;
};

extern ILObject* ILRetain(ILObject* o);
extern void ILRelease(ILObject* o);

extern void* const ILObjectClassIdentity;

#endif
