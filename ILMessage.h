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

/**
 A message is a single item of information about an event that occurred in an application. A message has a kind (an unique pointer value that is not dereferenced), retains its optional source object and copies an optional copiable payload.
 */
class ILMessage : public ILObject {
public:
	/** Creates a new message with specified kind, source and payload. The payload will be copied.  */
	ILMessage(void* kind, ILObject* source, ILCopiable* payload);
	~ILMessage();
	
	/** Returns the kind of this message. */
	void* kind();
	/** Returns the source object for this message. It may be NULL. */
	ILObject* source();
	/** Returns the payload for this message. */
	ILObject* payload();
	
private:
	void* _kind;
	ILObject* _source;
	ILObject* _payload;
};

/** A target is an object that is able to receive ILMessage objects (messages). */
class ILTarget : public ILObject {
public:
	/** Delivers the message to this target. The message may be processed synchronously or asynchronously. */
	virtual void deliverMessage(ILMessage* m) = 0;
};

/** The signature for a function that can be called by a ILFunctionTarget.
 @param m The message to receive.
 @param contest The context value passed to ILFunctionTarget::ILFunctionTarget() at creation time.
 */
typedef void (*ILTargetFunction)(ILMessage* m, void* context);

/** A target that delivers a message by calling a function synchronously. */
class ILFunctionTarget : public ILTarget {
public:
	/** Creates a target that delivers messages to the given function. The context parameter will not be dereferenced and will be passed with all invocations of that function. */
	ILFunctionTarget(ILTargetFunction f, void* context);
	
	/** Delivers the message by calling the associated function with this message and the context parameter passed at creation time. */
	virtual void deliverMessage(ILMessage* m);
	
private:
	ILTargetFunction _function;
	void* _context;
};

/** A target that delivers a message by calling a method on an object. This class is virtual; you create implementations for particular methods by using the @link ILTargetForMethod ILTargetForMethod macro. */
class ILObjectTarget : public ILTarget {
public:
	ILObjectTarget(ILObject* o);
	~ILObjectTarget();
	
	virtual ILObject* target();
	virtual void deliverMessage(ILMessage* m) = 0;
	
private:
	ILObject* _target;
};	

/** Creates a new subclass of ILObjectTarget that delivers messages by calling the given method of objects of the given class.
 
 @param targetClass The name of the ILObjectTarget subclass to create.
 @param receiverClass The name of the class whose instances will receive messages.
 @param method The name of the method that will receive the messages. The method must be public. Use the following signature: <code>void someMethodName(ILMessage* m)</code>.
 */
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
