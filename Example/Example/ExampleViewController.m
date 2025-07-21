//
//  Copyright © 2017 Record360. All rights reserved.
//

#import <Record360SDK/Record360.h>
#import <Record360SDK/Record360FieldData.h>
#import <Record360SDK/Record360Setting.h>
#import <Record360SDK/Record360ViewController.h>
#import <Record360SDK/Record360Identity.h>

#import "ExampleViewController.h"

NSString * const USER_TOKEN_KEY = @"user_token";
NSString * const USER_ID_KEY = @"user_id";

@interface ExampleViewController () <Record360Delegate>

@property (nonatomic) Record360 *record360;
@property (nonatomic) Record360ViewController *record360ViewController;

@property (weak, nonatomic) IBOutlet UITextField *username;
@property (weak, nonatomic) IBOutlet UITextField *password;
@property (weak, nonatomic) IBOutlet UIButton *savedLogin;
@property (nonatomic, assign) BOOL hostingSDKViewController;

@end

@implementation ExampleViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    
    self.record360 = [[Record360 alloc] initWithDelegate:self allowUserToExitRecord360:NO];
    [self.record360 startUploading];
}

- (void)viewDidAppear:(BOOL)animated {
    [super viewDidAppear:animated];
    [self updateSavedLogin];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (IBAction)loginButtonPressed:(UIButton *)sender {
    if (self.username.text.length > 0 && self.password.text.length > 0) {
        // Log in with supplied credentials.
        Record360Identity *identity = [[Record360Identity alloc] initWithUserName:self.username.text password:self.password.text];
        [self hostSDKViewController: ^{
            [self.record360 launchRecord360:identity];
            [self buildDefaultSettings];
        }];
    } else {
        NSLog(@"No credentials provided.  Please enter username and password to try again.");
    }
}

- (IBAction)savedLoginButtonPressed:(UIButton *)sender {
    // Login using the token saved from a previous login.
    Record360Identity *identity = [[Record360Identity alloc] initWithUserID:[[NSUserDefaults standardUserDefaults] stringForKey:USER_ID_KEY] userToken:[[NSUserDefaults standardUserDefaults] stringForKey:USER_TOKEN_KEY]];
    [self hostSDKViewController: ^{
        [self.record360 launchRecord360:identity];
        [self buildDefaultSettings];
    }];
}

- (IBAction)sdkLoginButtonPressed:(UIButton *)sender {
    // Use the login page inside the SDK.  No credentials are necessary.
    Record360Identity *identity = [[Record360Identity alloc] initWithUserName:nil password:nil];
    [self hostSDKViewController: ^{
        [self.record360 launchRecord360:identity];
        [self buildDefaultSettings];
    }];
}

// This callback is called after the user has entered a reference id.  Use this to push data into Record360.
- (NSArray<Record360FieldData *> *)onReferenceNumberEntered:(NSString *)referenceNumber fieldData:(NSArray<Record360FieldData *> *)fieldData {
    // Modify fields as appropriate.  This will place Sample Data in the first field on the form and the reference ID in the second field.
    if (fieldData.count > 2) {
        Record360FieldData *field = fieldData[0];
        field.fieldValue = @"Sample data";
        
        field = fieldData[1];
        field.fieldValue = referenceNumber;
    }
    return fieldData;
}

- (void)onSuccessfulAuthenticationWithToken:(NSString *)userToken andUserId:(NSString *)userId {
    [[NSUserDefaults standardUserDefaults] setObject:userId forKey:USER_ID_KEY];
    [[NSUserDefaults standardUserDefaults] setObject:userToken forKey:USER_TOKEN_KEY];
    [[NSUserDefaults standardUserDefaults] synchronize];
}

- (void)onFailedAuthentication:(NSError *)error {
    [self dismissSDKViewController:NO completion:^{
        [[NSUserDefaults standardUserDefaults] removeObjectForKey:USER_ID_KEY];
        [[NSUserDefaults standardUserDefaults] removeObjectForKey:USER_TOKEN_KEY];
        [[NSUserDefaults standardUserDefaults] synchronize];
        [self updateSavedLogin];
        NSLog(@"Error logging in %@.  Please check credentials and try again.", error);
    }];
}


- (void)updateSavedLogin {
    // Optionally, store the login credentials for future logins if that suits your needs.
    NSString *userToken = [[NSUserDefaults standardUserDefaults] objectForKey:USER_TOKEN_KEY];
    NSString *userId = [[NSUserDefaults standardUserDefaults] objectForKey:USER_ID_KEY];
    bool saved = userId != nil && userToken != nil;
    
    [self.savedLogin setEnabled:saved];
    [self.savedLogin setAlpha:saved ? 1.0F : .5F];
}

// Notification immediately after a transaction has completed
- (void)onInspectionComplete {
    // Show progress dialog
    [self dismissSDKViewController:NO completion:^{
        [self.record360 showProgressDialogOnViewController:self];
        [self updateSavedLogin];
    }];
}

// Notification immediately after a transaction has cancelled
- (void)onInspectionCanceled {
    [self dismissSDKViewController:NO completion:^{
        [self showDialogTitle:@"Transaction Cancelled" andMessage:nil];
        [self updateSavedLogin];
    }];
}

// Uploading progress notification as transaction is uploaded
- (void)onUploadBytesComplete:(long long)bytesComplete ofTotal:(long long)bytesTotal forReferenceNumber:(NSString *)referenceNumber {
    NSLog(@"Upload task progress on %@ at %lld of %lld", referenceNumber, bytesComplete, bytesTotal);
}

// Notification when a transaction has uploaded.  These come from the Record360 object.
- (void)onInspectionUploadedForReferenceNumber:(NSString *)referenceNumber {
    NSString *message = [NSString stringWithFormat:@"Transaction %@ uploaded successfully", referenceNumber];
    NSLog(@"%@", message);
    [self showDialogTitle:@"Transaction upload" andMessage:message]; // If the Record360ViewController or progress dialog is loaded and showing, then this alert will not show.
}

// Notification when a transaction has failed to upload.  These come from the Record360 object.
- (void)onInspectionUploadFailedForReferenceNumber:(NSString *)referenceNumber withError:(NSError *)error {
    NSString *message = [NSString stringWithFormat:@"An error occurred when uploading the transaction with reference number %@: %@", referenceNumber, error.localizedDescription];
    NSLog(@"%@", message);
    [self showDialogTitle:@"Transaction upload error" andMessage:message]; // If the Record360ViewController or progress dialog is loaded and showing, then this alert will not show.
}

// Notification when a transaction has stopped uploading due to the user deleting it.  These come from the Record360 object.
- (void)onInspectionUploadDeletedForReferenceNumber:(NSString *)referenceNumber {
    NSLog(@"Transaction upload with reference number %@ was deleted.", referenceNumber);
}

- (void)showDialogTitle:(NSString *)title andMessage:(NSString *)message {
    UIAlertController *alertController = [UIAlertController alertControllerWithTitle:title
                                                                             message:message
                                                                      preferredStyle:UIAlertControllerStyleAlert];
    [alertController addAction:[UIAlertAction actionWithTitle:@"OK" style:UIAlertActionStyleDefault handler:^(UIAlertAction *action) {
        [alertController dismissViewControllerAnimated:YES completion:nil];
    }]];
    [self presentViewController:alertController animated:NO completion:nil];
}

- (void)buildDefaultSettings {
    [self.record360 applyDefaultSettings:@[
        [[Record360Setting alloc] initSwitchSetting:SETTING_NOTATIONS_ON_IMAGES canDisplay:NO value:NO],
        [[Record360Setting alloc] initSwitchSetting:SETTING_NATIVE_PHOTO_MODE canDisplay:NO value:NO],
        [[Record360Setting alloc] initOptionSetting:SETTING_RESOLUTION canDisplay:YES value:RESOLUTION_HIGH],
        [[Record360Setting alloc] initOptionSetting:SETTING_UPLOAD_MODE canDisplay:YES value:UPLOAD_MODE_ONLINE],
        [[Record360Setting alloc] initSetting:SETTING_SEND_SUPPORT_LOG],
        [[Record360Setting alloc] initSetting:SETTING_LOGOUT],
        [[Record360Setting alloc] initSetting:SETTING_LINKS label:@"Access Records" link:@"https://app.record360.com"],
        [[Record360Setting alloc] initSetting:SETTING_RATE_RECORD360],
        [[Record360Setting alloc] initSetting:SETTING_LINKS label:@"Terms of Service" link:@"https://app.record360.com/terms.html"],
        [[Record360Setting alloc] initSetting:SETTING_LINKS label:@"Privacy" link:@"https://app.record360.com/privacy.html"],
        [[Record360Setting alloc] initSetting:SETTING_VERSION]
    ]];
}

#pragma mark - SDKViewController

- (void)hostSDKViewController: (void (^)(void))completion {

    // ok, the sdk ui needs to be totally torn down before being reconstructed via
    // one of the "launch" methods.  Future revisions to the SDK should address this,
    // but until then, this means that we must ensure the SDK VC is dismissed before
    // we can safely host it in preparation for one of the launch methods. Basically,
    // This effectively makes hostSDKViewController safely re-entrant
    
    [self dismissSDKViewController:NO completion:^{
    
        // remove from any previous host
        
        [self.record360.sdkViewController.view removeFromSuperview];
        [self.record360.sdkViewController removeFromParentViewController];
                
        // add to our view hierarchy
        
        [self addChildViewController:self.record360.sdkViewController];
        [self.record360.sdkViewController didMoveToParentViewController:self];
        
        [self.view addSubview:self.record360.sdkViewController.view];

        [self.record360.sdkViewController.view.topAnchor constraintEqualToAnchor:self.view.topAnchor].active = YES;
        [self.record360.sdkViewController.view.bottomAnchor constraintEqualToAnchor:self.view.bottomAnchor].active = YES;
        [self.record360.sdkViewController.view.leadingAnchor constraintEqualToAnchor:self.view.leadingAnchor].active = YES;
        [self.record360.sdkViewController.view.trailingAnchor constraintEqualToAnchor:self.view.trailingAnchor].active = YES;

        self.hostingSDKViewController = YES;
        
        completion();
    }];
}

- (void)dismissSDKViewController:(BOOL)animated completion: (void (^)(void))completion {

    if (!self.hostingSDKViewController) {
        completion();
        return;
    }

    // dismiss it via its nav controller, then take it out of the view hierarchy
    
    UIViewController *viewController = self.record360.sdkViewController.navigationController ?: self.record360.sdkViewController;
    
    [viewController dismissViewControllerAnimated:animated completion:^{
        [self.record360.sdkViewController willMoveToParentViewController:nil];
        [self.record360.sdkViewController.view removeFromSuperview];
        [self.record360.sdkViewController.view removeConstraints:self.view.constraints];
        [self.record360.sdkViewController removeFromParentViewController];
        self.hostingSDKViewController = NO;
        completion();
    }];
}


@end
