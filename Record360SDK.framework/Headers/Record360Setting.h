//
// Copyright © 2016 Record360. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface Record360Setting : NSObject

@property (nonatomic, copy, readonly, nonnull) NSString *settingKey;
@property (nonatomic, readonly, nonnull) NSNumber *settingType;
@property (nonatomic, copy, readonly, nonnull) NSString *label;
@property (nonatomic, readonly, nonnull) NSNumber *canDisplay;

- (instancetype)initSetting:(nonnull NSString *)settingKey;
- (instancetype)initSetting:(nonnull NSString *)settingKey label:(nonnull NSString *)label;
- (instancetype)initSetting:(nonnull NSString *)settingKey canDisplay:(BOOL)canDisplay;
- (instancetype)initSetting:(nonnull NSString *)settingKey label:(nonnull NSString *)label canDisplay:(BOOL)canDisplay;
- (instancetype)initSetting:(nonnull NSString *)settingKey label:(nonnull NSString *)label link:(nonnull NSString *)link;
- (instancetype)initSetting:(nonnull NSString *)settingKey label:(nonnull NSString *)label recipient:(nonnull NSString *)recipient title:(nonnull NSString *)title;

- (instancetype)initOptionSetting:(nonnull NSString *)settingKey value:(nonnull NSString *)value;
- (instancetype)initOptionSetting:(nonnull NSString *)settingKey canDisplay:(BOOL)canDisplay value:(nonnull NSString *)value;

- (instancetype)initSwitchSetting:(nonnull NSString *)settingKey value:(BOOL)value;
- (instancetype)initSwitchSetting:(nonnull NSString *)settingKey canDisplay:(BOOL)canDisplay value:(BOOL)value;

- (void)save;
- (nullable NSNumber *)loadSwitchValue;
- (nullable NSString *)loadSelectionValue;
- (nullable NSNumber *)loadSelectionValueCode;
    
+ (nonnull NSString *)getSettingOptionValueForNumber:(nonnull NSNumber *)number andSettingKey:(nonnull NSString *)settingKey;

@end
