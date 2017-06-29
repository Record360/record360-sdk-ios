//
// Copyright (c) 2016 Record360. All rights reserved.
//

typedef NS_ENUM(NSInteger, UploadMode) {
    UploadModeOnline,
    UploadModeOffline,
    UploadModeWifiOnly
};

typedef NS_ENUM(NSInteger, MediaResolutionMode) {
    MediaResolutionVeryHigh,
    MediaResolutionHigh,
    MediaResolutionMedium
};

typedef NS_ENUM(NSInteger, ScanMode) {
    ScanModeMultiFormat,
    ScanModeVinFormat
};

#define DATE_FORMAT @"yyyy-MM-dd'T'HH:mm:ss.SSS'Z'"

extern NSString * const SETTING_UPLOAD_MODE;
extern NSString * const SETTING_RESOLUTION;
extern NSString * const SETTING_NATIVE_PHOTO_MODE;
extern NSString * const SETTING_NOTATIONS_ON_IMAGES;
extern NSString * const SETTING_LICENSE_REGION;
extern NSString * const SETTING_VIN_SCAN;
extern NSString * const SETTING_ACCOUNT;
extern NSString * const SETTING_LOGOUT;
extern NSString * const SETTING_VERSION;
extern NSString * const SETTING_LINKS;
extern NSString * const SETTING_SEND_SUPPORT_LOG;
extern NSString * const SETTING_SEND_EMAIL;
extern NSString * const SETTING_RATE_RECORD360;
extern NSString * const SETTING_REMEMBER_LOGIN;

extern NSString * const RESOLUTION_MEDIUM;
extern NSString * const RESOLUTION_HIGH;
extern NSString * const RESOLUTION_VERY_HIGH;
extern NSString * const UPLOAD_MODE_ONLINE;
extern NSString * const UPLOAD_MODE_WIFI_ONLY;
extern NSString * const UPLOAD_MODE_OFFLINE;
extern NSString * const REGION_UNITED_STATES;
extern NSString * const REGION_CANADA;
extern NSString * const REGION_AMERICAS;
extern NSString * const REGION_AUSTRALIA;
extern NSString * const REGION_ASIA;
extern NSString * const REGION_EUROPE;
extern NSString * const REGION_AFRICA;
