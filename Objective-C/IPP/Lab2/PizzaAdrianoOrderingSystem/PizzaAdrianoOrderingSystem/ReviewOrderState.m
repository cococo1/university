//
//  ReviewOrderState.m
//  PizzaAdrianoOrderingSystem
//
//  Created by Maxim Chetrusca on 2/1/14.
//  Copyright (c) 2014 Maxim Chetrusca. All rights reserved.
//

#import "ReviewOrderState.h"

@implementation ReviewOrderState

-(id) initWithTabLabel:(NSString*)tabLabel
{
    self = [super initWithStateId:ReviewOrderStateId tabLabel:tabLabel];
    return self;
}

-(id) initWithStateId:(PizzaOrderingStateId)stateId
             tabLabel:(NSString *)tabLabel
{
    [NSException raise:@"do not use this init" format:nil];
    return nil;
}

-(NSDictionary*)giveOrderInfoForName:(NSString*)name
                         extraCheese:(NSArray*)cheese
                           extraMeat:(NSArray*)meat
                     extraVegetables:(NSArray*)vegetables
                     priceCalculator:(id<PriceCalculatorProtocol>)calculator
{
    NSMutableDictionary* order = [[NSMutableDictionary alloc]init];
    order[ORDER_NAME] = name;
    
    NSMutableArray* ingredients = [[NSMutableArray alloc]init];
    [ingredients addObject:@"Pizza"];
    [ingredients addObjectsFromArray:cheese];
    [ingredients addObjectsFromArray:meat];
    [ingredients addObjectsFromArray:vegetables];
    order[ORDER_INGREDIENTS] = ingredients;
    
    NSMutableArray* prices = [[NSMutableArray alloc]init];
    for (NSString* ingredient in ingredients)
    {
        [prices addObject:calculator.pricelist.pricelist[ingredient]];
    }
    order[ORDER_PRICES] = prices;
    
    order[ORDER_PRICE] = [NSNumber numberWithFloat: [calculator computePriceGivenIngredents:ingredients]];
    
    
    return order;
}

@end
