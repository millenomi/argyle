/*
 *  ILTimer.h
 *  Argyle
 *
 *  Created by ∞ on 18/05/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef ILTimer_H
#define ILTimer_H 1

#include "Argyle.h"
#include "ILSource.h"
#include "ILTime.h"
#include "ILRunLoop.h"

class ILTimer : public ILSource {
public:
	ILTimer(ILTimeInterval i, bool repeats);
	
	virtual void spin();
	virtual ILTimeInterval nextDesiredExecutionTime();
	
private:
	ILTimeInterval _interval, _nextFireTime;
	bool _repeats;
};

extern void* ILTimerTickedMessage;

#endif // #ifndef ILTimer_H