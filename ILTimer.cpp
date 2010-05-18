/*
 *  ILTimer.cpp
 *  Argyle
 *
 *  Created by ∞ on 18/05/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "ILTimer.h"

ILTimer::ILTimer(ILTimeInterval i, bool repeats) {
	_interval = i;
	_nextFireTime = ILGetAbsoluteTime() + i;
	_repeats = repeats;
}

void ILTimer::spin() {
	ILTimeInterval now = ILGetAbsoluteTime();
	if (_nextFireTime <= now) {
		this->runLoop()->currentThreadTarget()->deliverMessage(new ILMessage(ILTimerTickedMessage, this, NULL));
		
		if (_repeats)
			_nextFireTime = now + _interval;
		else
			this->runLoop()->removeSource(this);
	}
}

ILTimeInterval ILTimer::nextDesiredExecutionTime() {
	return _nextFireTime;
}

static char ILTimerTickedMessagePointedValue = 0;
void* ILTimerTickedMessage = &ILTimerTickedMessagePointedValue;
