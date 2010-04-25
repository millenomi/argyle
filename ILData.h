/*
 *  ILData.h
 *  Argyle
 *
 *  Created by ∞ on 25/04/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef ILData_H
#define ILData_H 1

#include "Argyle.h"
#include <sys/types.h>
#include <stdint.h>

// A wrapper for a byte buffer.
class ILData : public ILObject {
public:
	// If makeCopy, the buffer's content will be copied.
	// Otherwise, not. If so, it's the creator's responsibility to make sure the buffer remains alive as long as this object exists.
	ILData(uint8_t* bytes, size_t length, bool makeCopy);

	// Same as above with makeCopy == true.
	ILData(uint8_t* bytes, size_t length);
	
	~ILData();

	uint8_t* bytes();
	size_t length();
	
	// Creates a copy of this buffer.
	ILData* copy();
	
	// ILObject overrides.
	virtual void* classIdentity();
	virtual bool equals(ILObject* o);
	virtual uint64_t hash();
	
private:
	void initialize(uint8_t* bytes, size_t length, bool makeCopy);
	
	bool _owns;
	uint8_t* _bytes;
	size_t _length;
};

extern void* const ILDataClassIdentity;

#endif
