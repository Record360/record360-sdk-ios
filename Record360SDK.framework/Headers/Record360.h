//
//  Record360.h
//  Record360SDK
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

#import <Record360SDK/Record360Constants.h>
#import "Record360ViewController.h"

NS_ASSUME_NONNULL_BEGIN

@class UploadManager;
@class Record360FieldData;
@class Record360Setting;
@class Record360Identity;

@protocol Record360Delegate <NSObject>
- (void)onInspectionCompleteForReferenceNumber:(NSString *)refNum inspectionNonce:(NSString *)nonce;
- (void)onInspectionCancelledForReferenceNumber:(NSString *)refNum inspectionNonce:(NSString *)nonce;
- (void)onSDKShouldExit;
- (void)onSDKShouldRelaunch;
@optional
- (void)onSuccessfulAuthenticationWithToken:(NSString *)userToken andUserId:(NSString *)userId;
- (void)onFailedAuthentication:(NSError *)error;
- (NSArray<Record360FieldData *> *)onReferenceNumberEntered:(NSString *)referenceNumber fieldData:(NSArray<Record360FieldData *> *)fieldData;
- (void)onInspectionStartedForReferenceNumber:(NSString *)refNum inspectionNonce:(NSString *)nonce;
- (void)onInspectionUploadedForReferenceNumber:(NSString *)refNum inspectionNonce:(NSString *)nonce inspectionJSON:(NSDictionary *)inspectionJSON;
- (void)onInspectionUploadFailedForReferenceNumber:(NSString *)refNum inspectionNonce:(NSString *)nonce error:(NSError *)error;
- (void)onInspectionUploadDeletedForReferenceNumber:(NSString *)refNum inspectionNonce:(NSString *)nonce;
- (void)onInspectionUploadProgressForReferenceNumber:(NSString *)refNum inspectionNonce:(NSString *)nonce percentComplete:(CGFloat)percentComplete;
@end

@interface Record360 : NSObject

@property (nonatomic, strong, readonly) UploadManager *uploadManager;
@property (nonatomic, strong, readonly) Record360ViewController *sdkViewController;

@property (nonatomic, assign) UploadMode uploadMode;
@property (nonatomic, assign) BOOL enableNotifications;
@property (nonatomic, assign, readonly) BOOL allowUserToExitRecord360;

+ (void)configureForStaging;

+ (void)setBaseAPIUrl:(NSString *)baseApiUrl;

+ (void)setRedirectURLScheme:(NSString *)scheme;

+ (BOOL)handleAuthRedirectURL:(NSURL *)url;

- (Record360 *)initWithDelegate:(id <Record360Delegate>)delegate allowUserToExitRecord360:(BOOL)allowUserToExitRecord360 error:(NSError **)error;

- (void)setShowIntroVideo:(BOOL)showIntroVideo;

- (void)applyDefaultSettings:(NSArray<Record360Setting *> *)settings;

- (void)applySettings:(NSArray<Record360Setting *> *)settings;

- (void)enableAnalytics:(BOOL)enableAnalytics;

- (void)showProgressDialogOnViewController:(UIViewController *)rootViewController;

- (BOOL)hasAuthenticatedUser;

- (nullable NSString *)getAuthenticatedUserId;

- (void)setDeviceNotificationToken:(nullable NSString *)deviceNotificationToken;

- (void)launchRecord360:(Record360Identity *)identity;

- (void)launchReferenceCapture:(nullable NSString *)referenceNumber
           departmentReference:(nullable NSString *)departmentReference
             sequenceReference:(nullable NSString *)sequenceReference
                     fieldData:(nullable NSDictionary *)fieldData
                      identity:(Record360Identity *)identity;

- (void)launchTask:(nullable NSString *)taskID identity:(Record360Identity *)identity;

- (void)startUploading;

- (void)logoutUser;

@end

NS_ASSUME_NONNULL_END
