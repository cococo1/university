//
//  FibonacciGenerator.h
//  MVCExample1
//
//  Created by Maxim Chetrusca on 2/4/14.
//  Copyright (c) 2014 Maxim Chetrusca. All rights reserved.
//

#import <Foundation/Foundation.h>

//The model is way to simple to implement the observer pattern;
@interface FibonacciGenerator : NSObject

-(long long) giveMeNextFibonnaci;

@end
