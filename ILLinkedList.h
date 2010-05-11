/*
 *  ILLinkedList.h
 *  Argyle
 *
 *  Created by ∞ on 30/04/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef ILLinkedList_H
#define ILLinkedList_H 1

#include <sys/types.h>

typedef size_t ILIndex;

/** This function is called by ILLinkedList and ILHash to retain values inserted into those containers. It will be called once per value by the container, and can return a different value which will be used instead. One invocation of this function will be paired with an invocation of the corresponding ILReleaseFunction. */
typedef void* (*ILRetainFunction)(void*);

/** This function is called by ILLinkedList and ILHash to release previous values inserted into those containers. It will be called once per value by the container. */
 typedef void (*ILReleaseFunction)(void*);

/** This class represents a position in the linked list. */
class ILLinkedListPosition {
public:
	/** Returns the value at this position in the linked list. This method executes in constant time. */
	virtual void* get() = 0;
	
	/** Returns the position immediately following this one in the list, or NULL this position is the last one. */
	virtual ILLinkedListPosition* next() = 0;

	/** Returns the position immediately preceding this one in the list, or NULL this position is the first one. */
	virtual ILLinkedListPosition* previous() = 0;
};

class ILLinkedListLink;

/** A ILLinkedList implements a linked list storing pointer-sized values. The list does not dereference those pointers.
 
	Most operations on the linked list will operate on 'positions' -- individual links in the list. Certain positions can be retrieved in constant time, most others in linear time. Most operations on positions are performed in constant time.
 */
class ILLinkedList {
public:
	/** Creates a new, empty linked list. */
	ILLinkedList();
	~ILLinkedList();
	
	/** Will be called on values inserted in the list. */
	void setRetain(ILRetainFunction f);
	/** Will be called on values removed from the list. */
	void setRelease(ILReleaseFunction f);
	
	/** Returns the number of values in this list. This method executes in constant time. */
	ILIndex count();
	
	/** Removes all items in this list. This method executes at most in linear time. */
	void clear();
	
	/** Inserts the object at the beginning of the list and returns the position in the list it was inserted in. This method executes in constant time. */
	ILLinkedListPosition* insertAtBeginning(void* value);

	/** Inserts the object at the end of the list and returns the position in the list it was inserted in. This method executes in constant time. */
	ILLinkedListPosition* insertAtEnd(void* value);
	
	/** Inserts the object by creating a new position in the list after the given one. The new position will be returned. This method executes in constant time. */
	ILLinkedListPosition* insertAfterPosition(ILLinkedListPosition* pos, void* value);

	/** Inserts the object by creating a new position in the list before the given one. The new position will be returned. This method executes in constant time. */
	ILLinkedListPosition* insertBeforePosition(ILLinkedListPosition* pos, void* value);

	/** Removes the item at the given position in the list. This method executes in constant time. */
	void remove(ILLinkedListPosition* pos);
	
	/** Returns the first position in the list in constant time. */
	ILLinkedListPosition* beginning();
	/** Returns the last position in the list in constant time. */
	ILLinkedListPosition* end();
	/** Returns the position at the given index in the list. This method may execute at most in linear time. */
	ILLinkedListPosition* positionAtIndex(ILIndex index);
	
	/** Obtains the content of the list as a C array. This method may execute at most in linear time.
	 @param values A C array at least #count() items long. On return, values 0 to #count() - 1 will be set to the values contained by the list. */
	void getAllValues(void** values);
	
	/** As a debug aid, prints the contents of this list to stderr. */
	void describe();
	
private:
	void* retain(void* o);
	void release(void* o);
	
	
	ILRetainFunction _retain;
	ILReleaseFunction _release;
	
	ILLinkedListLink* _head;
	ILLinkedListLink* _tail;
	
	ILIndex _count;
};

#endif // #ifndef ILLinkedList_H
