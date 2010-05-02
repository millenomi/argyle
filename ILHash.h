/*
 *  ILHash.h
 *  Argyle
 *
 *  Created by ∞ on 01/05/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef ILHash_H
#define ILHash_H 1

#include "ILLinkedList.h"
#include <stdint.h>
#include <stdlib.h>

typedef uint64_t (*ILHashFunction)(void* value);
typedef bool (*ILEqualsFunction)(void* value, void* otherValue);
typedef bool (*ILValueCorrespondsToKeyFunction)(void* value, void* key);

class ILHash {
public:
	ILHash();
	ILHash(size_t buckets);
	~ILHash();
	
	void addValue(void* value);
	bool containsValue(void* value);
	void removeValue(void* value);
	
	void removeValueForKey(void* key);
	void* valueForKey(void* key);
	bool containsValueForKey(void* key);
	
	void setHashForValue(ILHashFunction h);
	void setHashForKey(ILHashFunction h);
	void setValueCorrespondsToKey(ILValueCorrespondsToKeyFunction h);
	void setEquals(ILEqualsFunction h);
	
	void setRetain(ILRetainFunction h);
	void setRelease(ILReleaseFunction h);
	
	size_t count();
	void getAllValues(void** values);

private:
	void initialize(size_t buckets);
	ILLinkedList* _buckets;
	size_t _bucketsCount;
	
	size_t _count;
	
	// either value or key must be non-NULL.
	bool getBucketAndPositionForValueOrKey(void* value, void* key, ILLinkedList** bucket, ILLinkedListPosition** position);
	
	ILHashFunction _hashForValue, _hashForKey;
	ILValueCorrespondsToKeyFunction _valueCorrespondsToKey;
	
	ILRetainFunction _retain;
	ILReleaseFunction _release;
	
	void* retain(void* value);
	void release(void* value);
	
	ILEqualsFunction _equals;
	bool equals(void* a, void* b);
	
	uint64_t hashForValue(void* value);
	uint64_t hashForKey(void* value);
	bool valueCorrespondsToKey(void* value, void* key);
};

#endif // #ifndef ILHash_H
