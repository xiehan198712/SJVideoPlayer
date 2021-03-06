//
//  SJEdgeControlButtonItem.h
//  SJVideoPlayer
//
//  Created by BlueDancer on 2018/10/19.
//  Copyright © 2018 畅三江. All rights reserved.
//

#import <UIKit/UIKit.h>
typedef NSInteger SJEdgeControlButtonItemTag;
@protocol SJEdgeControlButtonItemDelegate;
@class SJBaseVideoPlayer;

typedef struct SJEdgeInsets {
    // 前后间距
    CGFloat front, rear;
} SJEdgeInsets;

UIKIT_STATIC_INLINE SJEdgeInsets SJEdgeInsetsMake(CGFloat left, CGFloat right) {
    SJEdgeInsets insets = {left, right};
    return insets;
}

NS_ASSUME_NONNULL_BEGIN
@interface SJEdgeControlButtonItem : NSObject
/// 49 * 49
- (instancetype)initWithImage:(nullable UIImage *)image
                       target:(nullable id)target
                       action:(nullable SEL)action
                          tag:(SJEdgeControlButtonItemTag)tag;

/// 49 * title.size.width
- (instancetype)initWithTitle:(nullable NSAttributedString *)title
                       target:(nullable id)target
                       action:(nullable SEL)action
                          tag:(SJEdgeControlButtonItemTag)tag;

/// 49 * customView.size.width
- (instancetype)initWithCustomView:(nullable __kindof UIView *)customView
                               tag:(SJEdgeControlButtonItemTag)tag;

@property (nonatomic) SJEdgeInsets insets; // 左右间隔, 默认{0, 0}
@property (nonatomic) SJEdgeControlButtonItemTag tag;
@property (nonatomic, strong, nullable) __kindof UIView *customView;
@property (nonatomic, strong, nullable) NSAttributedString *title;
@property (nonatomic, strong, nullable) UIImage *image;
@property (nonatomic, getter=isHidden) BOOL hidden;
@property (nonatomic, weak, nullable) id target;
@property (nonatomic, nullable) SEL action;
- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new  NS_UNAVAILABLE;
@property (nonatomic) BOOL fill; // 当想要填充剩余空间时, 可以设置为`Yes`. 注意: 在`adapter`中, 此`item`只能存在一个. 
@property (nonatomic, weak, nullable) id<SJEdgeControlButtonItemDelegate> delegate;

- (void)addTarget:(id)target action:(nonnull SEL)action;
@end

@protocol SJEdgeControlButtonItemDelegate <NSObject>
- (void)updatePropertiesIfNeeded:(SJEdgeControlButtonItem *)item videoPlayer:(__kindof SJBaseVideoPlayer *)player;
@end



typedef enum : NSUInteger {
    SJButtonItemPlaceholderType_Unknown,
    SJButtonItemPlaceholderType_49x49,              // 49 * 49
    SJButtonItemPlaceholderType_49xAutoresizing,    // 49 * 自适应大小
    SJButtonItemPlaceholderType_49xFill,            // 49 * 填充父视图剩余空间
    SJButtonItemPlaceholderType_49xSpecifiedSize,   // 49 * 指定尺寸(水平布局时, 49为高度, `指定尺寸`为宽度. 相反的, 垂直布局时, 49为宽度, `指定尺寸`为高度)
} SJButtonItemPlaceholderType;
/// 占位Item
/// 先占好位置, 后更新属性
@interface SJEdgeControlButtonItem(Placeholder)
+ (instancetype)placeholderWithType:(SJButtonItemPlaceholderType)placeholderType tag:(SJEdgeControlButtonItemTag)tag;
+ (instancetype)placeholderWithSize:(CGFloat)size tag:(SJEdgeControlButtonItemTag)tag; // `placeholderType == SJButtonItemPlaceholderType_49xSpecifiedSize`
@property (nonatomic, readonly) SJButtonItemPlaceholderType placeholderType;
@property (nonatomic) CGFloat size;
@end
NS_ASSUME_NONNULL_END
