//
//  ILObjectTest.m
//  Argyle
//
//  Created by ∞ on 25/04/10.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

#import "ILObjectTest.h"
#import "ILReleasePool.h"

class ReportOnDeath : public ILObject {
public:
	bool* deathReport;
	
	ReportOnDeath(bool* d) : ILObject() {
		deathReport = d;
	}
	
	~ReportOnDeath() {
		*deathReport = true;
	}
};


@implementation ILObjectTest

- (void) testRetainCount;
{
	ILObject* o = new ILObject();
	STAssertTrue(o->retainCount() == 1, @"Just-created objects have a retain count of 1");
	
	o->retain();
	STAssertTrue(o->retainCount() == 2, @"Retain increases count");
	
	bool shouldDelete = o->release();
	STAssertTrue(o->retainCount() == 1, @"Release decreases count");
	STAssertFalse(shouldDelete, @"A retained object should not be deleted by release().");
	
	shouldDelete = o->release();
	STAssertTrue(shouldDelete, @"The last release() should report it's fine to delete the object.");
	
	delete o;
}

- (void) testRetainReleaseFunctions;
{
//	volatile BOOL go = NO; while (!go) { sleep(1); }
	
	bool dead = false;
	ReportOnDeath* d = new ReportOnDeath(&dead);
	
	STAssertTrue(d->retainCount() == 1, @"Just-created objects have a retain count of 1");
	
	ILRetain(d);
	STAssertTrue(d->retainCount() == 2, @"Retain increases count");
	
	ILRelease(d);
	STAssertTrue(d->retainCount() == 1, @"Release decreases count");
	STAssertFalse(dead, @"A retained object should not be deleted by ILRelease().");
	
	ILRelease(d);
	STAssertTrue(dead, @"The last ILRelease() should delete the object.");
	
}

- (void) testReleasePool;
{
	bool dead = false;
	{
		ILReleasePool pool;		
		ReportOnDeath* d = new ReportOnDeath(&dead);
		ReportOnDeath* d2 = (ReportOnDeath*) ILReleaseLater(d);
		STAssertTrue(d != NULL, @"d was constructed");
		STAssertTrue(d2 == d, @"ILReleaseLater() returned d");
		
		STAssertFalse(dead, @"d is still alive.");
	}
	
	STAssertTrue(dead, @"d was released");
}

@end
