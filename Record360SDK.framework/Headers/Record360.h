//
// Copyright © 2016 Record360. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

#import "Record360Constants.h"

@protocol Record360Delegate <NSObject>

- (void)onTransactionUploadedForReferenceNumber:(NSString *)referenceNumber;
- (void)onTransactionUploadFailedForReferenceNumber:(NSString *)referenceNumber withError:(NSError *)error;
- (void)onTransactionUploadDeletedForReferenceNumber:(NSString *)referenceNumber;

@optional
- (void)onUploadBytesComplete:(long long)bytesComplete ofTotal:(long long)bytesTotal forReferenceNumber:(NSString *)referenceNumber;

@end

@interface Record360 : NSObject

@property (nonatomic, assign) UploadMode uploadMode;

+ (void)setBaseAPIUrl:(NSString *)baseApiUrl;
- (Record360 *)initWithDelegate:(id <Record360Delegate>)delegate;
- (NSUInteger)getTransactionsReadyForUploadCount;
- (void)startUploading;
- (void)stopUploading;
- (void)showProgressDialogOnViewController:(UIViewController *)rootViewController onControllerClose:(void (^)(void))onClose;

@end
