//
//  DisplayView.h
//  MVCExample1
//
//  Created by Maxim Chetrusca on 2/4/14.
//  Copyright (c) 2014 Maxim Chetrusca. All rights reserved.
//

#import <UIKit/UIKit.h>

@protocol ControllerProtocol <NSObject>

-(void)handleButtonPress;

@end

@interface DisplayView : UIView

@property (nonatomic, strong) UILabel* label;
@property (nonatomic, strong) UIButton* button;
@property (nonatomic, weak) id<ControllerProtocol> controller;


@end
