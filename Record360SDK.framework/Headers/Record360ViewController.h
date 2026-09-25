//
//  Record360ViewController.h
//  Record360SDK
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@interface Record360ViewController : UIViewController

- (void)present:(UIViewController *)viewController;

- (void)showSpinner;
- (void)hideSpinner;

@end

NS_ASSUME_NONNULL_END
