//
//  CalculatorBrain.h
//  Calculator
//
//  Created by Maxim Chetrusca on 3/23/13.
//  Copyright (c) 2013 Maxim Chetrusca. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface CalculatorBrain : NSObject

@property (nonatomic) double operand1;
@property (nonatomic) double operand2;
@property (nonatomic) BOOL operand1IsSet;
@property (nonatomic) BOOL operand2IsSet;

//Resets the brain:
-(void) reset;

//Returns the result of the operation
-(double) performOperation:(NSString*)operation;

-(double) invertSign:(double)operand;

@end
