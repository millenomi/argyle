/*
 *  ILRunLoop.h
 *  Argyle
 *
 *  Created by ∞ on 11/05/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef ILRunLoop_H
#define ILRunLoop_H 1

#include "Argyle.h"
#include "ILMessage.h"
#include "ILMessageHub.h"
#include "ILThreadTarget.h"
#include "ILSource.h"

class ILRunLoop : public ILTarget {
public:
	ILRunLoop();
	~ILRunLoop();
	
	void addSource(ILSource* s);
	void spin();
	
	ILMessageHub* currentMessageHub();
	ILTarget* currentThreadTarget();
	
	// ONLY thread-safe method of this class.
	virtual void deliverMessage(ILMessage* m);
	
private:
	ILList* _sources;
	
	ILMessageHub* _messageHub;
	ILTarget* _target;
};

#endif // #ifndef ILRunLoop_H
