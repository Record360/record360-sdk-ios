//
//  Record360Identity.h
//  Record360SDK
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface Record360Identity : NSObject

@property (nonatomic, copy, readonly, nullable) NSString *userName;
@property (nonatomic, copy, readonly, nullable) NSString *password;
@property (nonatomic, copy, readonly, nullable) NSString *userID;
@property (nonatomic, copy, readonly, nullable) NSString *userToken;

@property (nonatomic, assign) BOOL allowSDKLogin;

- (instancetype)initWithUserName:(NSString *)userName password:(nullable NSString *)password;
- (instancetype)initWithToken:(NSString *)token;
- (instancetype)initWithUserID:(nullable NSString *)userID userToken:(NSString *)userToken;

- (BOOL)hasCredentials;

@end

NS_ASSUME_NONNULL_END
