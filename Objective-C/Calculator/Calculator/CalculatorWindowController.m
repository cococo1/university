//
//  CalculatorWindowController.m
//  Calculator
//
//  Created by Maxim Chetrusca on 3/23/13.
//  Copyright (c) 2013 Maxim Chetrusca. All rights reserved.
//

#import "CalculatorWindowController.h"
#import "CalculatorBrain.h"


@interface CalculatorWindowController ()

@property (nonatomic,strong) CalculatorBrain* brain;
@property (nonatomic,getter = isDotPressed) BOOL dotPressed;
@property (nonatomic,strong) NSString* operation;
@property (nonatomic, getter =  isTypingANumber) BOOL typingANumber;


@end

@implementation CalculatorWindowController

-(id)init
{
    self = [super initWithWindowNibName:@"MainMenu"];
    if (self)
    {
        
    }
    return self;
}

- (void)windowDidLoad
{
    [super windowDidLoad];

    
    self.dotPressed = NO;
    self.typingANumber = NO;
}


-(CalculatorBrain*) brain
{
    if (! _brain) {
        _brain = [[CalculatorBrain alloc]init];
    }
    return _brain;
}

-(void) keyDown:(NSEvent *)theEvent
{
    NSString *string = [theEvent characters];
    NSButton *button = [[NSButton alloc]init];
    button.title = string;
//    NSLog(@"%@",string);
    unichar c = [string characterAtIndex:0];
    
    NSSet *setOfOperations = [NSSet setWithObjects:@"+",@"-",@"*", @"/", @"^", nil];
    if (isdigit(c) || c == '.')
    {
//        NSLog(@"is digit");
        [self digitPressed:button];
    }
    else if ([setOfOperations containsObject:string])
    {
//        NSLog(@"it's an operation");
        
        button.title = string;
        [self operationPressed:button];
    }
    else if (c == NSDeleteCharacter)
    {
//        NSLog(@"Delete pressed");
        [self clearPressed:button];
    }
    else if (c == NSCarriageReturnCharacter || c == NSEnterCharacter || c == '=')
    {
//        NSLog(@"Return pressed");
        [self equalPressed:button];
    }
}

- (IBAction)digitPressed:(NSButton*)sender
{
    NSString* string = self.resultTextField.stringValue;
//    NSLog(@"digit pressed");
    if (self.isTypingANumber)
    {
        if ([sender.title isEqualToString:@"."])
        {
            if (! self.isDotPressed) {
                string = [self.resultTextField.stringValue stringByAppendingString:sender.title];

//                [self.resultTextField setStringValue:[self.resultTextField.stringValue stringByAppendingString:sender.title]];
                self.dotPressed = YES;
            }
        }
        else	
        {
            string = [self.resultTextField.stringValue stringByAppendingString:sender.title];
//            [self.resultTextField setStringValue:[self.resultTextField.stringValue stringByAppendingString:sender.title]];
        }
    }
    else
    {
        if ([sender.title isEqualToString:@"."])
        {
//            [self.resultTextField setStringValue:sender.title];
            self.dotPressed = YES;
        }
//        else
//        {
//            string = sender.title;
////            [self.resultTextField setStringValue:sender.title];
//        }
        string = sender.title;
        self.typingANumber = YES;
    }
    
    if (string.length < MAX_NUMBER_OF_DISPLAYED_DIGITS ) {
        self.resultTextField.stringValue = string;
    }
}


- (IBAction)operationPressed:(NSButton*)sender
{
//    NSLog(@"operation pressed");
    if (! self.brain.operand1IsSet)
    {
        self.brain.operand1 = [self.resultTextField.stringValue doubleValue];
    }
    else if (! self.brain.operand2IsSet)
    {
        self.brain.operand2 = [self.resultTextField.stringValue doubleValue];
    }
    
    if (self.brain.operand1IsSet && self.brain.operand2IsSet)
    {
        [self equalPressed:nil];
        self.brain.operand1 = [self.resultTextField.stringValue doubleValue];
    }
    
    self.operation = sender.title;
    
    self.dotPressed = NO;
    self.typingANumber = NO;
}


- (IBAction)equalPressed:(NSButton*)sender
{
//    NSLog(@"equal pressed");
    if (! self.brain.operand1IsSet)
    {
        self.brain.operand1 = [self.resultTextField.stringValue doubleValue];
    }
    else if (! self.brain.operand2IsSet)
    {
        self.brain.operand2 = [self.resultTextField.stringValue doubleValue];
    }
    double result = [self.brain performOperation:self.operation];
    NSString *string = [NSString stringWithFormat:@"%f",result];
    if ([string isEqualToString:@"inf"])
    {
        string = @"error";
        [self.brain reset];
        self.typingANumber = NO;
        self.dotPressed = NO;
        self.operation=nil;
    }
    
    if ([string length] > MAX_NUMBER_OF_DISPLAYED_DIGITS+6)//after floating point
    {
        string = @"results too big";
        [self.brain reset];
        self.typingANumber = NO;
        self.dotPressed = NO;
        self.operation=nil;
    }
    
    [self.resultTextField setStringValue:string];
    self.typingANumber = NO;
}

- (IBAction)clearPressed:(NSButton*)sender
{
//    NSLog(@"clearPressed");
    [self.resultTextField setStringValue:@"0"];
    [self.brain reset];
    self.typingANumber = NO;
    self.dotPressed = NO;
    self.operation=nil;
}

- (IBAction)changeSignPressed:(NSButton *)sender
{
    double operand = [self.resultTextField.stringValue doubleValue];
    operand = [self.brain invertSign:operand];
    [self.resultTextField setStringValue:[NSString stringWithFormat:@"%f",operand]];
}

- (IBAction)sqrtPressed:(NSButton *)sender
{
    if (self.brain.operand1IsSet && self.typingANumber)
    {
        [self equalPressed:nil];
    }
    self.brain.operand1 = [self.resultTextField.stringValue doubleValue];
    double result = [self.brain performOperation:sender.title];
    NSString *string = [NSString stringWithFormat:@"%f",result];
    if ([string isEqualToString:@"nan"])
    {
        string = @"error";
        [self.brain reset];
        self.typingANumber = NO;
        self.dotPressed = NO;
        self.operation=nil;
    }
    [self.resultTextField setStringValue:string];
    self.typingANumber = NO;

}

@end
