//
//  AppDelegate.m
//  TapTapTap
//
//  Created by Maxim Chetrusca on 11/25/13.
//  Copyright (c) 2013 Maxim Chetrusca. All rights reserved.
//

#import "AppDelegate.h"
#import "TapTapTapWindowController.h"

@implementation AppDelegate

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification
{
    // Insert code here to initialize your application
    TapTapTapWindowController *windowController = [[TapTapTapWindowController alloc] init];
    [windowController showWindow:windowController.window];
    
}

@end
