//
//  ILMessageHubTest.mm
//  Argyle
//
//  Created by ∞ on 11/05/10.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

#import "ILMessageHubTest.h"

static int ILMessageHubTestSomeInt = 0;
static void* ILMessageHubTestMessageKind = &ILMessageHubTestSomeInt;

class ILMessageHubTestReceiver : public ILTarget {
public:
	bool received;
	
	ILMessageHubTestReceiver() : ILTarget() {
		received = false;
	}
	
	virtual void deliverMessage(ILMessage* m) {
		received =
			(m->kind() == ILMessageHubTestMessageKind) &&
			(m->payload() != NULL) &&
			(m->payload()->equals(new ILNumber(42)));
	}
};

@implementation ILMessageHubTest

- (void) testDeliveryToTestReceiver {
	ILReleasePool pool;
	
	ILMessageHubTestReceiver* r = new ILMessageHubTestReceiver();
	STAssertFalse(r->received, @"Message not yet received");
	
	ILMessage* m = new ILMessage(ILMessageHubTestMessageKind, r, new ILNumber(42));
	
	r->deliverMessage(m);
	
	STAssertTrue(r->received, @"Message correctly received");
}

- (void) testDeliveryViaHub {
	ILReleasePool pool;
	
	ILMessageHubTestReceiver* r = new ILMessageHubTestReceiver(),
		* r2 = new ILMessageHubTestReceiver();
	
	STAssertFalse(r->received, @"Message not yet received");
	STAssertFalse(r2->received, @"Message not yet received");
	
	ILMessage* m = new ILMessage(ILMessageHubTestMessageKind, r, new ILNumber(42));

	ILMessageHub* hub = new ILMessageHub();
	
	hub->addTargetForMessagesOfType(r, ILMessageHubTestMessageKind, r);
	hub->addTargetForMessagesOfType(r2, ILMessageHubTestMessageKind, NULL);
	hub->deliverMessage(m);
	
	STAssertTrue(r->received, @"Message correctly received");
	STAssertTrue(r2->received, @"Message correctly received");
}

@end
