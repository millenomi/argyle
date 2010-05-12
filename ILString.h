/*
 *  ILString.h
 *  Argyle
 *
 *  Created by ∞ on 12/05/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef ILString_H
#define ILString_H 1

#include "ILObject.h"
#include "ILData.h"

typedef enum {
	kILStringEncodingUTF8 = 0,
} ILStringEncoding;

class ILString {
public:
	ILString(ILData* d, ILStringEncoding encoding);
	ILString(char* buffer, ILStringEncoding encoding);
	~ILString();
	
	ILData* dataUsingEncoding(ILStringEncoding encoding);
	char* nullTerminatedStringUsingEncoding(ILStringEncoding encoding);
	
private:
	ILData* _utf8data;
};

#endif // #ifndef ILString_H