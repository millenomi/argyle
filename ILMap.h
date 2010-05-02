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

class ILMap : public ILObject {
public:
	ILMap();
	
	void setValueForKey(ILCopiable* key, ILObject* value);
	ILObject* valueForKey(ILObject* key);
	void removeValueForKey(ILObject* key);
	
	size_t count();
	
	// keys[i] is the key for values[i].
	void getContent(ILObject** keys, ILObject** values);
	
private:
	ILHash _h;
	void initialize();
};

#endif // #ifndef ILMap_H
