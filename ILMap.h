/*
 *  ILMap.h
 *  Argyle
 *
 *  Created by ∞ on 02/05/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef ILMap_H
#define ILMap_H 1

#include "ILObject.h"
#include "ILHash.h"

class ILMapIterator : public ILObject {
public:
	// either or both can be NULL to ignore.
	virtual bool getNext(ILObject** key, ILObject** value) = 0;
};


/**
 A map associates an object (a 'key') to another (a 'value') and allows you to retrieve the value associated with a key, if any.
 Keys of a map must be copiable and will be copied by the map upon insertion; you don't need to pass the exact same object you passed for the key, so long that the object you pass is equal to the original (as indicated by ILObject::equals()). Values, instead, will be retained.
 */
class ILMap : public ILObject {
public:
	/** Constructs an empty map. */
	ILMap();
	
	/** Adds an entry to the map with the given key and value. The key will be copied, and the value will be retained.
	 If there is already one entry for an equal key in this table (as determined by ILObject::equals()), this method will replace the value already in the map with the new one (releasing the old one in the process). TODO TEST
	 
	 @param key The key. Cannot be NULL.
	 @param value The value. Cannot be NULL.
	 */
	void setValueForKey(ILCopiable* key, ILObject* value);
	
	/** Returns the object for the given key, or NULL if the key isn't associated to any value in this map. */
	ILObject* valueForKey(ILObject* key);
	
	/** Removes the entry for the given key, releasing the associated value in the process. */
	void removeValueForKey(ILObject* key);
	
	/** Returns the number of entries in the table. */
	size_t count();
	
	/** Obtains the contents of this map as two C arrays, one for keys and one for values. The objects returned in the keys array will be the keys associated with the objects in the same positions in the values array (for example, keys[2] will be the key associated with values[2]).
	 
	 @param keys A C array at least ILMap::count() items long. On return, the indexes between 0 and ILMap::count() - 1 will contain this map's keys.
	 @param values A C array at least ILMap::count() items long. On return, the indexes between 0 and ILMap::count() - 1 will contain this map's values.
	 */
	void getContent(ILObject** keys, ILObject** values);
	
	ILMapIterator* iterate();
	
private:
	ILHash _h;
	void initialize();
};

#endif // #ifndef ILMap_H
