/*
 *  ILDataTest.h
 *  Tests
 *
 *  Created by ∞ on 19/05/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef ILDataTest_H
#define ILDataTest_H 1

#include "Argyle.h"
#include "ILTesting.h"

using namespace ILTest;

class ILDataTest : public TestCase {
	ILTestCase(ILDataTest) {
		ILTestWith(testConstruction);
		ILTestWith(testConstructionNonowned);
		ILTestWith(testComparison);
		ILTestWith(testCopy);
		ILTestWith(testAppend);
	}
	
	void testConstruction();
	void testConstructionNonowned();
	void testComparison();
	void testCopy();
	void testAppend();
};

#endif // ILDataTest_H