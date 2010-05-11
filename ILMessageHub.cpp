/*
 *  ILMessageHub.cpp
 *  Argyle
 *
 *  Created by ∞ on 05/05/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "ILMessageHub.h"

class ILMessageHubTarget : public ILObject {
public:
	ILMessageHubTarget(ILTarget* t, ILObject* d) : ILObject() {
		_target = (ILTarget*) ILRetain(t);
		_desiredSource = ILRetain(d); // should retain? TODO
	}
	
	~ILMessageHubTarget() {
		ILRelease(_desiredSource);
		ILRetain(_target);
	}
	
	ILObject* _desiredSource;
	ILTarget* _target;
};

ILMessageHub::ILMessageHub() {
	_targets = (ILMap*) ILRetain(new ILMap());
}

ILMessageHub::~ILMessageHub() {
	ILRelease(_targets);
}

void ILMessageHub::addTargetForMessagesOfKind(ILTarget* target, void* type, ILObject* source) {
	ILMessageHubTarget* t = new ILMessageHubTarget(target, source);
	ILNumber* key = new ILNumber(type);
	
	ILList* l = (ILList*) _targets->valueForKey(key);
	if (!l) {
		l = new ILList();
		_targets->setValueForKey(key, l);
	}
	
	l->addObject(t);
}

void ILMessageHub::removeTargetForMessagesOfKind(ILTarget* t, void* kind) {
	ILNumber* key = new ILNumber(kind);
	ILList* l = (ILList*) _targets->valueForKey(key);
	if (l) {
		ILListIterator* i = l->copy()->iterate();
		ILMessageHubTarget* ht;
		
		size_t index = 0;
		while ((ht = (ILMessageHubTarget*) i->next())) {
			if (ht->_target == t)
				l->removeObjectAtIndex(index);
			else
				index++;
		}
	}
}


void ILMessageHub::deliverMessage(ILMessage* m) {
//#error TODO
	//size_t listCount = _targets->count();
//	ILList** lists = (ILList**)
//		alloca(ILSizeOfCArrayOfObjects(listCount));
//	
//	_targets->getContent(NULL, (ILObject**) &lists);
//	
//	size_t i; for (i = 0; i < listCount; i++) {
//		ILList* l = lists[i];
//		
//		size_t targetCount = l->count();
//		ILMessageHubTarget** targets = (ILMessageHubTarget**)
//			alloca(ILSizeOfCArrayOfObjects(targetCount));
//		
//		size_t j; for(j = 0; j < targetCount; j++) {
//			if (!targets[j]->_desiredSource || (m->source() && targets[j]->_desiredSource->equals(m->source())))
//				targets[j]->_target->deliverMessage(m);
//		}
//	}
	
//	ILDebugTrap(go);
	
	ILReleasePool pool;
	
	ILMapIterator* bucketsIterator = _targets->iterate();
	ILList* list;
	while (bucketsIterator->getNext(NULL, (ILObject**) &list)) {
		
		ILListIterator* targetsIterator = list->iterate();
		ILMessageHubTarget* t;
		
		while ((t = (ILMessageHubTarget*) targetsIterator->next())) {
			if (!t->_desiredSource || (m->source() && t->_desiredSource->equals(m->source())))
				t->_target->deliverMessage(m);
		}
		
	}
}

