//
// Record360.h
// Record360SDK
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

#import <Record360SDK/Record360Constants.h>
#import "Record360ViewController.h"

NS_ASSUME_NONNULL_BEGIN

@class UploadManager;
@class AuthenticationManager;
@class NotificationManager;
@class Record360FieldData;
@class Record360Setting;
@class Record360Identity;

@protocol Record360Delegate <NSObject>
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
@end

@interface Record360 : NSObject

@property (nonatomic, strong, readonly) UploadManager *uploadManager;
@property (nonatomic, strong, readonly) AuthenticationManager *authenticationManager;
@property (nonatomic, strong, readonly) NotificationManager *notificationManager;
@property (nonatomic, strong, readonly) Record360ViewController *sdkViewController;

@property (nonatomic, assign) UploadMode uploadMode;
@property (nonatomic, assign) BOOL enableNotifications;
@property (nonatomic, assign, readonly) BOOL allowUserToExitRecord360;

+ (void)setBaseAPIUrl:(NSString *)baseApiUrl;

- (Record360 *)initWithDelegate:(id <Record360Delegate>)delegate allowUserToExitRecord360:(BOOL)allowUserToExitRecord360;

- (void)setShowIntroVideo:(BOOL)showIntroVideo;

- (void)applyDefaultSettings:(NSArray<Record360Setting *> *)settings;

- (void)applySettings:(NSArray<Record360Setting *> *)settings;

- (void)enableAnalytics:(BOOL)enableAnalytics;

- (void)showProgressDialogOnViewController:(UIViewController *)rootViewController;

- (BOOL)hasAuthenticatedUser;

- (nullable NSString *)getAuthenticatedUserId;

- (void)setDeviceNotificationToken:(nullable NSString *)deviceNotificationToken;

- (void)loadControllerWithRefreshToken:(NSString *)authToken
                               success:(void (^)(void))success
                               failure:(void (^)(RefreshTokenError refreshErrorCode))failure;

- (void)launchRecord360:(Record360Identity *)identity;

- (void)launchReferenceCapture:(nullable NSString *)referenceNumber
                   workOrderID:(nullable NSNumber *)workOrderID
                workOrderLabel:(nullable NSString *)workOrderLabel
                      identity:(Record360Identity *)identity;

- (void)launchTask:(nullable NSString *)taskID identity:(Record360Identity *)identity;

- (void)userHasRequestedToExitRecord360;

- (void)startUploading;

@end

NS_ASSUME_NONNULL_END
