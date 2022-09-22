[![Version](https://img.shields.io/cocoapods/v/Record360SDK.svg?style=flat)](http://cocoapods.org/pods/Record360SDK)

Record360 iOS SDK
==================

Last updated on – 09/22/2022

# Introduction

The Record360SDK.framework is a Cocoa framework that allows mobile clients to leverage [Record360](https://www.record360.com).  This allows the client to track and record the condition of assets using the Record360 workflow.  An account with Record360 is required.  Please contact sales@record360.com for details.

# Requirements

-   iOS 12.0 or later
-   iPhone 8 and above.
-   iPad 4 and above.
-   iPad mini 2 and above.
-   iPod Touch 6G and above.

# Example

To run the example project, clone the repo, and run `pod install` from the Example directory.

# Installation with CocoaPods

Record360 SDK can be installed using CocoaPods. CocoaPods is a dependency manager that automates and simplifies the process of integrating 3rd-party libraries into your projects.  If you do not have CocoaPods, please see [CocoaPods](http://cocoapods.org) for details on how to install it.

### Podfile

Create a Podfile in your Xcode project directory with the following lines.
    
    platform :ios, '12.0'
    use_frameworks!
    
    pod 'Record360SDK', '~> 4.9.5' 

From the command line execute `pod install` to add the Record360SDK.

# Installation without CocoaPods

Record360 can provide the framework, contact support@record360.com for more information.

# Integrating Record360

### Starting the inspection upload handling process

Initialize a Record360 object and set its delegate.
    
    #import <Record360SDK/Record360.h>
    
    @interface MyApplicationViewController () <Record360Delegate>

    @property (nonatomic) Record360 *record360;

    @end

    @implementation

    - (void)viewDidLoad {
      [super viewDidLoad];

      self.record360 = [[Record360 alloc] initWithDelegate:self];
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
    
    #import <Record360SDK/Record360.h>
    #import <Record360SDK/Record360ViewController.h>
    
    @interface MyApplicationViewController () <Record360Delegate, Record360ViewControllerDelegate>
    
    @property (nonatomic) Record360 *record360;

    @end

    @implementation

    - (void)viewDidLoad {
      [super viewDidLoad];

      self.record360 = [[Record360 alloc] initWithDelegate:self];
    }

    - (IBAction)startInspection:(UIButton *)sender {
      Record360ViewController *record360ViewController = [Record360ViewController loadControllerWithUserName:@"testuser@record360.com" andPassword:@"P@ssword!" sendTo:self.record360 displayOn:self];
      record360ViewController.delegate = self;
    }

Depending on the state of the inspection in the workflow, the user will either be prompted to create a new inspection or resume their already existing inspection.  All entry points are asynchronous.  Any logic that depends on loading the Record360ViewController should be placed in the workflow event callbacks passed to your Record360ViewControllerDelegate object (see below).

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
                        [[Record360Setting alloc] initSetting:SETTING_LINKS label:@"Privacy" link:@"https://www.record360.com/privacy"],
                        [[Record360Setting alloc] initSetting:SETTING_VERSION]
                    ]];

Settings should be applied in one of the workflow event callbacks called on your Record360ViewControllerDelegate object. 

### Responding to workflow events

Implement the below Record360ViewControllerDelegate protocol to respond to workflow events:
  
    @protocol Record360ViewControllerDelegate <NSObject>

    - (void)onInspectionComplete;
    - (void)onInspectionCanceled;

    @optional
    - (void)onReferenceNumberEntered:(NSString *)referenceNumber completion:(void (^)(void))completion;
    - (void)onSuccessfulAuthenticationWithToken:(NSString *)userToken andUserId:(NSString *)userId;
    - (void)onFailedAuthentication:(NSError *)error;

    @end

Any object set up as the delegate of the Record360ViewController object will receive these delegate callbacks that represent the different events that occur during an inspection.

### Responding to inspection upload events

Implement the below Record360Delegate protocol to respond to inspection upload events:

    @protocol Record360Delegate <NSObject>

    - (void)onInspectionUploadedForReferenceNumber:(NSString *)referenceNumber;
    - (void)onInspectionUploadFailedForReferenceNumber:(NSString *)referenceNumber withError:(NSError *)error;
    - (void)onInspectionUploadDeletedForReferenceNumber:(NSString *)referenceNumber;

    @optional
    - (void)onUploadBytesComplete:(long long)bytesComplete ofTotal:(long long)bytesTotal forReferenceNumber:(NSString *)referenceNumber;

    @end

Any object set up as the delegate of the Record360 object will receive these delegate callbacks that represent the different events that occur while an inspection is uploading.

Please see the detailed instructions in our [SDK documentation](https://github.com/Record360/record360-sdk-ios/blob/master/iOSSDK.pdf)

# License

See the LICENSE file for more info on the Record360SDK license.
