//
// Copyright © 2016 Record360. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface Record360Setting : NSObject

@property (nonatomic, copy, readonly, nonnull) NSString *settingKey;
@property (nonatomic, readonly, nonnull) NSNumber *settingType;
@property (nonatomic, copy, readonly, nonnull) NSString *label;
@property (nonatomic, readonly, nonnull) NSNumber *canDisplay;

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

- (instancetype)initSliderSetting:(NSString *)settingKey value:(float)value;
- (instancetype)initSliderSetting:(NSString *)settingKey canDisplay:(BOOL)canDisplay value:(float)value;

- (void)save;
- (nullable NSNumber *)loadSwitchValue;
- (nullable NSString *)loadSelectionValue;
- (nullable NSNumber *)loadSelectionValueCode;
- (nullable NSString *)loadLink;
    
+ (NSString *)getSettingOptionValueForNumber:(NSNumber *)number andSettingKey:(NSString *)settingKey;

@end

NS_ASSUME_NONNULL_END
