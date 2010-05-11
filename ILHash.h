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

/**
 A hash function returns a hash (a 64-bit long integer) for the given value. The hash function must return the same values for certain -- possibly differing -- arguments; see ILEqualsFunction and ILValueCorrespondsToKeyFunction for more information. */
typedef uint64_t (*ILHashFunction)(void* value);

/**
 This function compares two values and returns true if they're logically the same, false otherwise. They need not be identical (that is, two values can be equal even if value != otherValue), but a hash function for two logically equal values must return the same hash.
 */
typedef bool (*ILEqualsFunction)(void* value, void* otherValue);

/**
 This function checks if this value corresponds to a given key (see ILHash for more information on values and keys). In a ILHash, the hashing function for values (set via ILHash::setHashForValue()) must return the same value as the hashing function for keys (set via ILHash::setHashForKey()) for values and keys this function returns true for.
 */
typedef bool (*ILValueCorrespondsToKeyFunction)(void* value, void* key);

/**
 A ILHash (or just hash) is a facet implementing an hashtable for generic pointer-sized values. The hash stores a number of pointer-sized items (called 'values'), and allows you to retrieve them, test their containment by the hashtable, and remove them if present; it also allows you to use a different pointer-sized value (called a 'key') to retrieve and perform editing on a value already inserted in the hash.
 
 The hash does not dereference the value and key pointers itself; it relies on manipulation functions you provide. Additionally, the hash only stores value pointers; you are expected to provide and/or store the key pointers yourself (perhaps as part of the value's pointed-to memory location).
 
 The hash requires the hash for a value to remain constant over time for the result of all its addition, testing and removal methods to conform to the given contracts. However, it guarantees that the #getAllValues() method will always perform correctly even in the face of hash changes.
 */
class ILHash {
public:
	/** Creates a new hash with a system-determined number of buckets. */
	ILHash();
	
	/** Creates a new hash with the given number of buckets. */
	ILHash(size_t buckets);
	~ILHash();
	
	/** Adds a value to the hash. This operation executes in constant time. The value will be retained with the retain function set via #setRetain() upon insertion, if any. */
	void addValue(void* value);
	
	/** Returns true if the given value has been inserted in the hash, false otherwise. This operation executes in near-constant time. */
	bool containsValue(void* value);
	
	/** Removes the given value if it was inserted in the hash. This operation executes in near-constant time. The value will be released with the release function set via #setRelease() upon insertion, if any. */
	void removeValue(void* value);
	
	/** Removes the value associated with the given key (just like #removeValue()). To use this method, you must set functions with the #setHashForKey(), #setValueCorrespondsToKey() and #setEquals() functions. */
	void removeValueForKey(void* key);

	/** Returns the value corresponding to the given key. This operation executes in near-constant time. To use this method, you must set functions with the #setHashForKey(), #setValueCorrespondsToKey() and #setEquals() functions. */
	void* valueForKey(void* key);

	/** Returns true if the hash contains a value for the given key. This operation executes in near-constant time. To use this method, you must set functions with the #setHashForKey(), #setValueCorrespondsToKey() and #setEquals() functions. */
	bool containsValueForKey(void* key);
	
	/** This function will be used to produce hashes for the values. If NULL, a hash will be produced by using the value pointer as an integer (without dereferencing it). */
	void setHashForValue(ILHashFunction h);
	/** This function will be used to produce hashes for the keys; the hash for a key must be equal to the hash for the corresponding value. If NULL, a hash will be produced by using the key pointer as an integer (without dereferencing it). */
	void setHashForKey(ILHashFunction h);
	/** This function must return true if a value corresponds to a given key. If NULL, a value will be considered to correspond to a key if their pointer values are equal (without dereferencing them). */
	void setValueCorrespondsToKey(ILValueCorrespondsToKeyFunction h);
	
	/** This function will be called upon all values that are stored into the hash. It will be called only once per value, and will be paired with a later call to the release function. If NULL, no function will be called. */
	void setRetain(ILRetainFunction h);
	
	/** This function will be called upon all values the hash stops storing into itself. If NULL, no function will be called. */
	void setRelease(ILReleaseFunction h);

	/** This function must return true if two values are logically equal. If NULL, a value will be considered to be logically equal to another value if their pointer values are equal (without dereferencing them). */	
	void setEquals(ILEqualsFunction h);
	
	/** Returns the number of values stored in this hash. This method executes in constant time. */
	size_t count();
	
	/** Obtains the values of this hash as a C array of pointers. This function executes in slightly-higher-than-linear time.
	 @param values A C array of values at least #count() items long. On return, the indexes between 0 and #count() - 1 will contain this hash's values. */
	void getAllValues(void** values);
	
	/** Obtains a particular bucket's first position. You should not call this method unless you need to implement fast iteration or similar algorithm; for general use, call #getAllValues() instead.
	 
		@param i The index of the bucket, a number between 0 and #bucketsCount() - 1.
	 */
	ILLinkedListPosition* beginningOfBucketAtIndex(size_t i);
	
	/** Returns the number of buckets used by this hash. */
	size_t bucketsCount();

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
