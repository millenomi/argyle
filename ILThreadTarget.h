/*
 *  ILThreadTarget.h
 *  Argyle
 *
 *  Created by ∞ on 11/05/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */


#ifndef ILThreadTarget_H
#define ILThreadTarget_H 1

#include "Argyle.h"
#include "ILMessage.h"
#include "ILSource.h"

class ILThreadTarget : public ILTarget, public ILSource {
public:
	ILThreadTarget(ILTarget* deliveryTarget);
	~ILThreadTarget();
	
	virtual void deliverMessage(ILMessage* m);
	virtual void performPeriodicWork();
	
	void deliverPendingMessagesOnThisThread();
	
private:
	ILTarget* _deliveryTarget;
	ILList* _messages;
	pthread_mutex_t _mutex;
};

#endif // #ifndef ILThreadTarget_H
