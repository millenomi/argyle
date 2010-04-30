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

typedef void* (*ILRetainFunction)(void*);
typedef void (*ILReleaseFunction)(void*);

class ILLinkedListPosition {
public:
	virtual void* get() = 0;
	virtual ILLinkedListPosition* next() = 0;
	virtual ILLinkedListPosition* previous() = 0;
};

class ILLinkedListLink;

class ILLinkedList {
public:
	ILLinkedList();
	~ILLinkedList();
	
	void setRetain(ILRetainFunction f);
	void setRelease(ILReleaseFunction f);
	
	size_t count();
	
	void clear();
	
	ILLinkedListPosition* insertAtBeginning(void* value);
	ILLinkedListPosition* insertAtEnd(void* value);
	ILLinkedListPosition* insertAfterPosition(ILLinkedListPosition* pos, void* value);
	ILLinkedListPosition* insertBeforePosition(ILLinkedListPosition* pos, void* value);

	void remove(ILLinkedListPosition* pos);
	
	ILLinkedListPosition* beginning();
	ILLinkedListPosition* end();
	ILLinkedListPosition* positionAtIndex(size_t index);
	
	void getAllValues(void** values);
	
	// Debug aid: prints to stderr.
	void describe();
	
private:
	void* retain(void* o);
	void release(void* o);
	
	
	ILRetainFunction _retain;
	ILReleaseFunction _release;
	
	ILLinkedListLink* _head;
	ILLinkedListLink* _tail;
	
	size_t _count;
};

#endif // #ifndef ILLinkedList_H
