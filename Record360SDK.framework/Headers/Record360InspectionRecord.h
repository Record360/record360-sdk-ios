//
//  Record360InspectionRecord.h
//  Record360SDK
//

#import <Foundation/Foundation.h>

typedef NS_ENUM(NSInteger, Record360RecordSource) {
    Record360RecordSourceDevice = 0,
    Record360RecordSourceServer = 1
};

typedef NS_ENUM(NSInteger, Record360RecordStatus) {
    Record360RecordStatusInProgress = 0,
    Record360RecordStatusUploading = 1,
    Record360RecordStatusFailed = 2,
    Record360RecordStatusCompletedUpload = 3
};

NS_ASSUME_NONNULL_BEGIN

extern NSErrorDomain const Record360InspectionRecordErrorDomain;

typedef NS_ERROR_ENUM(Record360InspectionRecordErrorDomain, Record360InspectionRecordErrorCode) {
    Record360InspectionRecordErrorAuthentication = 1,
    Record360InspectionRecordErrorMissingMedia = 2,
    Record360InspectionRecordErrorMaxRetriesExhausted = 3,
    Record360InspectionRecordErrorInspectionLimit = 4
};

@interface Record360InspectionRecord : NSObject

@property (nonatomic, copy, readonly) NSString *referenceNumber;
@property (nonatomic, copy, readonly) NSString *inspectionNonce;
@property (nonatomic, copy, readonly, nullable) NSDictionary *recordJSON;
@property (nonatomic, copy, readonly, nullable) NSNumber *sourceType;
@property (nonatomic, assign, readonly) Record360RecordStatus status;
@property (nonatomic, copy, readonly, nullable) NSDate *startedAt;
@property (nonatomic, copy, readonly, nullable) NSError *uploadError;
@property (nonatomic, assign, readonly) BOOL isUploaded;

- (instancetype)initWithReferenceNumber:(NSString *)referenceNumber
                        inspectionNonce:(NSString *)inspectionNonce
                             recordJSON:(nullable NSDictionary *)recordJSON
                             sourceType:(nullable NSNumber *)sourceType
                                 status:(Record360RecordStatus)status
                              startedAt:(nullable NSDate *)startedAt
                            uploadError:(nullable NSError *)uploadError;

- (instancetype)init NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
