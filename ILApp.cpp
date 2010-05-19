/*
 *  ILApp.cpp
 *  Argyle
 *
 *  Created by ∞ on 19/05/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "ILApp.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

ILApp* ILApp::_current = NULL;

ILApp::ILApp(int argc, const char** argv) {
	if (_current)
		abort();
	
	_current = this;
}

ILApp* ILApp::current() {
	return _current;
}

int ILApp::end(int result) {
	fflush(stdout);
	fflush(stderr);
	_exit(result);
	return result;
}
