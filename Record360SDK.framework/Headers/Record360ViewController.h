//
// Copyright (c) 2016 Record360. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

#import "Record360Constants.h"
#import "Record360Setting.h"

@class Record360;

@protocol Record360ViewControllerDelegate <NSObject>

- (void)onTransactionComplete;
- (void)onTransactionCanceled;

@optional
- (void)onReferenceNumberEntered:(NSString *)referenceNumber completion:(void (^)(void))completion;
- (void)onSuccessfulAuthenticationWithToken:(NSString *)userToken andUserId:(NSString *)userId;
- (void)onFailedAuthentication:(NSError *)error;

@end

@interface Record360ViewController : NSObject

@property (nonatomic, weak) id<Record360ViewControllerDelegate> delegate;

+ (Record360ViewController *)loadControllerLoginAndSendTo:(Record360 *)record360 displayOn:(UIViewController *)rootViewController showCancelButton:(BOOL)showCancel;
+ (Record360ViewController *)loadControllerWithUserName:(NSString *)userName andPassword:(NSString *)password sendTo:(Record360 *)record360 displayOn:(UIViewController *)rootViewController;
+ (Record360ViewController *)loadControllerWithUserToken:(NSString *)userToken andUserId:(NSString *)userId sendTo:(Record360 *)record360 displayOn:(UIViewController *)rootViewController;
+ (Record360ViewController *)loadControllerLoginAndSendTo:(Record360 *)record360 withReferenceNumber:(NSString *)referenceNumber displayOn:(UIViewController *)rootViewController showCancelButton:(BOOL)showCancel;
+ (Record360ViewController *)loadControllerWithUserToken:(NSString *)userToken andUserId:(NSString *)userId andReferenceNumber:(NSString *)referenceNumber sendTo:(Record360 *)record360 displayOn:(UIViewController *)rootViewController;
+ (Record360ViewController *)loadControllerWithUserName:(NSString *)userName andPassword:(NSString *)password andReferenceNumber:(NSString *)referenceNumber sendTo:(Record360 *)record360 displayOn:(UIViewController *)rootViewController;

- (void)setShowOnboarding:(BOOL)showOnboarding;
- (void)applySettings:(NSArray<Record360Setting *> *)settings;
- (void)applyDefaultSettings:(NSArray<Record360Setting *> *)settings;
- (NSArray *)getFieldData;
- (void)setFieldData:(NSArray *)dataToPopulate;
- (void)presentModalController:(UIViewController *)controller;

@end
