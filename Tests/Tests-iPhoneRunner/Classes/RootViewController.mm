//
//  RootViewController.m
//  Tests-iPhoneRunner
//
//  Created by ∞ on 19/05/10.
//  Copyright __MyCompanyName__ 2010. All rights reserved.
//

#import "RootViewController.h"

#include "ILTesting.h"
using namespace ILTest;

#include "ILPlatformCoreTests.h"

@interface ILTestResult : NSObject
{
	NSString* description;
	NSString* testCase;
	BOOL passed;
}

@property(nonatomic, copy) NSString* description, * testCase;
@property(nonatomic) BOOL passed;

@end

@implementation ILTestResult

- (void) dealloc
{
	[description release];
	[testCase release];
	[super dealloc];
}

@synthesize description, testCase, passed;

@end

#pragma mark C++ bridging

@interface RootViewController ()

- (void) test:(const char*) description passed:(BOOL) passed;

@end


class ILTestViewControllerResults : public Results {
	RootViewController* _vc;
	
public:
	ILTestViewControllerResults(RootViewController* vc) {
		_vc = [vc retain];
	}
	
	~ILTestViewControllerResults() {
		[_vc release];
	}
	
	virtual void didBeginTestCase(TestCase* c, const char* what) {
		_vc.currentlyExecutingTestCaseName = [NSString stringWithFormat:@"%s (%s)", c->name(), what];
	}
	
	virtual void passed(TestCase* c, const char* description) {
		[_vc test:description passed:YES];
	}
	
	virtual void failed(TestCase* c, const char* description) {
		[_vc test:description passed:NO];
	}
};

#pragma mark The VC

@implementation RootViewController


#pragma mark -
#pragma mark View lifecycle

- (id) initWithStyle:(UITableViewStyle)style;
{
	if ((self = [super initWithStyle:style]))
		results = [NSMutableArray new];
	
	return self;
}

- (id) initWithCoder:(NSCoder*) c;
{
	if ((self = [super initWithCoder:c]))
		results = [NSMutableArray new];
	
	return self;
}

- (id) initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil;
{
	if ((self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil]))
		results = [NSMutableArray new];
	
	return self;
}

- (void) dealloc
{
	[results release];
	[super dealloc];
}

@synthesize currentlyExecutingTestCaseName;

#pragma mark -
#pragma mark Table view data source

// Customize the number of sections in the table view.
- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView {
    return 1;
}


// Customize the number of rows in the table view.
- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    return [results count];
}


// Customize the appearance of table view cells.
- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    
    static NSString *CellIdentifier = @"Cell";
    
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:CellIdentifier];
    if (cell == nil) {
        cell = [[[UITableViewCell alloc] initWithStyle:UITableViewCellStyleSubtitle reuseIdentifier:CellIdentifier] autorelease];
    }

    
	ILTestResult* result = [results objectAtIndex:[indexPath row]];
	
	NSString* mark = result.passed? @"\u2713" : @"\u2717";
	
	cell.textLabel.text = [NSString stringWithFormat:@"%@ %@", mark, result.description];
	cell.detailTextLabel.text = result.testCase;
	cell.textLabel.textColor = result.passed? [UIColor blackColor] : [UIColor redColor];
	
    return cell;
}

#pragma mark Running the tests

- (IBAction) play;
{
	if (running)
		return;
	
	running = YES;
	
	[results removeAllObjects];
	[self.tableView reloadData];
	
	[NSThread detachNewThreadSelector:@selector(runInBackgroundThread) toTarget:self withObject:nil];
}

- (void) doneRunning;
{
	running = NO;
}

- (void) runInBackgroundThread;
{
	NSAutoreleasePool* pool = [NSAutoreleasePool new];
	
	{
		ILReleasePool corePool;

		ILTestViewControllerResults* r = new ILTestViewControllerResults(self);
		ILPlatformCoreRunAllTestCases(r);
		
		[self performSelectorOnMainThread:@selector(doneRunning) withObject:nil waitUntilDone:YES];
	}	

	[pool release];
}

- (void) test:(const char*) description passed:(BOOL) passed;
{
	ILTestResult* tr = [[ILTestResult new] autorelease];
	tr.testCase = self.currentlyExecutingTestCaseName;
	tr.passed = passed;
	tr.description = [NSString stringWithUTF8String:description];
	
	[self performSelectorOnMainThread:@selector(addResult:) withObject:tr waitUntilDone:NO];
}

- (void) addResult:(ILTestResult*) tr {
	[results addObject:tr];
	
	NSIndexPath* ip = [NSIndexPath indexPathForRow:[results count] - 1 inSection:0];
	[self.tableView insertRowsAtIndexPaths:[NSArray arrayWithObject:ip] withRowAnimation:UITableViewRowAnimationTop];
	
	[NSObject cancelPreviousPerformRequestsWithTarget:self selector:@selector(scrollToBottom) object:nil];
	[self performSelector:@selector(scrollToBottom) withObject:nil afterDelay:1.0];
}

- (void) scrollToBottom;
{
	NSIndexPath* ip = [NSIndexPath indexPathForRow:[results count] - 1 inSection:0];
	[self.tableView scrollToRowAtIndexPath:ip atScrollPosition:UITableViewScrollPositionBottom animated:YES];
	[self.tableView performSelector:@selector(flashScrollIndicators) withObject:nil afterDelay:0.5];
}

#pragma mark Examining results

- (void) tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath;
{
	ILTestResult* result = [results objectAtIndex:[indexPath row]];
	UIAlertView* av = [[UIAlertView new] autorelease];
	
	av.title = [NSString stringWithFormat:@"%@ in %@.", result.passed? @"Passed" : @"Failed", result.testCase];
	av.message = result.description;
	[av addButtonWithTitle:@"Dismiss"];
	[av show];
	
	[self.tableView deselectRowAtIndexPath:indexPath animated:YES];
}

@end

