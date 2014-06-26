//
//  AppDelegate.m
//  Calculator
//
//  Created by Maxim Chetrusca on 3/23/13.
//  Copyright (c) 2013 Maxim Chetrusca. All rights reserved.
//

#import "AppDelegate.h"
#import "CalculatorWindowController.h"

@implementation AppDelegate

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification
{

    // Insert code here to initialize your application
    CalculatorWindowController *calculator=[[CalculatorWindowController alloc]init];
    [calculator showWindow:calculator.window];
}

@end
