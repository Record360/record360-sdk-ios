//
//  Record360AuthAlerts.h
//  Record360SDK
//

#import <UIKit/UIKit.h>

@class User;
@class Inspection;

NS_ASSUME_NONNULL_BEGIN

@interface Record360AuthAlerts : NSObject

+ (void)showPriorUserAndInspectionAlert:(UIViewController *)rootViewController
                                   user:(User *)oldUser
                             inspection:(Inspection *)oldInspection
                         confirmHandler:(void (^)(UIAlertAction *action))confirmHandler
                          cancelHandler:(void (^)(UIAlertAction *action))cancelHandler;

+ (void)showPriorUserAlert:(UIViewController *)rootViewController
                   oldUser:(User *)oldUser
            confirmHandler:(void (^)(UIAlertAction *action))confirmHandler
             cancelHandler:(void (^)(UIAlertAction *action))cancelHandler;

+ (void)showPriorInspectionAlert:(UIViewController *)controller
              newReferenceNumber:(NSString *)newReferenceNumber
                   oldInspection:(Inspection *)oldInspection
                  confirmHandler:(void (^)(UIAlertAction *action))confirmHandler
                   cancelHandler:(void (^)(UIAlertAction *action))cancelHandler;

@end

NS_ASSUME_NONNULL_END
