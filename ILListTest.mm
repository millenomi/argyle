//
//  ILListTest.mm
//  Argyle
//
//  Created by ∞ on 30/04/10.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

#import "ILListTest.h"
#import "Argyle.h"
#import "ILReleasePoolDelegate.h"

@interface ILListTest ()

- (BOOL) testIterationStepWithEachWithObject:(ILObject*) o;

@end


@implementation ILListTest

- (void) testBasics;
{	
	ILReleasePoolMonitor monitor;
	ILNumber* one;
	
	{
		ILReleasePool pool;
		pool.setDelegate(&monitor);
	
		ILList* l = new ILList((one = new ILNumber(1)), new ILNumber(2), new ILData((uint8_t*)"Wow!", 4), NULL);
		
		STAssertTrue(l->count() == 3, @"3 items");
		STAssertTrue(l->objectAtIndex(0)->equals(new ILNumber(1)), @"ILNo 1 at first position");
		STAssertTrue(l->objectAtIndex(1)->equals(new ILNumber(2)), @"ILNo 1 at 2nd position");
		STAssertTrue(l->objectAtIndex(2)->equals(new ILData((uint8_t*)"Wow!", 4)), @"ILData str at 3rd position");
		
		l->removeObjectAtIndex(0);
		STAssertTrue(l->count() == 2, @"2 items");
		STAssertTrue(l->objectAtIndex(0)->equals(new ILNumber(2)), @"ILNo 1 at 2nd position");
		STAssertTrue(l->objectAtIndex(1)->equals(new ILData((uint8_t*)"Wow!", 4)), @"ILData str at 3rd position");
	}
	
	STAssertTrue(monitor.objectWasDestroyed(one), @"The list destroyed the object at index 0 by releasing it");
}

static void ILListTest_Iterate(ILObject* o, void* context, bool* stop) {
	*stop = ![(id)context testIterationStepWithEachWithObject:o];
}

- (BOOL) testIterationStepWithEachWithObject:(ILObject*) o;
{
	switch (indexSeen) {
		case 0:
			STAssertTrue(o->equals(new ILNumber(1)), @"ILNo 1 at first position");
			break;
			
		case 1:
			STAssertTrue(o->equals(new ILNumber(2)), @"ILNo 1 at 2nd position");
			break;
			
		case 2:
			STAssertTrue(o->equals(new ILData((uint8_t*)"Wow!", 4)), @"ILData str at 3rd position");
			break;
	}
	
	indexSeen++;
	return YES;
}

- (void) testIterationWithEach;
{
	ILReleasePool pool;
	
	ILList* l = new ILList(new ILNumber(1), new ILNumber(2), new ILData((uint8_t*)"Wow!", 4), NULL);
	
	indexSeen = 0;
	l->each(&ILListTest_Iterate, (void*) self);
	STAssertEquals((int) indexSeen, (int) 3, @"Three runs of the each() function");
}

- (void) testGetAllObjects;
{
	ILReleasePool pool;
	
	ILList* l = new ILList(new ILNumber(1), new ILNumber(2), new ILData((uint8_t*)"Wow!", 4), NULL);
	
	size_t count = l->count();
	ILObject** objects = (ILObject**) alloca(sizeof(ILObject*) * count);
	
	l->getAllObjects(objects);
	
	STAssertTrue(objects[0]->equals(new ILNumber(1)), @"ILNo 1 at first position");
	STAssertTrue(objects[1]->equals(new ILNumber(2)), @"ILNo 1 at 2nd position");
	STAssertTrue(objects[2]->equals(new ILData((uint8_t*)"Wow!", 4)), @"ILData str at 3rd position");	
}

- (void) testCopy;
{
	ILReleasePool pool;
	
	ILList* l = new ILList(new ILNumber(1), new ILNumber(2), new ILData((uint8_t*)"Wow!", 4), NULL);
	
	STAssertTrue(l->count() == 3, @"3 items");
	STAssertTrue(l->objectAtIndex(0)->equals(new ILNumber(1)), @"ILNo 1 at first position");
	STAssertTrue(l->objectAtIndex(1)->equals(new ILNumber(2)), @"ILNo 1 at 2nd position");
	STAssertTrue(l->objectAtIndex(2)->equals(new ILData((uint8_t*)"Wow!", 4)), @"ILData str at 3rd position");	
	
	STAssertTrue(l->canCopy(), @"The object can be copied");
	
	ILList* l2 = l->copy();
	
	STAssertTrue(l2->count() == 3, @"3 items");
	STAssertTrue(l2->objectAtIndex(0)->equals(new ILNumber(1)), @"ILNo 1 at first position");
	STAssertTrue(l2->objectAtIndex(1)->equals(new ILNumber(2)), @"ILNo 1 at 2nd position");
	STAssertTrue(l2->objectAtIndex(2)->equals(new ILData((uint8_t*)"Wow!", 4)), @"ILData str at 3rd position");

	ILCopiable* lx = (ILCopiable*) l;
	ILList* l3 = (ILList*) lx->copy();
	
	STAssertTrue(l3->count() == 3, @"3 items");
	STAssertTrue(l3->objectAtIndex(0)->equals(new ILNumber(1)), @"ILNo 1 at first position");
	STAssertTrue(l3->objectAtIndex(1)->equals(new ILNumber(2)), @"ILNo 1 at 2nd position");
	STAssertTrue(l3->objectAtIndex(2)->equals(new ILData((uint8_t*)"Wow!", 4)), @"ILData str at 3rd position");
}

@end
