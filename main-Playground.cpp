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

int main(int argc, const char* argv[]) {
	ILReleasePool pool;
	
	ILRunLoop* r = ILRunLoop::current();
	r->spinForUpTo(5.0);
	
	return 0;
}