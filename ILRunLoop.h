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
#include "ILTime.h"

#include <pthread.h>


class ILRunLoop : public ILTarget {
public:
	ILRunLoop();
	~ILRunLoop();
	
	void addSource(ILSource* s);
	void removeSource(ILSource* s);
	
	void spin();
	
	ILMessageHub* currentMessageHub();
	ILTarget* currentThreadTarget();
	
	/**
	 Spins the run loop for a time in the ballpark of the specified number of seconds.
	 Note that the method can run for far shorter or far longer times. It will return before the specified amount of time if spinning the loop is meaningless (because there are no registered sources, for example). It will return far after the specified amount of time if a spin takes longer than that (it will however return as soon as possible after that).
	 When this method is called, the current thread sleeps until the timeout is met or a source signals that it's ready (via the run loop's #signalReady() method). It will then spin. This may repeat for a number of times until the run loop detects that the specified timeout has been exceeded.
	 */
	void spinForAboutUpTo(ILTimeInterval seconds);
	
	// ONLY thread-safe method of this class.
	virtual void deliverMessage(ILMessage* m);
	
	static ILRunLoop* current();
	
	void signalReady();
	
private:
	ILSet* _sources;
	
	ILMessageHub* _messageHub;
	ILTarget* _target;
	
	pthread_cond_t _signaler;
	pthread_mutex_t _mutex;
};

#endif // #ifndef ILRunLoop_H
