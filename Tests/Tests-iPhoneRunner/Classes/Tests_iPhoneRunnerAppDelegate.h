//
//  Tests_iPhoneRunnerAppDelegate.h
//  Tests-iPhoneRunner
//
//  Created by ∞ on 19/05/10.
//  Copyright __MyCompanyName__ 2010. All rights reserved.
//

#import <UIKit/UIKit.h>

#import "RootViewController.h"

@interface Tests_iPhoneRunnerAppDelegate : NSObject <UIApplicationDelegate> {
    
    UIWindow *window;
    UINavigationController *navigationController;
	
	IBOutlet RootViewController* root;
}

@property (nonatomic, retain) IBOutlet UIWindow *window;
@property (nonatomic, retain) IBOutlet UINavigationController *navigationController;

@end

