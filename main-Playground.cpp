/*
 *  main-Playground.cpp
 *  Argyle
 *
 *  Created by ∞ on 11/05/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include <iostream>
#include "Argyle.h"

#include "ILMessage.h"
#include "ILRunLoop.h"
#include "ILTimer.h"

static bool run = true;

static void PrintSomeNumbers(ILMessage* m, void* context) {
	static int i = 0;
	printf("Numero %d!\n", i);
	i++;
	
	if (i >= 10)
		run = false;
}

int main(int argc, const char* argv[]) {
	ILReleasePool pool;
	
	ILRunLoop* r = ILRunLoop::current();
	ILTimer* t = new ILTimer(0.5, true);
	r->addSource(t);
	
	ILTarget* ta = new ILFunctionTarget(&PrintSomeNumbers, NULL);
	
	r->currentMessageHub()->addTargetForMessagesOfKind(ta, ILTimerTickedMessage, t);
	
	while (run)
		r->spinForAboutUpTo(5.0);
	_exit(0);
	
	return 0;
}
