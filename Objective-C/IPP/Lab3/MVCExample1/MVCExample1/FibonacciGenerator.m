//
//  FibonacciGenerator.m
//  MVCExample1
//
//  Created by Maxim Chetrusca on 2/4/14.
//  Copyright (c) 2014 Maxim Chetrusca. All rights reserved.
//

#import "FibonacciGenerator.h"

@interface FibonacciGenerator()

@property (nonatomic) long long number;
@property (nonatomic) long long previousNumber;

@end

@implementation FibonacciGenerator

-(id) init
{
    self = [super init];
    if (self)
    {
        _number = 1;
        _previousNumber = 0;
    }
    return self;
}

-(long long) giveMeNextFibonnaci
{
    long long result = self.number;
    
    long long temp = self.number;
    self.number = self.number + self.previousNumber;
    self.previousNumber = temp;
    
    return result;
}

@end
