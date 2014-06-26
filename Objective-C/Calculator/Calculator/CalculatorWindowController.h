//
//  CalculatorWindowController.h
//  Calculator
//
//  Created by Maxim Chetrusca on 3/23/13.
//  Copyright (c) 2013 Maxim Chetrusca. All rights reserved.
//

#import <Cocoa/Cocoa.h>

#define MAX_NUMBER_OF_DISPLAYED_DIGITS 20

@interface CalculatorWindowController : NSWindowController

@property (weak) IBOutlet NSTextField *resultTextField;

- (IBAction)digitPressed:(NSButton*)sender;

- (IBAction)operationPressed:(NSButton*)sender;

- (IBAction)equalPressed:(NSButton*)sender;

- (IBAction)clearPressed:(NSButton*)sender;

//considered a number introduction rather than an operation
- (IBAction)changeSignPressed:(NSButton *)sender;

//the only unary operator
- (IBAction)sqrtPressed:(NSButton *)sender;

@end
