/*
 *  ILList.h
 *  Argyle
 *
 *  Created by ∞ on 30/04/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef ILList_H
#define ILList_H 1

#include "ILObject.h"
#include <sys/types.h>

#include "ILLinkedList.h"

typedef void (*ILListIterationFunction)(ILObject* thisObject, void* context, bool* stop);

class ILList : public ILObject, public ILCopiable {
public:
	ILList();
	ILList(ILObject* firstObject, ...) __attribute__((sentinel));
	ILList(ILObject** objects, size_t count);
	
	size_t count();
	void addObject(ILObject* o);
	
	void insertObjectAtIndex(size_t i, ILObject* o);
	void removeObjectAtIndex(size_t i);
	
	ILObject* objectAtIndex(size_t i);
	
	void each(ILListIterationFunction f, void* context);
	void getAllObjects(ILObject** objects);

	// ILObject overrides.
	virtual void* classIdentity();
	virtual bool equals(ILObject* o);
	virtual uint64_t hash();
	
	// ILCopiable overrides.
	virtual bool canCopy();
	virtual ILList* copy();
	
private:
	void initialize();
	ILLinkedList _content;
};

extern void* const ILListClassIdentity;

#endif // #ifndef ILList_H
