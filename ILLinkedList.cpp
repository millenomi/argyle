/*
 *  ILLinkedList.cpp
 *  Argyle
 *
 *  Created by ∞ on 30/04/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "ILLinkedList.h"
#include <stdio.h>
#include <stdlib.h>

class ILLinkedListLink : public ILLinkedListPosition {
public:
	void* _value;
	ILLinkedListLink* _next;
	ILLinkedListLink* _previous;
	
	virtual void* get() {
		return _value;
	}
	
	virtual ILLinkedListPosition* next() {
		return _next;
	}
	
	virtual ILLinkedListPosition* previous() {
		return _previous;
	}
	
	void describe() {
		fprintf(stderr, "{ %p <-- %p (%p) --> %p }\n", _previous, this, _value, _next);
	}
};

ILLinkedList::ILLinkedList() {
	_head = NULL;
	_tail = NULL;
	
	_count = 0;

	_retain = NULL;
	_release = NULL;
}

ILLinkedList::~ILLinkedList() {
	this->clear();
}

void ILLinkedList::clear() {
	ILLinkedListLink* l = _head;
	while (l) {
		ILLinkedListLink* thisOne = l;
		if (_release)
			_release(thisOne->_value);
		l = thisOne->_next;
		delete thisOne;
	}
}

void ILLinkedList::setRetain(ILRetainFunction f) {
	_retain = f;
}

void ILLinkedList::setRelease(ILReleaseFunction f) {
	_release = f;
}

void* ILLinkedList::retain(void* o) {
	return _retain? _retain(o) : o;
}

void ILLinkedList::release(void* o) {
	if (_release)
		_release(o);
}

ILLinkedListPosition* ILLinkedList::beginning() {
	return _head;
}

ILLinkedListPosition* ILLinkedList::end() {
	return _tail;
}

ILIndex ILLinkedList::count() {
	return _count;
}

void ILLinkedList::remove(ILLinkedListPosition* pos) {
	ILLinkedListLink* l = (ILLinkedListLink*) pos;
	
	ILLinkedListLink
		* before = l->_previous,
		* after = l->_next;
	
	if (before)
		before->_next = after;
	else
		_head = after;
	
	if (after)
		after->_previous = before;
	else
		_tail = before;
	
	this->release(l->_value);
	
	_count--;
	
	delete l;
}

ILLinkedListPosition* ILLinkedList::insertAtBeginning(void* o) {
	ILLinkedListLink* l = new ILLinkedListLink();
	
	l->_value = this->retain(o);
	
	l->_next = _head;
	l->_previous = NULL;
	
	if (_head)
		_head->_previous = l;
	else // there was no head, so this just became the tail too.
		_tail = l;
	
	_head = l;
	
	_count++;
	
	return l;
}

ILLinkedListPosition* ILLinkedList::insertAtEnd(void* o) {
	ILLinkedListLink* l = new ILLinkedListLink();
	
	l->_value = this->retain(o);
	
	l->_next = NULL;
	l->_previous = _tail;
	
	if (_tail)
		_tail->_next = l;
	else // there was no tail, so this just became the head too.
		_head = l;
	
	_tail = l;
	
	_count++;
	
	return l;
}

ILLinkedListPosition* ILLinkedList::insertAfterPosition(ILLinkedListPosition* somePos, void* value) {
	
	ILLinkedListLink* pos = (ILLinkedListLink*) somePos;
	
	if (pos == _tail)
		return this->insertAtEnd(value);

	ILLinkedListLink* l = new ILLinkedListLink();
	
	l->_value = this->retain(value);
	
	l->_next = pos->_next;
	l->_previous = pos;
	
	if (l->_next)
		l->_next->_previous = l;
	else // no next? we're the tail. (we can't be the head, because we're after pos.)
		_tail = l;

	pos->_next = l;
	
	_count++;
	
	return l;
}

ILLinkedListPosition* ILLinkedList::insertBeforePosition(ILLinkedListPosition* somePos, void* value) {
	
	ILLinkedListLink* pos = (ILLinkedListLink*) somePos;

	if (pos == _head)
		return this->insertAtBeginning(value);
	
	ILLinkedListLink* l = new ILLinkedListLink();
	
	l->_value = this->retain(value);

	l->_next = pos;
	l->_previous = pos->_previous;
	
	pos->_previous = l;
	
	if (l->_previous)
		l->_previous->_next = l;
	else // no previous? we're the head. (we can't be the tail, because we're before pos.)
		_head = l;
	
	_count++;

	return l;		

}

void ILLinkedList::getAllValues(void** values) {
	ILLinkedListLink* here = _head;
	ILIndex i = 0;
	
	while (here) {
		values[i] = here->_value;
		here = here->_next;
		i++;
	}
}

void ILLinkedList::describe() {
	fprintf(stderr, "<ILLinkedList %p> --\n", this);
	ILLinkedListLink* here = _head;

	while (here) {
		here->describe();
		here = here->_next;
	}
	
	fprintf(stderr, "-- <end ILLinkedList>\n");
}

ILLinkedListPosition* ILLinkedList::positionAtIndex(ILIndex index) {
	ILLinkedListLink* here = _head;
	
	while (index > 0) {
		here = here->_next;
		index--;
	}
	
	return here;
}
