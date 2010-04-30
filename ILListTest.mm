//
//  ILListTest.mm
//  Argyle
//
//  Created by ∞ on 30/04/10.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

#import "ILListTest.h"
#import "Argyle.h"

@implementation ILListTest

- (void) testBasics;
{	
	ILReleasePool pool;
	
	ILList* l = new ILList(new ILNumber(1), new ILNumber(2), new ILData((uint8_t*)"Wow!", 4), NULL);
	
	STAssertTrue(l->count() == 3, @"3 items");
	STAssertTrue(l->objectAtIndex(0)->equals(new ILNumber(1)), @"ILNo 1 at first position");
	STAssertTrue(l->objectAtIndex(1)->equals(new ILNumber(2)), @"ILNo 1 at 2nd position");
	STAssertTrue(l->objectAtIndex(2)->equals(new ILData((uint8_t*)"Wow!", 4)), @"ILData str at 3rd position");
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

@end
