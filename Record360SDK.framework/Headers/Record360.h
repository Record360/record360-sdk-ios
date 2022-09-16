//
// Copyright © 2016 Record360. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

#import <Record360SDK/Record360Constants.h>

@protocol UploadManagerDelegate;

@protocol Record360Delegate <NSObject>

- (void)onInspectionUploadedForReferenceNumber:(nonnull NSString *)referenceNumber;
- (void)onInspectionUploadFailedForReferenceNumber:(nonnull NSString *)referenceNumber withError:(nonnull NSError *)error;
- (void)onInspectionUploadDeletedForReferenceNumber:(nonnull NSString *)referenceNumber;

@optional
- (void)onUploadBytesComplete:(long long)bytesComplete ofTotal:(long long)bytesTotal forReferenceNumber:(nonnull NSString *)referenceNumber;

@end

@interface Record360 : NSObject

@property (nonatomic, assign) UploadMode uploadMode;
@property (nonatomic, assign) BOOL enableNotifications;

+ (void)setBaseAPIUrl:(nonnull NSString *)baseApiUrl;
- (nonnull Record360 *)initWithDelegate:(nullable id <Record360Delegate>)delegate;
- (void)enableAnalytics:(BOOL)enableAnalytics;
- (NSUInteger)getInspectionsReadyForUploadCount;
- (BOOL)isAtLeastOneInspectionUploading;
- (BOOL)isAtLeastOneUploadError;
- (void)startUploading;
- (void)stopUploading;
- (void)showProgressDialogOnViewController:(nonnull UIViewController *)rootViewController onControllerClose:(nullable void (^)(void))onClose;
- (void)setUploadManagerDelegate:(id<UploadManagerDelegate>_Nonnull)delegate;
- (void)retryUploadForInspectionId:(NSString *_Nullable)inspectionId;
- (BOOL)hasAuthenticatedUser;
- (nullable NSString *)getAuthenticatedUserId;
- (void)setDeviceNotificationToken:(nullable NSString *)deviceNotificationToken;

@end
