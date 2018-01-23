[![Version](https://img.shields.io/cocoapods/v/Record360SDK.svg?style=flat)](http://cocoapods.org/pods/Record360SDK)

Record360 iOS SDK
==================

Last updated on – 06/30/2017

# Introduction

The Record360SDK.framework is a Cocoa framework that allows mobile clients to leverage [Record360](https://www.record360.com).  This allows the client to track and record the condition of assets using the Record360 workflow.  An account with Record360 is required.  Please contact sales@record360.com for details.

# Requirements

-   iOS 9.0 or later
-   iPhone 4S and above.
-   iPad 3 and above.
-   iPad mini.
-   iPod Touch 5G and above.

# Example

To run the example project, clone the repo, and run `pod install` from the Example directory.

# Installation with CocoaPods

Record360 SDK can be installed using CocoaPods. CocoaPods is a dependency manager that automates and simplifies the process of integrating 3rd-party libraries into your projects.  If you do not have CocoaPods, please see [CocoaPods](http://cocoapods.org) for details on how to install it.

### Podfile

Create a Podfile in your Xcode project directory with the following lines.
    
    platform :ios, '9.0'
    use_frameworks!
    
    pod 'Record360SDK', '~> 0.9' 

From the command line execute `pod install` to add the Record360SDK.

# Installation without CocoaPods

Record360 can provide the framework, contact support@record360.com for more information.

# Integrating Record360

### Starting the transaction upload handling process

Initialize a Record360 object and set its delegate.
    
    #import <Record360SDK/Record360.h>
    
    @interface MyApplicationHandler : NSObject <Record360Delegate>

    - (void)viewDidLoad {
    	[super viewDidLoad];

    	Record360 *record360 = [[Record360 alloc] initWithDelegate:self];
    }

### Entering the workflow

There are six ways to start the workflow.  See the below header for the Record360ViewController:

    + (Record360ViewController *)loadControllerLoginAndSendTo:(Record360 *)record360 displayOn:(UIViewController *)rootViewController showCancelButton:(BOOL)showCancel;
    
    + (Record360ViewController *)loadControllerWithUserName:(NSString *)userName andPassword:(NSString *)password sendTo:(Record360 *)record360 displayOn:(UIViewController *)rootViewController;
    
    + (Record360ViewController *)loadControllerWithUserToken:(NSString *)userToken andUserId:(NSString *)userId sendTo:(Record360 *)record360 displayOn:(UIViewController *)rootViewController;
    
    + (Record360ViewController *)loadControllerLoginAndSendTo:(Record360 *)record360 withReferenceNumber:(NSString *)referenceNumber displayOn:(UIViewController *)rootViewController showCancelButton:(BOOL)showCancel;
    
    + (Record360ViewController *)loadControllerWithUserToken:(NSString *)userToken andUserId:(NSString *)userId andReferenceNumber:(NSString *)referenceNumber sendTo:(Record360 *)record360 displayOn:(UIViewController *)rootViewController;
    
    + (Record360ViewController *)loadControllerWithUserName:(NSString *)userName andPassword:(NSString *)password andReferenceNumber:(NSString *)referenceNumber sendTo:(Record360 *)record360 displayOn:(UIViewController *)rootViewController;

Entry points that begin with **loadControllerLoginAndSendTo** start the workflow with a provided login UI where the user can input their user name and password.  The other entry points authenticate and enter directly into the workflow.  Login credentials can be created through the Record360 API or by contacting support@record360.com.

Initialize a Record360 object and pass it into a Record360ViewController factory method.

    #import <Record360SDK/Record360ViewController.h>
    
    @interface MyApplicationHandler : NSObject <Record360Delegate, Record360ViewControllerDelegate>

    - (void)viewDidLoad {
    	[super viewDidLoad];

    	Record360 *record360 = [[Record360 alloc] initWithDelegate:self];

    	Record360ViewController *record360ViewController = [Record360ViewController loadControllerWithUserName:@"testuser@record360.com" andPassword:@"P@ssword!" sendTo:record360 displayOn:self];
    	record360ViewController.delegate = self;
    }

Depending on the state of the transaction in the workflow, the user will either be prompted to create a new transaction or resume their already existing transaction.

### Adding workflow settings
	
	  [record360ViewController applyDefaultSettings:@[
	                      [[Record360Setting alloc] initSwitchSetting:SETTING_NOTATIONS_ON_IMAGES canDisplay:NO value:NO],
	                      [[Record360Setting alloc] initSwitchSetting:SETTING_VIN_SCAN canDisplay:YES value:NO],
	                      [[Record360Setting alloc] initSwitchSetting:SETTING_NATIVE_PHOTO_MODE canDisplay:NO value:NO],
	                      [[Record360Setting alloc] initOptionSetting:SETTING_RESOLUTION canDisplay:YES value:RESOLUTION_MEDIUM],
	                      [[Record360Setting alloc] initOptionSetting:SETTING_UPLOAD_MODE canDisplay:YES value:UPLOAD_MODE_ONLINE],
	                      [[Record360Setting alloc] initSetting:SETTING_SEND_SUPPORT_LOG],
	                      [[Record360Setting alloc] initSetting:SETTING_LOGOUT],
	                      [[Record360Setting alloc] initSetting:SETTING_RATE_RECORD360],
	                      [[Record360Setting alloc] initSetting:SETTING_LINKS label:@"Privacy" link:@"https://app.record360.com/privacy.html"],
	                      [[Record360Setting alloc] initSetting:SETTING_VERSION]
	                  ]];

### Responding to workflow events

Implement the below Record360ViewControllerDelegate protocol to respond to workflow events:
	
	@protocol Record360ViewControllerDelegate <NSObject>

	- (void)onTransactionComplete;
	- (void)onTransactionCanceled;

	@optional
	- (void)onReferenceNumberEntered:(NSString *)referenceNumber completion:(void (^)(void))completion;
	- (void)onSuccessfulAuthenticationWithToken:(NSString *)userToken andUserId:(NSString *)userId;
	- (void)onFailedAuthentication:(NSError *)error;

	@end

Any object set up as the delegate of the Record360ViewController object will receive these delegate callbacks that represent the different events that occur during the workflow.

### Responding to transaction upload events

Implement the below Record360Delegate protocol to respond to transaction upload events:

	@protocol Record360Delegate <NSObject>

	- (void)onTransactionUploadedForReferenceNumber:(NSString *)referenceNumber;
	- (void)onTransactionUploadFailedForReferenceNumber:(NSString *)referenceNumber withError:(NSError *)error;
	- (void)onTransactionUploadDeletedForReferenceNumber:(NSString *)referenceNumber;

	@optional
	- (void)onUploadBytesComplete:(long long)bytesComplete ofTotal:(long long)bytesTotal forReferenceNumber:(NSString *)referenceNumber;

	@end

Any object set up as the delegate of the Record360 object will receive these delegate callbacks that represent the different events that occur while a transaction is uploading.

Please see the detailed instructions in our [SDK documentation](https://github.com/Record360/ios/blob/readme/SDK.pdf)

# License

See the LICENSE file for more info on the Record360SDK license.
