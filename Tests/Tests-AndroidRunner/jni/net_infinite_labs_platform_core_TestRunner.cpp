/*
 *  net_infinite_labs_platform_core_TestRunner.cpp
 *  JNI
 *
 *  Created by ∞ on 19/05/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */


#include "net_infinite_labs_platform_core_TestRunner.h"

#include "Argyle.h"
#include "ILTesting.h"
#include "ILPlatformCoreTests.h"

using namespace ILTest;

class ILResultsJavaCallout : public Results {
	jobject _self;
	JNIEnv* _env;
	
public:
	ILResultsJavaCallout(JNIEnv* env, jobject self) {
		_env = env;
		_self = self;
	}
	
	virtual void didBeginTestCase(TestCase* c, const char* what) {
		jclass selfClass = _env->GetObjectClass(_self);
		if (!selfClass)
			return;
		
		jmethodID method = _env->GetMethodID(selfClass, "didBeginTestCase", "(Ljava/lang/String;Ljava/lang/String;)V");
		if (!method)
			return;
		
		jstring nameJ = _env->NewStringUTF(c->name());
		jstring whatJ = _env->NewStringUTF(what);
		
		_env->CallVoidMethod(_self, method, nameJ, whatJ);
	}
	
	virtual void passed(TestCase* c, const char* description) {
		jclass selfClass = _env->GetObjectClass(_self);
		if (!selfClass)
			return;
		
		jmethodID method = _env->GetMethodID(selfClass, "passed", "(Ljava/lang/String;)V");
		if (!method)
			return;
		
		jstring descriptionJ = _env->NewStringUTF(description);
		
		_env->CallVoidMethod(_self, method, descriptionJ);
	}
	
	virtual void failed(TestCase* c, const char* description) {
		jclass selfClass = _env->GetObjectClass(_self);
		if (!selfClass)
			return;
		
		jmethodID method = _env->GetMethodID(selfClass, "failed", "(Ljava/lang/String;)V");
		if (!method)
			return;
		
		jstring descriptionJ = _env->NewStringUTF(description);
		
		_env->CallVoidMethod(_self, method, descriptionJ);		
	}
};	


JNIEXPORT void JNICALL Java_net_infinite_1labs_platform_1core_TestRunner_nativeRunTests
(JNIEnv* env, jobject self) {
	ILReleasePool pool;
	
	ILResultsJavaCallout* callout = new ILResultsJavaCallout(env, self);
	ILPlatformCoreRunAllTestCases(callout);
}
