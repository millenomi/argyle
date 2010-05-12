//
//  ILSetTest.mm
//  Argyle
//
//  Created by ∞ on 12/05/10.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

#import "ILSetTest.h"


@implementation ILSetTest

- (void) testBasics;
{
	ILReleasePool pool;
	
	ILSet* set = new ILSet();
	
	STAssertEquals(set->classIdentity(), ILSetClassIdentity, @"The set has the right class ID");
	STAssertTrue(set->canCopy(), @"The set is copiable");
}

- (void) testInsertionAndRemoval;
{
	ILReleasePool pool;
	
	ILSet* set = new ILSet();
	STAssertEquals(set->count(), (ILIndex)0, @"The set is empty");
	STAssertFalse(set->containsObject(new ILNumber(42)), @"The set does not contain 42");

	set->addObject(new ILNumber(42));
	STAssertEquals(set->count(), (ILIndex)1, @"The set has one item");	
	STAssertTrue(set->containsObject(new ILNumber(42)), @"The set contains 42");

	set->addObject(new ILNumber(42));
	STAssertEquals(set->count(), (ILIndex)1, @"The set has one item (after repeated insertion)");
	STAssertTrue(set->containsObject(new ILNumber(42)), @"The set contains 42");

	set->removeObject(new ILNumber(42));
	STAssertEquals(set->count(), (ILIndex)0, @"The set is empty");
	STAssertFalse(set->containsObject(new ILNumber(42)), @"The set does not contain 42");
}

- (void) testEquality;
{
	ILReleasePool pool;
	
	ILSet* setA = new ILSet(), * setB = new ILSet();
	
	STAssertTrue(setA->equals(setB), @"Empty sets are equal");
	STAssertTrue(setB->equals(setA), @"Empty sets are equal");
	STAssertEquals(setA->hash(), setB->hash(), @"Empty sets have the same hash");
	
	setA->addObject(new ILNumber(42));
	setB->addObject(new ILNumber(42));
	
	STAssertTrue(setA->equals(setB), @"{42} sets are equal");
	STAssertTrue(setB->equals(setA), @"Empty sets are equal");
	STAssertEquals(setA->hash(), setB->hash(), @"{42} sets have the same hash");
	
	setB->addObject(new ILNumber(33));
	STAssertFalse(setA->equals(setB), @"{42} set != {42, 33} set");
	STAssertFalse(setB->equals(setA), @"{42} set != {42, 33} set");
}

@end
