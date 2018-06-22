//
// Copyright © 2016 Record360. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

#import "Record360Constants.h"
#import "Record360Setting.h"

@class Record360, Record360FieldData;

@protocol Record360ViewControllerDelegate <NSObject>

- (void)onTransactionComplete;
- (void)onTransactionCanceled;

@optional

- (nonnull NSArray<Record360FieldData *> *)onReferenceNumberEntered:(nonnull NSString *)referenceNumber fieldData:(nonnull NSArray<Record360FieldData *> *)fieldData;
- (nonnull NSArray<Record360FieldData *> *)onContractFieldData:(nonnull NSArray<Record360FieldData *> *)fieldData;
- (void)onSuccessfulAuthenticationWithToken:(nonnull NSString *)userToken andUserId:(nonnull NSString *)userId;
- (void)onFailedAuthentication:(nonnull NSError *)error;

@end

@interface Record360ViewController : NSObject

+ (nonnull Record360ViewController *)loadControllerLoginAndSendTo:(nonnull Record360 *)record360 displayOn:(nonnull UIViewController *)rootViewController showCancelButton:(BOOL)showCancel;
+ (nonnull Record360ViewController *)loadControllerLoginAndSendTo:(nonnull Record360 *)record360 withReferenceNumber:(nonnull NSString *)referenceNumber displayOn:(nonnull UIViewController *)rootViewController showCancelButton:(BOOL)showCancel;

+ (nonnull Record360ViewController *)loadControllerWithUserName:(nonnull NSString *)userName andPassword:(nonnull NSString *)password sendTo:(nonnull Record360 *)record360 displayOn:(nonnull UIViewController *)rootViewController;
+ (nonnull Record360ViewController *)loadControllerWithUserName:(nonnull NSString *)userName andPassword:(nonnull NSString *)password andReferenceNumber:(nonnull NSString *)referenceNumber sendTo:(nonnull Record360 *)record360 displayOn:(nonnull UIViewController *)rootViewController;

+ (nonnull Record360ViewController *)loadControllerWithUserToken:(nonnull NSString *)userToken andUserId:(nonnull NSString *)userId sendTo:(nonnull Record360 *)record360 displayOn:(nonnull UIViewController *)rootViewController;
+ (nonnull Record360ViewController *)loadControllerWithUserToken:(nonnull NSString *)userToken andUserId:(nonnull NSString *)userId andReferenceNumber:(nonnull NSString *)referenceNumber sendTo:(nonnull Record360 *)record360 displayOn:(nonnull UIViewController *)rootViewController;

- (void)dismissViewController;
- (void)setShowOnboarding:(BOOL)showOnboarding;
- (void)setShowIntroVideo:(BOOL)showIntroVideo;
- (void)applySettings:(nonnull NSArray<Record360Setting *> *)settings;
- (void)applyDefaultSettings:(nonnull NSArray<Record360Setting *> *)settings;

@property (nonatomic, weak, nullable) id<Record360ViewControllerDelegate> delegate;

- (void)presentModalController:(nonnull UIViewController *)controller;
- (void)processIntroVideo;

@end
