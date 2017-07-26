//
// Copyright (c) 2016 Record360. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface Record360Setting : NSObject

@property (nonatomic, copy, readonly) NSString *settingKey;
@property (nonatomic, readonly) NSNumber *settingType;
@property (nonatomic, copy, readonly) NSString *label;
@property (nonatomic, readonly) NSNumber *canDisplay;

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
- (NSNumber *)loadSwitchValue;
- (NSString *)loadSelectionValue;
- (NSNumber *)loadSelectionValueCode;
    
+ (NSString *)getSettingOptionValueForNumber:(NSNumber *)number andSettingKey:(NSString *)settingKey;

@end
