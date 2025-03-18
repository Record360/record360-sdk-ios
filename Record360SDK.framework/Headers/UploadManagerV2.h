//
// Copyright (c) 2016 Record360. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "Record360Constants.h"

NS_ASSUME_NONNULL_BEGIN

@class InspectionUploadStatus;
@class NetworkStatusManager;
@class Inspection;

@protocol UploadObserver;

@interface UploadManagerV2 : NSObject

@property (nonatomic, strong, readonly) NSArray<InspectionUploadStatus *> *uploadStatuses;

- (instancetype)initWithNetworkStatusManager:(NetworkStatusManager *)networkStatusManager;

- (void)startUploading;

- (NSMutableArray *)getCompletedInspections;

- (void)retryUploadForInspectionId:(NSString *)inspectionId;

- (void)createUploadInspection:(Inspection *)inspection extendedNotations:(NSString *)extendedNotations;

- (void)deleteUploadInspection:(NSString *)inspectionId;

- (void)addUploadObserver:(id<UploadObserver>)observer;

- (void)removeUploadObserver:(id<UploadObserver>)observer;

- (void)inspectionShouldIgnoreFileMissingError:(NSString *)inspectionID;

@end

NS_ASSUME_NONNULL_END
