/*
 *  ILDataTest.cpp
 *  Tests
 *
 *  Created by ∞ on 19/05/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "ILDataTest.h"
#include <string.h>

static uint8_t hello[] = { 'H', 'e', 'l', 'l', 'o' };
static size_t helloSize = sizeof(uint8_t) * 5;

static uint8_t wow[] = { 'W', 'o', 'w' };
static size_t wowSize = sizeof(uint8_t) * 3;


void ILDataTest::testConstruction()
{
	ILReleasePool pool;
	
	ILData* d = new ILData(hello, helloSize);
	
	ILTestNotNull(d);
	ILTestEqualValues(d->classIdentity(), ILDataClassIdentity);
	ILTestNotEqualValues(d->bytes(), (uint8_t*) hello); // the string WAS copied
	ILTestEqualValues(d->length(), helloSize);
	
	assertTrue(memcmp(d->bytes(), hello, d->length()) == 0, "the string was copied correctly");
}

void ILDataTest::testConstructionNonowned()
{
	ILReleasePool pool;
	
	ILData* d = new ILData(hello, helloSize, false);
	
	ILTestNotNull(d);
	ILTestEqualValues(d->classIdentity(), ILDataClassIdentity);
	ILTestEqualValues(d->bytes(), (uint8_t*) hello); // the string WAS NOT copied
	ILTestEqualValues(d->length(), helloSize);
}

void ILDataTest::testComparison()
{
	ILReleasePool pool;
	
	ILData* d = new ILData(hello, helloSize);
	
	ILData* d2 = new ILData(hello, helloSize);
	
	ILTestEqualObjects(d, d2);
	ILTestEqualObjects(d2, d);
	ILTestEqualValues(d->hash(), d2->hash());
	
	ILData* d3 = new ILData(wow, wowSize);
	ILTestNotEqualObjects(d, d3);
}

void ILDataTest::testCopy()
{
	ILReleasePool pool;
	
	ILData* d = new ILData(hello, helloSize);
	ILData* d2 = d->copy();
	
	ILTestEqualObjects(d, d2);
	ILTestEqualObjects(d2, d);
	ILTestEqualValues(d->hash(), d2->hash());
}

void ILDataTest::testAppend()
{
	ILReleasePool pool;
	
	uint8_t hell[] = { 'H', 'e', 'l', 'l' };
	ILData* d = new ILData(hell, sizeof(uint8_t) * 4);
	
	uint8_t o = 'o';
	d->appendBytes(&o, 1);
	
	ILData* d2 = new ILData(hello, helloSize);
	ILTestEqualObjects(d, d2);
}
