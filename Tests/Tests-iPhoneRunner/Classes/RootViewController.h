//
//  RootViewController.h
//  Tests-iPhoneRunner
//
//  Created by ∞ on 19/05/10.
//  Copyright __MyCompanyName__ 2010. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface RootViewController : UITableViewController {
	NSMutableArray* results;
	
	NSString* currentlyExecutingTestCaseName;
	
	BOOL running;
}

@property(/* atomic, */ copy) NSString* currentlyExecutingTestCaseName;

- (IBAction) play;

@end
