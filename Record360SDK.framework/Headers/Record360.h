//
// Copyright © 2016 Record360. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

#import <Record360SDK/Record360Constants.h>

NS_ASSUME_NONNULL_BEGIN

@class UploadManagerV2;

@protocol Record360Delegate <NSObject>
- (void)onInspectionUploadedForReferenceNumber:(NSString *)referenceNumber;
- (void)onInspectionUploadFailedForReferenceNumber:(NSString *)referenceNumber;
- (void)onInspectionUploadDeletedForReferenceNumber:(NSString *)referenceNumber;
@end

@interface Record360 : NSObject

@property (nonatomic, strong, readonly) UploadManagerV2 *uploadManager;

@property (nonatomic, assign) UploadMode uploadMode;
@property (nonatomic, assign) BOOL enableNotifications;

+ (void)setBaseAPIUrl:(NSString *)baseApiUrl;

- (Record360 *)initWithDelegate:(nullable id <Record360Delegate>)delegate;
- (void)enableAnalytics:(BOOL)enableAnalytics;
- (void)showProgressDialogOnViewController:(UIViewController *)rootViewController onControllerClose:(nullable void (^)(void))onClose;
- (BOOL)hasAuthenticatedUser;
- (nullable NSString *)getAuthenticatedUserId;
- (void)setDeviceNotificationToken:(nullable NSString *)deviceNotificationToken;

@end

NS_ASSUME_NONNULL_END
