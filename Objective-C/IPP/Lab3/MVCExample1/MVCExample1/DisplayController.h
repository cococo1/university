//
//  DisplayController.h
//  MVCExample1
//
//  Created by Maxim Chetrusca on 2/4/14.
//  Copyright (c) 2014 Maxim Chetrusca. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "DisplayView.h"
#import "FibonacciGenerator.h"

//This is a Page Controller and it is designed specifically for FibonacciGenerator and DisplayView
@interface DisplayController : UIViewController <ControllerProtocol>

@property (nonatomic, strong) FibonacciGenerator* dataGenerator; 
@property (nonatomic, strong) DisplayView* displayView;

-(void)handleButtonPress;

@end
