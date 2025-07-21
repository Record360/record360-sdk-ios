//
// Record360ViewController.h
// Record360SDK
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

typedef void (^PresentCompletionBlock)(void);

@interface Record360ViewController : UIViewController

- (void)present:(UIViewController *)viewController completion:(PresentCompletionBlock)completion;

- (void)showSpinner;
- (void)hideSpinner;

@end

NS_ASSUME_NONNULL_END
