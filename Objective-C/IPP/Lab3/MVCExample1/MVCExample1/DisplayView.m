//
//  DisplayView.m
//  MVCExample1
//
//  Created by Maxim Chetrusca on 2/4/14.
//  Copyright (c) 2014 Maxim Chetrusca. All rights reserved.
//

#import "DisplayView.h"

@implementation DisplayView

- (id)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    if (self)
    {
        // Initialization code
        // initilize all your UIView components
        _label = [[UILabel alloc]initWithFrame:CGRectMake(60, 50, 200, 44)];
        _label.text = @"Some label";
        [self addSubview:_label]; //add label to your custom view
        
        _button = [UIButton buttonWithType:UIButtonTypeRoundedRect];
        _button.frame =CGRectMake(60, 280, 200, 44);
        [_button setTitle:@"Some button" forState:UIControlStateNormal];

        [_button addTarget:self action:@selector(buttonPressed) forControlEvents:UIControlEventTouchUpInside];
        [self addSubview:_button];
    }
    return self;
}

-(void)buttonPressed
{
    [self.controller handleButtonPress];
}

@end
