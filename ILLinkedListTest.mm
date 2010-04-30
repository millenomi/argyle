//
//  ILLinkedListTest.mm
//  Argyle
//
//  Created by ∞ on 30/04/10.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

#import "ILLinkedListTest.h"


@implementation ILLinkedListTest

- (void) testCreation;
{
	ILLinkedList l;
	
	STAssertTrue(l.count() == 0, @"No items");
	STAssertTrue(l.beginning() == NULL, @"No starting position");
	STAssertTrue(l.end() == NULL, @"No ending position");	
}

struct Something {
	Something() {
		isRetained = false;
	}
	
	bool isRetained;
};

static Something* SomethingRetain(Something* s) {
	s->isRetained = true;
	return s;
}

static void SomethingRelease(Something* s) {
	s->isRetained = false;
}

- (void) testRetainRelease;
{
	ILLinkedList l;
	
	l.setRetain((ILRetainFunction) &SomethingRetain);
	l.setRelease((ILReleaseFunction) &SomethingRelease);
	
	Something a, b;
	STAssertFalse(a.isRetained, @"Not before insertion");
	STAssertFalse(b.isRetained, @"Not before insertion");
	
	l.insertAtEnd(&a);
	l.insertAtEnd(&b);
	
	STAssertTrue(a.isRetained, @"Retained by insertion");
	STAssertTrue(b.isRetained, @"Retained by insertion");
	
	l.remove(l.end());
	STAssertTrue(a.isRetained, @"Untouched");
	STAssertFalse(b.isRetained, @"Released by removal");
	
	l.remove(l.beginning());
	STAssertFalse(a.isRetained, @"Released by removal");
}

- (void) testInsertAtEnd;
{
	ILLinkedList l;
	int a, b, c;
	
	l.insertAtEnd(&a);
	STAssertTrue(l.count() == 1, @"One");
	void* values[1];
	l.getAllValues(values);
	STAssertTrue(values[0] == &a, @"It's a");
	
	l.insertAtEnd(&b);
	STAssertTrue(l.count() == 2, @"Two");
	void* values2[2];
	l.getAllValues(values2);
	STAssertTrue(values2[0] == &a, @"It's a");
	STAssertTrue(values2[1] == &b, @"It's b");

	l.insertAtEnd(&c);
	STAssertTrue(l.count() == 3, @"Three");
	void* values3[3];
	l.getAllValues(values3);
	STAssertTrue(values3[0] == &a, @"It's a");
	STAssertTrue(values3[1] == &b, @"It's b");	
	STAssertTrue(values3[2] == &c, @"It's c");
}

- (void) testRemove;
{
	ILLinkedList l;
	int a, b, c, d;
	
	l.insertAtEnd(&a);
	l.insertAtEnd(&b);
	l.insertAtEnd(&c);
	l.insertAtEnd(&d);
	
	l.remove(l.beginning()->next());
	
	STAssertTrue(l.count() == 3, @"Count of list is three after one removal");
	void* one[3];
	l.getAllValues(one);
	STAssertTrue(one[0] == &a, @"a is still there");
	STAssertTrue(one[1] == &c, @"c is still there");
	STAssertTrue(one[2] == &d, @"d is still there");
	
	l.remove(l.end());
	
	STAssertTrue(l.count() == 2, @"Count of list is three after two removals");
	void* two[2];
	l.getAllValues(two);
	STAssertTrue(two[0] == &a, @"a is still there");
	STAssertTrue(two[1] == &c, @"c is still there");
	
	
	l.remove(l.beginning());
	
	STAssertTrue(l.count() == 1, @"Count of list is one after three removals");
	void* three[1];
	l.getAllValues(three);
	STAssertTrue(three[0] == &c, @"c is still there");
	
	l.remove(l.beginning());
	
	STAssertTrue(l.count() == 0, @"Count of list is zero after four removals");
	STAssertTrue(l.beginning() == NULL, @"No beginning");
	STAssertTrue(l.end() == NULL, @"No end");
}

- (void) testInsertions;
{
	ILLinkedList l;
	int a, b, c, d;
	
	// insertAtBeginning a
	
	l.insertAtBeginning(&a);
	STAssertTrue(l.count() == 1, @"One addition");
	void* one[1];
	l.getAllValues(one);
	STAssertTrue(one[0] == &a, @"a is there");
	
	STAssertTrue(l.beginning()->get() == &a, @"a is the head");
	STAssertTrue(l.end()->get() == &a, @"a is the tail");
	
	// insertAfterPosition head, b
	
	l.insertAfterPosition(l.beginning(), &b);
	STAssertTrue(l.count() == 2, @"Two additions");
	void* two[2];
	l.getAllValues(two);
	STAssertTrue(two[0] == &a, @"a is there");
	STAssertTrue(two[1] == &b, @"b is there");
	
	STAssertTrue(l.beginning()->get() == &a, @"a is the head");
	STAssertTrue(l.end()->get() == &b, @"b is the tail");
	
	// insertBeforePosition end, c
	
	l.insertBeforePosition(l.end(), &c);
	STAssertTrue(l.count() == 3, @"Three additions");
	void* three[3];
	l.getAllValues(three);
	STAssertTrue(three[0] == &a, @"a is there");
	STAssertTrue(three[1] == &c, @"c is there");
	STAssertTrue(three[2] == &b, @"b is there");
	
	STAssertTrue(l.beginning()->get() == &a, @"a is the head");
	STAssertTrue(l.end()->get() == &b, @"b is the tail");
	
	// insertAtEnd d
	
	l.insertAtEnd(&d);
	STAssertTrue(l.count() == 4, @"Four additions");
	void* four[4];
	l.getAllValues(four);
	STAssertTrue(four[0] == &a, @"a is there");
	STAssertTrue(four[1] == &c, @"c is there");
	STAssertTrue(four[2] == &b, @"b is there");
	STAssertTrue(four[3] == &d, @"d is there");
	
	STAssertTrue(l.beginning()->get() == &a, @"a is the head");
	STAssertTrue(l.end()->get() == &d, @"d is the tail");
	
}

@end
