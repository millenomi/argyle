/*
 *  ILMessageHub.h
 *  Argyle
 *
 *  Created by ∞ on 05/05/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef ILMessageHub_H
#define ILMessageHub_H 1

#include "ILObject.h"
#include "ILMessage.h"

/**
 A message hub is a target for messages that works to distribute those messages to a number of other targets. You register a number of targets with an instance of this class, then have messages delivered to that instance; the message will be delivered to all registered targets that want to receive that particular kind of message (optionally only from a given source).
 
 */
class ILMessageHub : public ILTarget {
public:
	ILMessageHub();
	~ILMessageHub();
	
	void addTargetForMessagesOfKind(ILTarget* target, void* kind, ILObject* source);
	void removeTargetForMessagesOfKind(ILTarget* t, void* kind);
	
	virtual void deliverMessage(ILMessage* m);
	
private:
	ILMap* _targets;
};

#endif // #ifndef ILMessageHub_H
