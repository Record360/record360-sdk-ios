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

- (NSArray<Record360FieldData *> *)onReferenceNumberEntered:(NSString *)referenceNumber fieldData:(NSArray<Record360FieldData *> *)fieldData;
- (void)onSuccessfulAuthenticationWithToken:(NSString *)userToken andUserId:(NSString *)userId;
- (void)onFailedAuthentication:(NSError *)error;

@end

@interface Record360ViewController : NSObject

+ (Record360ViewController *)loadControllerLoginAndSendTo:(Record360 *)record360 displayOn:(UIViewController *)rootViewController showCancelButton:(BOOL)showCancel;
+ (Record360ViewController *)loadControllerLoginAndSendTo:(Record360 *)record360 withReferenceNumber:(NSString *)referenceNumber displayOn:(UIViewController *)rootViewController showCancelButton:(BOOL)showCancel;

+ (Record360ViewController *)loadControllerWithUserName:(NSString *)userName andPassword:(NSString *)password sendTo:(Record360 *)record360 displayOn:(UIViewController *)rootViewController;
+ (Record360ViewController *)loadControllerWithUserName:(NSString *)userName andPassword:(NSString *)password andReferenceNumber:(NSString *)referenceNumber sendTo:(Record360 *)record360 displayOn:(UIViewController *)rootViewController;

+ (Record360ViewController *)loadControllerWithUserToken:(NSString *)userToken andUserId:(NSString *)userId sendTo:(Record360 *)record360 displayOn:(UIViewController *)rootViewController;
+ (Record360ViewController *)loadControllerWithUserToken:(NSString *)userToken andUserId:(NSString *)userId andReferenceNumber:(NSString *)referenceNumber sendTo:(Record360 *)record360 displayOn:(UIViewController *)rootViewController;

- (void)dismissViewController;
- (void)setShowOnboarding:(BOOL)showOnboarding;
- (void)setShowIntroVideo:(BOOL)showIntroVideo;
- (void)applySettings:(NSArray<Record360Setting *> *)settings;
- (void)applyDefaultSettings:(NSArray<Record360Setting *> *)settings;

@property (nonatomic, weak) id<Record360ViewControllerDelegate> delegate;

- (void)presentModalController:(UIViewController *)controller;
- (void)processIntroVideo;

@end
