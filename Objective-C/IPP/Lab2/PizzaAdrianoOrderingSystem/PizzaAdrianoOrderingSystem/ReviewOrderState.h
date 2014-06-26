//
//  ReviewOrderState.h
//  PizzaAdrianoOrderingSystem
//
//  Created by Maxim Chetrusca on 2/1/14.
//  Copyright (c) 2014 Maxim Chetrusca. All rights reserved.
//

#import "OrderState.h"
#import "PriceCalculatorProtocol.h"

@interface ReviewOrderState : OrderState

-(NSDictionary*)giveOrderInfoForName:(NSString*)name
                        extraCheese:(NSArray*)cheese
                           extraMeat:(NSArray*)meat
                     extraVegetables:(NSArray*)vegetables
                     priceCalculator:(id<PriceCalculatorProtocol>)calculator;


@end
