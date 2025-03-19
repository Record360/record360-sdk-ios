//
// Copyright © 2016 Record360. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class Setting;

@interface Record360Setting : NSObject

@property (nonatomic, strong, readonly) NSString *settingKey;
@property (nonatomic, strong, readonly) NSString *label;
@property (nonatomic, strong, readonly) NSNumber *settingType;
@property (nonatomic, strong, readonly) NSNumber *canDisplay;

- (instancetype)initSetting:(NSString *)settingKey;
- (instancetype)initSetting:(NSString *)settingKey label:(NSString *)label;
- (instancetype)initSetting:(NSString *)settingKey canDisplay:(BOOL)canDisplay;
- (instancetype)initSetting:(NSString *)settingKey label:(NSString *)label canDisplay:(BOOL)canDisplay;
- (instancetype)initSetting:(NSString *)settingKey label:(NSString *)label link:(NSString *)link;
- (instancetype)initSetting:(NSString *)settingKey label:(NSString *)label recipient:(NSString *)recipient title:(NSString *)title;

- (instancetype)initOptionSetting:(NSString *)settingKey value:(NSString *)value;
- (instancetype)initOptionSetting:(NSString *)settingKey canDisplay:(BOOL)canDisplay value:(NSString *)value;

- (instancetype)initSwitchSetting:(NSString *)settingKey value:(BOOL)value;
- (instancetype)initSwitchSetting:(NSString *)settingKey canDisplay:(BOOL)canDisplay value:(BOOL)value;

- (void)save;
- (nullable NSNumber *)loadSwitchValue;
- (nullable NSString *)loadSelectionValue;
- (nullable NSNumber *)loadSelectionValueCode;
- (nullable NSString *)loadLink;

- (void)updateSettingToMatch:(Setting *)setting;

+ (NSString *)getSettingOptionValueForNumber:(NSNumber *)number andSettingKey:(NSString *)settingKey;

@end

NS_ASSUME_NONNULL_END
