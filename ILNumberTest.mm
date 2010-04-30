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
		* n1 = new ILNumber(42),
		* n2 = new ILNumber(42),
		* n3 = new ILNumber(0);
	
	STAssertTrue(n1 != NULL, @"n1 was constructed");
	STAssertTrue(n2 != NULL, @"n2 was constructed");
	STAssertTrue(n3 != NULL, @"n3 was constructed");

	STAssertTrue(n1->classIdentity() == ILNumberClassIdentity, @"n1 uses the ILNumber class id token");
	STAssertTrue(n2->classIdentity() == ILNumberClassIdentity, @"n2 uses the ILNumber class id token");
	STAssertTrue(n3->classIdentity() == ILNumberClassIdentity, @"n3 uses the ILNumber class id token");
	
	
	STAssertTrue(n1->type() == kILNumberInt64Type, @"n1 uses the int64 number type");
	STAssertTrue(n2->type() == kILNumberInt64Type, @"n2 uses the int64 number type");
	STAssertTrue(n3->type() == kILNumberInt64Type, @"n3 uses the int64 number type");

	STAssertTrue(n1->booleanValue(), @"Nonzero returns true");
	STAssertFalse(n3->booleanValue(), @"Zero returns false");

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
		* n1 = new ILNumber(42.0),
		* n2 = new ILNumber(42.0),
		* n3 = new ILNumber(0.0);
	
	STAssertTrue(n1 != NULL, @"n1 was constructed");
	STAssertTrue(n2 != NULL, @"n2 was constructed");
	STAssertTrue(n3 != NULL, @"n3 was constructed");
	
	STAssertTrue(n1->classIdentity() == ILNumberClassIdentity, @"n1 uses the ILNumber class id token");
	STAssertTrue(n2->classIdentity() == ILNumberClassIdentity, @"n2 uses the ILNumber class id token");
	STAssertTrue(n3->classIdentity() == ILNumberClassIdentity, @"n3 uses the ILNumber class id token");
	
	
	STAssertTrue(n1->type() == kILNumberDoubleType, @"n1 uses the double number type");
	STAssertTrue(n2->type() == kILNumberDoubleType, @"n2 uses the double number type");
	STAssertTrue(n3->type() == kILNumberDoubleType, @"n3 uses the double number type");
	
	
	STAssertTrue(n1->integerValue() == (int64_t) 42.0, @"Int value returned correctly");
	STAssertTrue(n1->doubleValue() == 42.0, @"Double value returned correctly");
	STAssertTrue(n1->booleanValue(), @"Nonzero returns true");
	STAssertFalse(n3->booleanValue(), @"Zero returns false");
	
	STAssertTrue(n1->doubleValue() == n2->doubleValue(), @"n1 and n2 return equal values");
	STAssertTrue(n1->doubleValue() != n3->doubleValue(), @"n1 and n3 return diff values");
	STAssertTrue(n1->equals(n2), @"equals works");
	STAssertTrue(n2->equals(n1), @"equals is symmetric");
	STAssertTrue(!n1->equals(n3), @"equals works with diff value");
	STAssertTrue(n1->hash() == n2->hash(), @"hash returns equal values for equal integers");
}

- (void) testBoolean;
{
	ILReleasePool pool;
	
	ILNumber
		* n1 = new ILNumber(true),
		* n2 = new ILNumber(true),
		* n3 = new ILNumber(false);
	
	STAssertTrue(n1 != NULL, @"n1 was constructed");
	STAssertTrue(n2 != NULL, @"n2 was constructed");
	STAssertTrue(n3 != NULL, @"n3 was constructed");
	
	STAssertTrue(n1->classIdentity() == ILNumberClassIdentity, @"n1 uses the ILNumber class id token");
	STAssertTrue(n2->classIdentity() == ILNumberClassIdentity, @"n2 uses the ILNumber class id token");
	STAssertTrue(n3->classIdentity() == ILNumberClassIdentity, @"n3 uses the ILNumber class id token");
	
	
	STAssertTrue(n1->type() == kILNumberBoolType, @"n1 uses the bool number type");
	STAssertTrue(n2->type() == kILNumberBoolType, @"n2 uses the bool number type");
	STAssertTrue(n3->type() == kILNumberBoolType, @"n3 uses the bool number type");
	
	
	STAssertTrue(n1->integerValue() == 1, @"Int value returned correctly (true)");
	STAssertTrue(n1->doubleValue() == 1.0, @"Double value returned correctly (true)");
	STAssertTrue(n3->integerValue() == 0, @"Int value returned correctly (false)");
	STAssertTrue(n3->doubleValue() == 0.0, @"Double value returned correctly (false)");
	
	STAssertTrue(n1->booleanValue() == n2->booleanValue(), @"n1 and n2 return equal values");
	STAssertTrue(n1->booleanValue() != n3->booleanValue(), @"n1 and n3 return diff values");
	STAssertTrue(n1->equals(n2), @"equals works");
	STAssertTrue(n2->equals(n1), @"equals is symmetric");
	STAssertTrue(!n1->equals(n3), @"equals works with diff value");
	STAssertTrue(n1->hash() == n2->hash(), @"hash returns equal values for equal integers");
}

@end
