/*
 *  ILMessage.h
 *  Argyle
 *
 *  Created by ∞ on 05/05/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef ILMessage_H
#define ILMessage_H 1

#include "Argyle.h"

class ILMessage : public ILObject {
public:
	ILMessage(void* kind, ILObject* source, ILCopiable* payload);
	~ILMessage();
	
	void* kind();
	ILObject* source();
	ILObject* payload();
	
private:
	void* _kind;
	ILObject* _source;
	ILObject* _payload;
};

class ILTarget : public ILObject {
public:
	virtual void deliverMessage(ILMessage* m) = 0;
};

typedef void (*ILTargetFunction)(ILMessage* m, void* context);

class ILFunctionTarget : public ILTarget {
public:
	ILFunctionTarget(ILTargetFunction f, void* context);
	virtual void deliverMessage(ILMessage* m);
	
private:
	ILTargetFunction _function;
	void* _context;
};

class ILObjectTarget : public ILTarget {
public:
	ILObjectTarget(ILObject* o);
	~ILObjectTarget();
	
	virtual ILObject* target();
	virtual void deliverMessage(ILMessage* m) = 0;
	
private:
	ILObject* _target;
};	

#define ILTargetForMethod(targetClass, receiverClass, method) \
	class targetClass : public ILObjectTarget { \
	public: \
		targetClass(receiverClass* me) : ILObjectTarget(me) {} \
		virtual void deliverMessage(ILMessage* m) { ((receiverClass*)this->target())->method(m); } \
	}

// Example of use:
/*
 
 ILTargetForMethod(SomeClassTarget, SomeClass, doSomethingWithMessage);
 // later
 {
	...
	someComponent->setTarget(new SomeClassTarget(this));
	...
 }
 
 void doSomethingWithMessage(ILMessage* m) { ... }
*/

//class SomeClass : public ILObject {
//public:
//	virtual void someMethod(ILMessage* m) = 0;
//};
//
//ILTargetForMethod(SomeClassTarget, SomeClass, someMethod);
//
//static void tester(SomeClass* x, ILMessage* y) {
//	(new SomeClassTarget(x))->deliverMessage(y);
//}

#endif // #ifndef ILMessage_H
