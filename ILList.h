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

/** This function is called repeatedly with the objects contained in the list by the ILList::each() function.
 @param thisObject One of the objects in the list.
 @param context The context pointer passed to the ILList::each() function.
 @param stop If the pointed-to boolean variable is set to true, the iteration will stop upon return of this function.
 */
typedef void (*ILListIterationFunction)(ILObject* thisObject, void* context, bool* stop);

/**
 A ILList object (or a list) is an ordered collection of objects. The list retains objects you add to it and releases them upon removal; the list can contain the same object more than once in different locations.
 
 A list cannot contain the NULL value.
 */
class ILList : public ILObject, public ILCopiable {
public:
	/** Creates an empty list. */
	ILList();
	
	/** Creates a list containing the passed-in objects. Terminate the list with a NULL argument. */
	ILList(ILObject* firstObject, ...) __attribute__((sentinel));
	
	/** Creates a list containing the objects in the passed-in C array from index 0 to the index at position count - 1. The list does not require the C array to remain valid past the execution of this constructor. */
	ILList(ILObject** objects, size_t count);
	
	/** Returns the number of objects in this list. */
	size_t count();
	
	/** Adds the object at the end of the list. */
	void addObject(ILObject* o);
	
	/** Adds an object at a given position in the list. */
	void insertObjectAtIndex(size_t i, ILObject* o);
	
	/** Removes the object at the given position in the list. */
	void removeObjectAtIndex(size_t i);
	
	/** Returns the object at the given position in the list. */
	ILObject* objectAtIndex(size_t i);
	
	/** Executes the given function once for each object in the array, passing each of the objects in turn as arguments to each call. The functions are called synchronously.
	 */
	void each(ILListIterationFunction f, void* context);
	
	/** Obtains the contents of this list as a C array.
	 @param objects A C array at least #count() items long. On return, the indexes between 0 and #count() - 1 will contain this list's objects. */
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
