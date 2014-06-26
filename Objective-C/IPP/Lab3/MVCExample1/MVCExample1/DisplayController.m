//
//  DisplayController.m
//  MVCExample1
//
//  Created by Maxim Chetrusca on 2/4/14.
//  Copyright (c) 2014 Maxim Chetrusca. All rights reserved.
//

#import "DisplayController.h"

@implementation DisplayController

-(id) init
{
    self = [super init];
    if (self)
    {
        _dataGenerator = [[FibonacciGenerator alloc] init];
    }
    return self;
}

-(void) viewDidLoad
{
    [super viewDidLoad];
    self.displayView = [[DisplayView alloc] initWithFrame:self.view.frame];
    [self.view addSubview:self.displayView];
    self.displayView.label.text = [NSString stringWithFormat:@"%lli",[self.dataGenerator giveMeNextFibonnaci]];
    self.displayView.button.titleLabel.text = @"Next number";
    self.displayView.controller = self;
//    self.view
}


-(void)handleButtonPress
{
    self.displayView.label.text = [NSString stringWithFormat:@"%lli",[self.dataGenerator giveMeNextFibonnaci]];
}

@end
