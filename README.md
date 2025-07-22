[![Version](https://img.shields.io/cocoapods/v/Record360SDK.svg?style=flat)](http://cocoapods.org/pods/Record360SDK)

Record360 iOS SDK
==================

![Record360 Logo](https://r360-public-media.s3.amazonaws.com/screenshots/cocoapods-sdk/360-logo.png)

# Introduction

The Record360SDK.framework is a Cocoa framework that allows mobile clients to leverage [Record360](https://www.record360.com).  This allows the client to track and record the condition of assets using the Record360 workflow.  An account with Record360 is required.  Please contact sales@record360.com for details.

# Requirements

-   iOS 14.0 or later

# Example

To run the example project, clone the repo, and run `pod install` from the Example directory.

# Preparation

In order to utilize the SDK framework, an account with Record360 is required.  Please contact sales@record360.com for details.

This SDK is not compatible with dark mode.  Please add the **Appearance** property to your info.plist file like this:

![Appearance Screenshot](https://r360-public-media.s3.amazonaws.com/screenshots/cocoapods-sdk/appearance.png)

# Installation with CocoaPods

Record360 SDK can be installed using CocoaPods. CocoaPods is a dependency manager that automates the process of integrating 3rd-party libraries into your projects.  If you do not have CocoaPods, please see [CocoaPods](http://cocoapods.org) for details on how to install it.

### Podfile

Create a Podfile in your Xcode project directory with the following lines.
    
```ruby
platform :ios, '14.0'
use_frameworks!

pod 'Record360SDK', '~> 4.19.8' 
```

From the command line execute `pod install` to add the Record360SDK.

Note: If you want Drivers License verification functionality packed into the SDK, please contact us at sales@record360.com.

# Installation without CocoaPods

Record360 can provide the framework, contact support@record360.com for more information.

# Integrating Record360

### Starting the inspection upload handling process

1. Designate a Record360Delegate that will handle inspection upload events.  Note that the upload process is asynchronous, so the delegate will not be called immediately after the process completes.

```objectivec    
@interface MyApplicationViewController () <Record360Delegate>
```

2. Create a Record360 object that will display the Record360 Inspection Interface, handle inspection file uploads and provide information about upload progress events to a delegate.  Pass in the delegate to handle the inspection upload events.
   If you pass YES to allowUserToExitRecord360, then the SDK will surface a button that when tapped will call the Record360Delegate userHasRequestedToExitRecord360 method. Normally, your
   implemenation of userHasRequestedToExitRecord360 would then dismiss the SDK View Controller.  If you pass NO, no button will be displayed and your app will be responsible for deciding when to dimiss the SDK View Controller. 

```objectivec    
Record360 *record360 = [[Record360 alloc] initWithDelegate:self allowUserToExitRecord360:YES];
```

3. Add methods to host and dismiss the SDK View Controller.  The SDK exposes its sdkViewController property to your app.  This allows you to add the View Controller to your apps View Hiearchy in any way you wish.  Commensurately,
   you will need to have a way to dismiss the View Controller (remove it from your view hierarchy).  This Example App includes two methods - hostSDKViewController and dismissSDKViewController - which you can use as is if you wish,
   along with a boolean property to help managing hosting the SDK View Controller. 
    
4. Present the Record360 Inspection Interface.  To do so, you first need to ensure you are hosting the SDK View Controller.   Next, create a Record360Identity object which encapsulates login credential details, and
   pass the identity object to one of the following methods to launch the record360 Interface:

```objectivec   
 
- (void)launchRecord360:(Record360Identity *)identity;

- (void)launchReferenceCapture:(nullable NSString *)referenceNumber
                   workOrderID:(nullable NSNumber *)workOrderID
                workOrderLabel:(nullable NSString *)workOrderLabel
                      identity:(Record360Identity *)identity;
```

Here is an example that shows creating an identity with a user name and password, hosting the SDK View Controller, and then calling to launch the record360 interface:

```objectivec   
=
Record360Identity *identity = [[Record360Identity alloc] initWithUserName:@"testuser@record360.com" password:@"P@ssword!"];

[self hostSDKViewController: ^{
    [self.record360 launchRecord360:identity];
}];
```

Here is an example that shows creating an identity with a user ID and User Token (acquired from a previously successful login), hosting the SDK View Controller, and then calling to launch the record360 interface:

```objectivec   
- (void)loginWithSavedUserIDAndToken {
    Record360Identity *identity = [[Record360Identity alloc] initWithUserID:[[NSUserDefaults standardUserDefaults] stringForKey:USER_ID_KEY] userToken:[[NSUserDefaults standardUserDefaults] stringForKey:USER_TOKEN_KEY]];

    [self hostSDKViewController: ^{
        [self.record360 launchRecord360:identity];
    }];
}

- (void)onSuccessfulAuthenticationWithToken:(NSString *)userToken andUserId:(NSString *)userId {
    [[NSUserDefaults standardUserDefaults] setObject:userId forKey:USER_ID_KEY];
    [[NSUserDefaults standardUserDefaults] setObject:userToken forKey:USER_TOKEN_KEY];
    [[NSUserDefaults standardUserDefaults] synchronize];
}

```

Your class should now look something like this:

```objectivec    
#import <Record360SDK/Record360.h>

@interface MyApplicationViewController () <Record360Delegate>

@property (nonatomic) Record360 *record360;

@end

@implementation

- (void)viewDidLoad {
    [super viewDidLoad];

    self.record360 = [[Record360 alloc] initWithDelegate:self allowUserToExitRecord360:YES];
}

- (IBAction)loginButtonPressed:(UIButton *)sender {
    if (self.username.text.length > 0 && self.password.text.length > 0) {
        Record360Identity *identity = [[Record360Identity alloc] initWithUserName:self.username.text password:self.password.text];
        [self hostSDKViewController: ^{
            [self.record360 launchRecord360:identity];
        }];
    }
}

- (void)loginWithSavedUserIDAndToken {
    Record360Identity *identity = [[Record360Identity alloc] initWithUserID:[[NSUserDefaults standardUserDefaults] stringForKey:USER_ID_KEY] userToken:[[NSUserDefaults standardUserDefaults] stringForKey:USER_TOKEN_KEY]];

    [self hostSDKViewController: ^{
        [self.record360 launchRecord360:identity];
    }];
}

```

5. If login is unsucessful, the SDK will call the delegate onFailedAuthentication method.  You will need to first dismiss the SDK View Controller.  For Example:
 
```objectivec
- (void)onFailedAuthentication:(NSError *)error {
    [self dismissSDKViewController:NO completion:^{
        NSLog(@"Error logging in %@.  Please check credentials and try again.", error);
    }];
}
```

6. If login is sucessful, You may optionally persist the user's token and id for later logging the user in again without asking for their credentials.  For Example:

```objectivec
- (void)onSuccessfulAuthenticationWithToken:(NSString *)userToken andUserId:(NSString *)userId {
    [[NSUserDefaults standardUserDefaults] setObject:userId forKey:USER_ID_KEY];
    [[NSUserDefaults standardUserDefaults] setObject:userToken forKey:USER_TOKEN_KEY];
    [[NSUserDefaults standardUserDefaults] synchronize];
}
```

7. After login and the completion or cancellation of the the inspection by the user, one of the Record360ViewController delegate methods will be called.

```objectivec
- (void)onInspectionComplete;
- (void)onInspectionCanceled;
```

In both of these methods you should first dismiss the SDK View Controller. For Example:

```objectivec
- (void)onInspectionComplete {
    [self dismissSDKViewController:NO completion:^{
        [self.record360 showProgressDialogOnViewController:self];
    }];
}

- (void)onInspectionCanceled {
    [self dismissSDKViewController:NO completion:^{
        [self showDialogTitle:@"Transaction Cancelled" andMessage:nil];
    }];
}
```

6. If the inspection is uploading, implement the callbacks as specified by the Record360Delegate protocol.  When the Record360 object has finished uploading an inspection, one of the Record360Delegate methods will be called.

```objectivec
- (void)onInspectionUploadedForReferenceNumber:(nonnull NSString *)referenceNumber;
- (void)onInspectionUploadFailedForReferenceNumber:(nonnull NSString *)referenceNumber withError:(nonnull NSError *)error;
- (void)onInspectionUploadDeletedForReferenceNumber:(nonnull NSString *)referenceNumber;
```

# Record360 Class

This object handles inspection uploads.  If there are remaining inspections that haven’t been processed, the instance you create will process them when online.

Use the init method below to create a Record360 class:

```objectivec
- (nonnull Record360 *)initWithDelegate:(nullable id <Record360Delegate>)delegate allowUserToExitRecord360:(BOOL)allowUserToExitRecord360;
```

Get/Set the property below for the upload mode.  Options include online, offline or wifi-only.  In wifi-only mode, the inspections will be uploaded when a wifi network is available.

```objectivec
@property (nonatomic, assign) UploadMode uploadMode;
```

The method below returns the number of inspections that are ready for upload.  Inspections that are in the process of uploading will be included in this count.

```objectivec
- (NSUInteger)getInspectionsReadyForUploadCount;
```

Use the method below to manually start uploading inspections:

```objectivec
- (void)startUploading;
```

Use the method below to show a progress dialog UI over the passed in UIViewController:

```objectivec
- (void)showProgressDialogOnViewController:(nonnull UIViewController *)rootViewController;
```

Present the Record360 User Interaface:

```objectivec
- (void)launchRecord360:(Record360Identity *)identity;
```

Present the Record360 User Interaface, allowing you to provide a reference number of the Unit / Asset to begin an insepction with. 

```objectivec
- (void)launchReferenceCapture:(nullable NSString *)referenceNumber
                   workOrderID:(nullable NSNumber *)workOrderID
                workOrderLabel:(nullable NSString *)workOrderLabel
                      identity:(Record360Identity *)identity;
```

Use one of the methods below to configure the Record360ViewController object to modify the workflow process.  Some of these settings are preset, while others are customizable.  See the [Record360Setting](#Record360Setting) section below for more details.

```objectivec
- (void)applySettings:(nonnull NSArray<Record360Setting *> *)settings;
- (void)applyDefaultSettings:(nonnull NSArray<Record360Setting *> *)settings;
```

Sets whether to show the Record360 Introduction Video.  Defaults to false.

```objectivec
- (void)setShowIntroVideo:(BOOL)showIntroVideo;
```

# Record360Delegate

Use these delegate methods to respond to various inspection upload events:

```objectivec
- (void)onInspectionComplete;
- (void)onInspectionCanceled;

@optional

- (void)onSuccessfulAuthenticationWithToken:(NSString *)userToken andUserId:(NSString *)userId;
- (void)onFailedAuthentication:(NSError *)error;
- (NSArray<Record360FieldData *> *)onContractFieldData:(NSArray<Record360FieldData *> *)fieldData;
- (NSArray<Record360FieldData *> *)onReferenceNumberEntered:(NSString *)referenceNumber fieldData:(NSArray<Record360FieldData *> *)fieldData;
- (void)onInspectionUploadedForReferenceNumber:(NSString *)referenceNumber inspectionJSON:(NSDictionary *)inspectionJSON;
- (void)onInspectionUploadFailedForReferenceNumber:(NSString *)referenceNumber;
- (void)onInspectionUploadDeletedForReferenceNumber:(NSString *)referenceNumber;
- (void)userHasRequestedToExitRecord360;
```

# Record360Identity

Use one of the below init methods to create a Record360Identity which you can then pass to Record360 to present the Record360 Interface:

```objectivec
- (instancetype)initWithUserName:(NSString *)userName password:(nullable NSString *)password;
- (instancetype)initWithToken:(NSString *)token;
- (instancetype)initWithUserID:(nullable NSString *)userID userToken:(NSString *)userToken;
```

# Record360Setting

Use one of the below init methods to create a Record360Setting that can be used to modify the workflow process.  Use one of the Setting constants as the settingKey with the appropriate init method.  The [Example](#Example) project contains various settings configurations.

```objectivec
- (instancetype)initSetting:(nonnull NSString *)settingKey;
- (instancetype)initSetting:(nonnull NSString *)settingKey label:(nonnull NSString *)label;
- (instancetype)initSetting:(nonnull NSString *)settingKey canDisplay:(BOOL)canDisplay;
- (instancetype)initSetting:(nonnull NSString *)settingKey label:(nonnull NSString *)label canDisplay:(BOOL)canDisplay;
- (instancetype)initSetting:(nonnull NSString *)settingKey label:(nonnull NSString *)label link:(nonnull NSString *)link;
- (instancetype)initSetting:(nonnull NSString *)settingKey label:(nonnull NSString *)label recipient:(nonnull NSString *)recipient title:(nonnull NSString *)title;

- (instancetype)initOptionSetting:(nonnull NSString *)settingKey value:(nonnull NSString *)value;
- (instancetype)initOptionSetting:(nonnull NSString *)settingKey canDisplay:(BOOL)canDisplay value:(nonnull NSString *)value;

- (instancetype)initSwitchSetting:(nonnull NSString *)settingKey value:(BOOL)value;
- (instancetype)initSwitchSetting:(nonnull NSString *)settingKey canDisplay:(BOOL)canDisplay value:(BOOL)value;
```

Here is a list of settings and their possible values:

```objectivec
// Setting
extern NSString * const SETTING_UPLOAD_MODE;
// Possible values
extern NSString * const UPLOAD_MODE_ONLINE;
extern NSString * const UPLOAD_MODE_WIFI_ONLY;
extern NSString * const UPLOAD_MODE_OFFLINE;

// Setting
extern NSString * const SETTING_RESOLUTION;
// Possible values
extern NSString * const RESOLUTION_MEDIUM;
extern NSString * const RESOLUTION_HIGH;
extern NSString * const RESOLUTION_VERY_HIGH;

// On/Off switch settings
extern NSString * const SETTING_NATIVE_PHOTO_MODE;
extern NSString * const SETTING_NOTATIONS_ON_IMAGES;
extern NSString * const SETTING_REMEMBER_LOGIN;
extern NSString * const SETTING_ADD_TIMESTAMP_TO_MEDIA;

// Other settings
extern NSString * const SETTING_ACCOUNT;
extern NSString * const SETTING_LOGOUT;
extern NSString * const SETTING_VERSION;
extern NSString * const SETTING_SHOW_INTRO_VIDEO;
extern NSString * const SETTING_SEND_SUPPORT_LOG;
extern NSString * const SETTING_RATE_RECORD360;
extern NSString * const SETTING_LINKS;
extern NSString * const SETTING_SEND_EMAIL;

// Possible values
extern NSString * const SYMBOLOGIES_ALL;
extern NSString * const SYMBOLOGIES_VIN_SCAN;
extern NSString * const SYMBOLOGIES_QR_SCAN;
extern NSString * const SYMBOLOGIES_DATA_MATRIX;
```

Questions? 

Alexis Valencia – alex@record360.com

John Detloff – jdetloff@record360.com

Ando Sonenblick – ando.sonenblick@record360.com

Visit us on the web at www.record360.com/business

# License

See the LICENSE file for more info on the Record360SDK license.
