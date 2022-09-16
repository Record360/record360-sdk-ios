//
// Copyright © 2016 Record360. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

#import <Record360SDK/Record360Constants.h>
#import <Record360SDK/Record360Setting.h>

NS_ASSUME_NONNULL_BEGIN

@class Record360, Record360FieldData;

@protocol Record360ViewControllerDelegate <NSObject>

- (void)onInspectionComplete;
- (void)onInspectionCanceled;

@optional

- (NSArray<Record360FieldData *> *)onReferenceNumberEntered:(NSString *)referenceNumber fieldData:(NSArray<Record360FieldData *> *)fieldData;
- (NSArray<Record360FieldData *> *)onContractFieldData:(NSArray<Record360FieldData *> *)fieldData;
- (void)onSuccessfulAuthenticationWithToken:(NSString *)userToken andUserId:(NSString *)userId;
- (void)onFailedAuthentication:(NSError *)error;

@end

@interface Record360ViewController : NSObject

+ (Record360ViewController *)loadControllerLoginAndSendTo:(Record360 *)record360 displayOn:(UIViewController *)rootViewController showCancelButton:(BOOL)showCancel withLoginUsername:(nullable NSString *)username;
+ (Record360ViewController *)loadControllerLoginAndSendTo:(Record360 *)record360 withReferenceNumber:(nullable NSString *)referenceNumber workOrderId:(NSNumber *)workOrderId workOrderLabel:(NSString *)workOrderLabel displayOn:(UIViewController *)rootViewController showCancelButton:(BOOL)showCancel withLoginUsername:(nullable NSString *)username;
+ (Record360ViewController *)loadControllerLoginAndSendTo:(Record360 *)record360 withTaskId:(NSString *)taskId displayOn:(UIViewController *)rootViewController showCancelButton:(BOOL)showCancel withLoginUsername:(nullable NSString *)username;

+ (Record360ViewController *)loadControllerWithUserName:(NSString *)userName andPassword:(NSString *)password sendTo:(Record360 *)record360 displayOn:(UIViewController *)rootViewController;
+ (Record360ViewController *)loadControllerWithUserName:(NSString *)userName andPassword:(NSString *)password andReferenceNumber:(nullable NSString *)referenceNumber workOrderId:(nullable NSNumber *)workOrderId workOrderLabel:(nullable NSString *)workOrderLabel sendTo:(Record360 *)record360 displayOn:(UIViewController *)rootViewController;
+ (Record360ViewController *)loadControllerWithUserName:(NSString *)userName andPassword:(NSString *)password andTaskId:(NSString *)taskId sendTo:(Record360 *)record360 displayOn:(UIViewController *)rootViewController;

+ (Record360ViewController *)loadControllerWithUserToken:(NSString *)userToken andReferenceNumber:(nullable NSString *)referenceNumber workOrderId:(nullable NSNumber *)workOrderId workOrderLabel:(nullable NSString *)workOrderLabel sendTo:(Record360 *)record360 displayOn:(UIViewController *)rootViewController;
+ (Record360ViewController *)loadControllerWithUserToken:(NSString *)userToken andUserId:(NSString *)userId sendTo:(Record360 *)record360 displayOn:(UIViewController *)rootViewController;
+ (Record360ViewController *)loadControllerWithUserToken:(NSString *)userToken andUserId:(NSString *)userId andReferenceNumber:(nullable NSString *)referenceNumber workOrderId:(nullable NSNumber *)workOrderId workOrderLabel:(nullable NSString *)workOrderLabel sendTo:(Record360 *)record360 displayOn:(UIViewController *)rootViewController;
+ (Record360ViewController *)loadControllerWithUserToken:(NSString *)userToken andUserId:(nullable NSString *)userId andTaskId:(NSString *)taskId sendTo:(Record360 *)record360 displayOn:(UIViewController *)rootViewController;
+ (Record360ViewController *)loadControllerWithUserToken:(NSString *)userToken userId:(NSString *)userId referenceNumber:(nullable NSString *)referenceNumber workOrderId:(nullable NSNumber *)workOrderId workOrderLabel:(nullable NSString *)workOrderLabel andIsOneTimeLink:(BOOL)isOneTimeUseLink sendTo:(Record360 *)record360 displayOn:(UIViewController *)rootViewController;

+ (Record360ViewController *)loadControllerWithRefreshToken:(NSString *)authToken sendTo:(Record360 *)record360 displayOn:(UIViewController *)rootViewController success:(void (^)(void))success failure:(void (^)(RefreshTokenError refreshErrorCode))failure;

- (void)dismissViewController;
- (void)setShowOnboarding:(BOOL)showOnboarding;
- (void)setShowIntroVideo:(BOOL)showIntroVideo;
- (void)applySettings:(NSArray<Record360Setting *> *)settings;
- (void)applyDefaultSettings:(NSArray<Record360Setting *> *)settings;

@property (nonatomic, weak, nullable) id<Record360ViewControllerDelegate> delegate;

- (void)presentModalController:(UIViewController *)controller;
- (void)processIntroVideo;

@end

NS_ASSUME_NONNULL_END
