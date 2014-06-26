//
//  CalculatorBrain.m
//  Calculator
//
//  Created by Maxim Chetrusca on 3/23/13.
//  Copyright (c) 2013 Maxim Chetrusca. All rights reserved.
//

#import "CalculatorBrain.h"
#import <math.h>

@implementation CalculatorBrain

-(void) setOperand1:(double)operand1
{
    _operand1 = operand1;
    self.operand1IsSet = YES;
}

-(void) setOperand2:(double)operand2
{
    _operand2 = operand2;
    self.operand2IsSet = YES;
}

-(double) invertSign:(double)operand
{
    if (operand)
    {
            return -1*operand;
    }
    else
    {
        return 0;
    }
}

-(double) performOperation:(NSString*)operation
{
    double result = 0.0f;
//    NSLog(@"%f %@ %f",self.operand1,operation,self.operand2);
    if ([operation isEqualToString:@"+"])
    {
        result = self.operand1 + self.operand2;
    }
    else if ([operation isEqualToString:@"−"] ||
             [operation isEqualToString:@"-"])
    {
       // NSLog(@"minus");
        result = self.operand1 - self.operand2;
    }
    else if ([operation isEqualToString:@"×"] ||
             [operation isEqualToString:@"*"])
    {
        result = self.operand1 * self.operand2;
    }
    else if ([operation isEqualToString:@"÷"] ||
             [operation isEqualToString:@"/"])
    {
        result = self.operand1 / self.operand2;
    }
//    else if ([operation isEqualToString:@"±"] && self.operand1)
//    {
//        result = self.operand1 * -1;
//    }
    else if ([operation isEqualToString:@"x^y"] ||
             [operation isEqualToString:@"^"])
    {
        result = pow(self.operand1,self.operand2);
    }
    else if ([operation isEqualToString:@"√"])
    {
        result = pow(self.operand1,.5f);
    }
    else if (!operation) result = self.operand1;
//    NSLog(@"result=%f",result);
    self.operand1IsSet = NO;
    self.operand2IsSet = NO;

    return result;
}

-(void) reset
{
    self.operand1 = 0.0f;
    self.operand2 = 0.0f;
    self.operand1IsSet = NO;
    self.operand2IsSet = NO;

}
@end
