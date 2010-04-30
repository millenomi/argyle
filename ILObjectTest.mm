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
#warning TODO
}

- (void) testRetainReleaseFunctions;
{
#warning TODO
}

- (void) testReleasePool;
{
#warning TODO
}

@end
