//
//  ILDataTest.m
//  Argyle
//
//  Created by ∞ on 25/04/10.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

static uint8_t hello[] = { 'H', 'e', 'l', 'l', 'o' };
static size_t helloSize = sizeof(uint8_t) * 5;

static uint8_t wow[] = { 'W', 'o', 'w' };
static size_t wowSize = sizeof(uint8_t) * 3;

#import "ILDataTest.h"

@implementation ILDataTest

- (void) testConstruction;
{
	ILReleasePool pool;
	
	ILData* d = new ILData(hello, helloSize);
	ILReleaseLater(d);
	
	STAssertTrue(d != NULL, @"d was constructed");
	STAssertTrue(d->classIdentity() == ILDataClassIdentity, @"d uses the ILData class id token");
	STAssertTrue(d->bytes() != hello, @"the string was copied");
	STAssertTrue(d->length() == helloSize, @"the length was init'd correctly");
	
	STAssertTrue(memcmp(d->bytes(), hello, d->length()) == 0, @"the string was copied correctly");
}

- (void) testConstructionNonowned;
{
	ILReleasePool pool;
	
	ILData* d = new ILData(hello, helloSize, false);
	ILReleaseLater(d);
	
	STAssertTrue(d != NULL, @"d was constructed");
	STAssertTrue(d->classIdentity() == ILDataClassIdentity, @"d uses the ILData class id token");
	STAssertTrue(d->bytes() == hello, @"the string was NOT copied");
	STAssertTrue(d->length() == helloSize, @"the length was init'd correctly");
}

- (void) testComparison {
	ILReleasePool pool;

	ILData* d = new ILData(hello, helloSize);
	ILReleaseLater(d);

	ILData* d2 = new ILData(hello, helloSize);
	ILReleaseLater(d2);
	
	STAssertTrue(d->equals(d2), @"equals works");
	STAssertTrue(d2->equals(d), @"equals is symmetric");
	STAssertTrue(d->hash() == d2->hash(), @"equal strings have the same hash");
	
	ILData* d3 = new ILData(wow, wowSize);
	STAssertFalse(d->equals(d3), @"equals works");	
}

- (void) testCopy {
	ILReleasePool pool;
	
	ILData* d = new ILData(hello, helloSize);
	ILReleaseLater(d);
	
	ILData* d2 = d->copy();
	
	STAssertTrue(d->equals(d2), @"equals works");
	STAssertTrue(d2->equals(d), @"equals is symmetric");
	STAssertTrue(d->hash() == d2->hash(), @"equal strings have the same hash");
}

@end
