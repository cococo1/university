//
//  ComponentSelectionState.m
//  PizzaAdrianoOrderingSystem
//
//  Created by Maxim Chetrusca on 2/1/14.
//  Copyright (c) 2014 Maxim Chetrusca. All rights reserved.
//

#import "ComponentSelectionState.h"
#import "Pricelist.h"

@implementation ComponentSelectionState

-(id) initWithTabLabel:(NSString*)tabLabel
{
    self = [super initWithStateId:PizzaComponentSelectionStateId tabLabel:tabLabel];
    if (self)
    {
        _extraIngredientsSelected = NO;
        _cheesesSelected = NO;
        _meatSelected = NO;
        _vegetablesSelected = NO;
        _cheeses = [[NSMutableArray alloc]init];
        _meat = [[NSMutableArray alloc]init];
        _vegetables = [[NSMutableArray alloc]init];
        
    }
    return self;
}

-(id) initWithStateId:(PizzaOrderingStateId)stateId
             tabLabel:(NSString *)tabLabel
{
    [NSException raise:@"do not use this init" format:nil];
    return nil;
}

-(BOOL) addIngredient:(NSString*)ingredient ofType:(IngredientType)ingredientType
{
    Pricelist *p = [[Pricelist alloc]init];
    if (ingredientType < Cheese || ingredientType > Vegetables)
    {
        [NSException raise:@"unknown ingredient" format:nil];
    }
    _extraIngredientsSelected = YES;
    switch (ingredientType)
    {
        case Cheese:
            if ([self.cheeses count] < MAX_CHEESE_INGREDIENTS_ALLOWED)
            {
                if (![p.cheese containsObject:ingredient])
                {
                    [NSException raise:@"There is no such cheese ingredient" format:nil];
                }
                [self.cheeses addObject:ingredient];
                _cheesesSelected = YES;
            }
            else
            {
                return NO;
            }
            break;
            
            
            
        case Meat:
            if ([self.meat count] < MAX_MEAT_INGREDIENTS_ALLOWED)
            {
                if (![p.meat containsObject:ingredient])
                {
                    [NSException raise:@"There is no such meat ingredient" format:nil];
                }
                [self.meat addObject:ingredient];
                _meatSelected = YES;
            }
            else
            {
                return NO;
            }
            break;
            
            
            
        case Vegetables:
            if ([self.vegetables count] < MAX_VEGETABLE_INGREDIENTS_ALLOWED)
            {
                if (![p.vegetables containsObject:ingredient])
                {
                    [NSException raise:@"There is no such vegetable ingredient" format:nil];
                }
                [self.vegetables addObject:ingredient];
                _vegetablesSelected = YES;
            }
            else
            {
                return NO;
            }
            break;
            
            
        default:
            [NSException raise:@"unimplemented ingredient yet." format:nil];
    }
    return YES;
    
}

-(BOOL) removeIngredient:(NSString*)ingredient
{
    BOOL found = NO;
    for (NSString* ing in self.cheeses)
    {
        if ([ing isEqualToString:ingredient])
        {
            found = YES;
            break;
        }
    }
    if (found)
    {
        [self.cheeses removeObject:ingredient];
        return YES;
    }
    
    
    for (NSString* ing in self.meat)
    {
        if ([ing isEqualToString:ingredient])
        {
            found = YES;
            break;
        }
    }
    if (found)
    {
        [self.meat removeObject:ingredient];
        return YES;
    }
    
    
    
    for (NSString* ing in self.vegetables)
    {
        if ([ing isEqualToString:ingredient])
        {
            found = YES;
            break;
        }
    }
    if (found)
    {
        [self.vegetables removeObject:ingredient];
        return YES;
    }
    
    return NO;
}

@end
