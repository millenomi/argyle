//
//  ILListTest.h
//  Argyle
//
//  Created by ∞ on 30/04/10.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

#import <SenTestingKit/SenTestingKit.h>
#import "ILObject.h"
#import "ILReleasePool.h"
#import "ILList.h"

@interface ILListTest : SenTestCase {
	size_t indexSeen;
}

- (BOOL) testIterationStepWithEachWithObject:(ILObject*) o;

@end
