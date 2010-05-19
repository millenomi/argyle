/*
 *  ILPlatformCoreTests.cpp
 *  Tests
 *
 *  Created by ∞ on 19/05/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "ILPlatformCoreTests.h"

#include "ILDataTest.h"

ILSet* ILPlatformCoreAllTestCases(ILTest::Results* r) {
	ILSet* s = new ILSet();
	
	// ----- Add a line for each test case here.
	s->addObject(new ILDataTest(r));
	
	// ----- End.
	
	return s;
}

void ILPlatformCoreRunAllTestCases(ILTest::Results* r) {
	ILSet* s = ILPlatformCoreAllTestCases(r);
	ILSetIterator* i = s->iterate();
	ILTest::TestCase* tc;
	
	while ((tc = (ILTest::TestCase*) i->next()))
		tc->run();
}
