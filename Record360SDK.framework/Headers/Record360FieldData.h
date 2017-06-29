//
// Copyright (c) 2016 Record360. All rights reserved.
//

#import <Foundation/Foundation.h>

@protocol RLMInt;

@interface Record360FieldData : NSObject

@property (nonatomic) NSNumber <RLMInt>  *id;
@property (nonatomic) NSString *fieldName;
@property (nonatomic) NSString *fieldValue;

@end
