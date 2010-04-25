//
//  ILNumberTest.mm
//  Argyle
//
//  Created by ∞ on 25/04/10.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

#import "ILNumberTest.h"


@implementation ILNumberTest

- (void) testInteger;
{
	ILReleasePool pool;
	
	ILNumber
		* n1 = (ILNumber*) ILReleaseLater(new ILNumber(42)),
		* n2 = (ILNumber*) ILReleaseLater(new ILNumber(42)),
		* n3 = (ILNumber*) ILReleaseLater(new ILNumber(23));
	
	STAssertTrue(n1 != NULL, @"n1 was constructed");
	STAssertTrue(n2 != NULL, @"n2 was constructed");
	STAssertTrue(n3 != NULL, @"n3 was constructed");

	STAssertTrue(n1->classIdentity() == ILNumberClassIdentity, @"n1 uses the ILNumber class id token");
	STAssertTrue(n2->classIdentity() == ILNumberClassIdentity, @"n2 uses the ILNumber class id token");
	STAssertTrue(n3->classIdentity() == ILNumberClassIdentity, @"n3 uses the ILNumber class id token");
	
	
	STAssertTrue(n1->type() == kILNumberInt64Type, @"n1 uses the int64 number type");
	STAssertTrue(n2->type() == kILNumberInt64Type, @"n1 uses the int64 number type");
	STAssertTrue(n3->type() == kILNumberInt64Type, @"n1 uses the int64 number type");


	STAssertTrue(n1->integerValue() == 42, @"Int value returned correctly");
	STAssertTrue(n1->doubleValue() == (double) 42, @"Double value returned correctly");

	STAssertTrue(n1->integerValue() == n2->integerValue(), @"n1 and n2 return equal values");
	STAssertTrue(n1->integerValue() != n3->integerValue(), @"n1 and n3 return diff values");
	STAssertTrue(n1->equals(n2), @"equals works");
	STAssertTrue(n2->equals(n1), @"equals is symmetric");
	STAssertTrue(!n1->equals(n3), @"equals works with diff value");
	STAssertTrue(n1->hash() == n2->hash(), @"hash returns equal values for equal integers");
}

- (void) testDouble;
{
	ILReleasePool pool;
	
	ILNumber
		* n1 = (ILNumber*) ILReleaseLater(new ILNumber(42.0)),
		* n2 = (ILNumber*) ILReleaseLater(new ILNumber(42.0)),
		* n3 = (ILNumber*) ILReleaseLater(new ILNumber(23.0));
	
	STAssertTrue(n1 != NULL, @"n1 was constructed");
	STAssertTrue(n2 != NULL, @"n2 was constructed");
	STAssertTrue(n3 != NULL, @"n3 was constructed");
	
	STAssertTrue(n1->classIdentity() == ILNumberClassIdentity, @"n1 uses the ILNumber class id token");
	STAssertTrue(n2->classIdentity() == ILNumberClassIdentity, @"n2 uses the ILNumber class id token");
	STAssertTrue(n3->classIdentity() == ILNumberClassIdentity, @"n3 uses the ILNumber class id token");
	
	
	STAssertTrue(n1->type() == kILNumberDoubleType, @"n1 uses the int64 number type");
	STAssertTrue(n2->type() == kILNumberDoubleType, @"n1 uses the int64 number type");
	STAssertTrue(n3->type() == kILNumberDoubleType, @"n1 uses the int64 number type");
	
	
	STAssertTrue(n1->integerValue() == (int64_t) 42.0, @"Int value returned correctly");
	STAssertTrue(n1->doubleValue() == 42.0, @"Double value returned correctly");
	
	STAssertTrue(n1->doubleValue() == n2->doubleValue(), @"n1 and n2 return equal values");
	STAssertTrue(n1->doubleValue() != n3->doubleValue(), @"n1 and n3 return diff values");
	STAssertTrue(n1->equals(n2), @"equals works");
	STAssertTrue(n2->equals(n1), @"equals is symmetric");
	STAssertTrue(!n1->equals(n3), @"equals works with diff value");
	STAssertTrue(n1->hash() == n2->hash(), @"hash returns equal values for equal integers");
}

@end
