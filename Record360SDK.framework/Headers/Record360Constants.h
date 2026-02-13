//
// Copyright © 2016 Record360. All rights reserved.
//

typedef NS_ENUM(NSInteger, UploadMode) {
    UploadModeOnline = 0,
    UploadModeWifiOnly = 2,
    UploadModeHybrid = 3
};

// Setting
extern NSString * const SETTING_UPLOAD_MODE;
// Possible values
extern NSString * const UPLOAD_MODE_ONLINE;
extern NSString * const UPLOAD_MODE_HYBRID;
extern NSString * const UPLOAD_MODE_WIFI_ONLY;

// Setting
extern NSString * const SETTING_RESOLUTION;
// Possible values
extern NSString * const RESOLUTION_MEDIUM;
extern NSString * const RESOLUTION_HIGH;
extern NSString * const RESOLUTION_VERY_HIGH;

// On/Off switch settings
extern NSString * const SETTING_NATIVE_PHOTO_MODE;
extern NSString * const SETTING_NOTATIONS_ON_IMAGES;
extern NSString * const SETTING_REMEMBER_LOGIN;
extern NSString * const SETTING_ADD_TIMESTAMP_TO_MEDIA;

// Other settings
extern NSString * const SETTING_ACCOUNT;
extern NSString * const SETTING_LOGOUT;
extern NSString * const SETTING_VERSION;
extern NSString * const SETTING_SHOW_INTRO_VIDEO;
extern NSString * const SETTING_SEND_SUPPORT_LOG;
extern NSString * const SETTING_RATE_RECORD360;
extern NSString * const SETTING_LINKS;
extern NSString * const SETTING_SEND_EMAIL;

// Possible values
extern NSString * const SYMBOLOGIES_ALL;
extern NSString * const SYMBOLOGIES_VIN_SCAN;
extern NSString * const SYMBOLOGIES_QR_SCAN;
extern NSString * const SYMBOLOGIES_DATA_MATRIX;
