/*
 *  ILString.cpp
 *  Argyle
 *
 *  Created by ∞ on 12/05/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "ILString.h"
#include <string.h>

ILString::ILString(ILData* d, ILStringEncoding encoding) {
	_utf8data = ILRetain(d);
}

ILString::ILString(char* buffer, ILStringEncoding encoding) {
	ILData* d = new ILData((uint8_t*) buffer, strlen(buffer));
	_utf8data = ILRetain(d);
}

ILString::~ILString() {
	ILRelease(_utf8data);
}

ILData* ILString::dataUsingEncoding(ILStringEncoding encoding) {
	return _utf8data;
}

char* ILString::nullTerminatedStringUsingEncoding(ILStringEncoding encoding) {
	ILData* d = _utf8data->copy();
	
	uint8_t nullByte = 0;
	
	d->appendBytes(&nullByte, 1);
	
	return (char*) d->bytes();
}
