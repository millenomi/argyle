/*
 *  ILNumber.h
 *  Argyle
 *
 *  Created by ∞ on 25/04/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef ILNumber_H
#define ILNumber_H 1

#include "Argyle.h"

enum {
	kILNumberInt64Type = 0,
	kILNumberDoubleType,
	kILNumberBoolType,
	kILNumberNonretainedPointerType,
};
typedef uint32_t ILNumberType;

class ILNumber : public ILObject, public ILCopiable {
public:
	ILNumber(int integerValue); // convenience, casts to int64_t.
	
	ILNumber(bool booleanValue);
	ILNumber(int64_t integerValue);
	ILNumber(double doubleValue);
	
	ILNumber(void* nonretainedPointerValue);
	
	ILNumberType type();
	
	int64_t integerValue();
	double doubleValue();
	bool booleanValue();
	
	void* nonretainedPointerValue();
	
	// ILObject overrides.
	virtual void* classIdentity();
	virtual bool equals(ILObject* o);
	virtual uint64_t hash();
	
	virtual bool canCopy();
	virtual ILNumber* copy();
	
private:
	ILNumberType _type;
	union {
		int64_t integerValue;
		double doubleValue;
		bool booleanValue;
		void* nonretainedPointerValue;
	} _value;
};

extern void* const ILNumberClassIdentity;

#endif
