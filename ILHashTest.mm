//
//  ILHashTest.mm
//  Argyle
//
//  Created by ∞ on 01/05/10.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

#import "ILHashTest.h"

typedef struct {
	const char* key;
	int value;
} ILHashTestValue;

@implementation ILHashTest

static ILHashTestValue a = { "a", 1 };
static ILHashTestValue b = { "b", 2 };
static ILHashTestValue c = { "c", 3 };
static ILHashTestValue d = { "d", 4 };
static ILHashTestValue e = { "e", 5 };

static uint64_t ILHashTestFromValue(ILHashTestValue* v) {
	return (uint64_t) v->key[0];
}

static uint64_t ILHashTestFromKey(char* k) {
	return (uint64_t) k[0];
}

static bool ILHashTestValueHasKey(ILHashTestValue* v, char* k) {
	return v->key[0] == k[0];
}

static void ILHashTestSetUpHash(ILHash* h) {
	h->setHashForValue((ILHashFunction) &ILHashTestFromValue);
	h->setHashForKey((ILHashFunction) &ILHashTestFromKey);
	h->setValueCorrespondsToKey((ILValueCorrespondsToKeyFunction) &ILHashTestValueHasKey);
}

- (void) testInsertionAndRetrieval;
{
	ILHash h;
	
	STAssertEquals((int) h.count(), 0, @"No items");
	
	h.addValue(&a);
	STAssertEquals((int) h.count(), 1, @"One item");
	
	h.addValue(&b);
	STAssertEquals((int) h.count(), 2, @"Two items");
	
	h.addValue(&c);
	h.addValue(&d);
	h.addValue(&e);
	STAssertEquals((int) h.count(), 5, @"Five items");
	
	void* x;

	x = h.valueForKey((void*) "a");
	STAssertEquals(x, (void*) &a, @"'a' was retrieved by its key");
	x = h.valueForKey((void*) "b");
	STAssertEquals(x, (void*) &b, @"'b' was retrieved by its key");
}

- (void) testEditing;
{
	ILHash h;
	
	STAssertFalse(h.containsValueForKey((void*) "a"), @"No value for 'a'");
	
	h.addValue(&a);
	STAssertTrue(h.containsValueForKey((void*) "a"), @"One value for 'a'");
	
	h.removeValueForKey((void*) "a");
	STAssertFalse(h.containsValueForKey((void*) "a"), @"No value for 'a'");
}

@end
