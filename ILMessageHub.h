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

#include "Argyle.h"
#include "ILMessage.h" // TODO include in Argyle.h

class ILMessageHub : public ILTarget {
public:
	ILMessageHub();
	~ILMessageHub();
	
	void addTargetForMessagesOfType(ILTarget* target, void* type, ILObject* source);
	
	virtual void deliverMessage(ILMessage* m);
	
private:
	ILMap* _targets;
};

#endif // #ifndef ILMessageHub_H
