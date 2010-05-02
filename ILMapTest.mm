//
//  ILMapTest.m
//  Argyle
//
//  Created by ∞ on 02/05/10.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

#import "ILMapTest.h"
#import "ILNumber.h"
#import "ILData.h"

@implementation ILMapTest

- (void) testInsertionAndRetrieval;
{
	ILReleasePool pool;
	
	ILMap* m = new ILMap();
	STAssertEquals(m->count(), (size_t) 0, @"0 object(s) in map");
	
	ILData* hi = new ILData((uint8_t*)"Hi!", 3);
	ILData* hello = new ILData((uint8_t*)"Hello", 5);
	
	m->setValueForKey(new ILNumber(42), hi);
	STAssertEquals(m->count(), (size_t) 1, @"1 object(s) in map");

	m->setValueForKey(new ILNumber(33), hello);
	STAssertEquals(m->count(), (size_t) 2, @"2 object(s) in map");

	ILObject* x = m->valueForKey(new ILNumber(42));
	STAssertTrue(hi->equals(x), @"42 returns Hi");
	
	ILObject* y = m->valueForKey(new ILNumber(33));
	STAssertTrue(hello->equals(y), @"33 returns Hello");
}

- (void) testRemoval;
{
	ILReleasePool pool;
	
	ILMap* m = new ILMap();
	ILData* hi = new ILData((uint8_t*)"Hi!", 3);
	ILData* hello = new ILData((uint8_t*)"Hello", 5);
	
	m->setValueForKey(new ILNumber(42), hi);
	m->setValueForKey(new ILNumber(33), hello);
	
	m->removeValueForKey(new ILNumber(33));
	STAssertEquals(m->count(), (size_t) 1, @"1 object in map");
	STAssertEquals(m->valueForKey(new ILNumber(33)), (ILObject*) NULL, @"object was removed");
	STAssertTrue(m->valueForKey(new ILNumber(42)) == hi, @"other object is untouched");
}

@end
