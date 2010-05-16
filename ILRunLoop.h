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

typedef double ILTimeInterval;
extern ILTimeInterval ILGetAbsoluteTime();

class ILRunLoop : public ILTarget {
public:
	ILRunLoop();
	~ILRunLoop();
	
	void addSource(ILSource* s);
	void removeSource(ILSource* s);
	
	void spin();
	
	ILMessageHub* currentMessageHub();
	ILTarget* currentThreadTarget();
	
	void spinForUpTo(ILTimeInterval seconds);
	
	// ONLY thread-safe method of this class.
	virtual void deliverMessage(ILMessage* m);
	
	static ILRunLoop* current();
	
	void signalReady();
	void signalByDeliveringMessage(ILMessage* m);
	
private:
	ILSet* _sources;
	
	ILMessageHub* _messageHub;
	ILTarget* _target;
	
	int _pipe[2];
};

extern void* const ILRunLoopSignalReadyMessage;

#endif // #ifndef ILRunLoop_H
