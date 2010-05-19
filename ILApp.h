/*
 *  ILApp.h
 *  Argyle
 *
 *  Created by ∞ on 19/05/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef ILApp_H
#define ILApp_H 1

class ILApp {
private:
	static ILApp* _current;
	
public:
	static ILApp* current();
	
	ILApp(int argc, const char** argv);
	
	int end(int result = 0);
};

#endif // #ifndef ILApp_H
