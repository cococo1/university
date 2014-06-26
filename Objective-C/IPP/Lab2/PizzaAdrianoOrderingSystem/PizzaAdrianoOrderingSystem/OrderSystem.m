//
//  OrderingSystem.m
//  PizzaAdrianoOrderingSystem
//
//  Created by Maxim Chetrusca on 1/31/14.
//  Copyright (c) 2014 Maxim Chetrusca. All rights reserved.
//

#import "OrderSystem.h"

#import "OrderState.h"
#import "InputNameState.h"
#import "ComponentSelectionState.h"
#import "ReviewOrderState.h"
#import "PriceCalculator.h"

@interface OrderSystem()

@property (nonatomic) int currentState;
@property (nonatomic, strong) NSArray* states;


@end

@implementation OrderSystem

@synthesize states = _states;
@synthesize orderId = _orderId;

-(void) setCurrentState:(int)currentState
{
    if ((currentState >= 0) && (currentState <= [self.states count]-1) )
    {
        _currentState = currentState;
    }
}

-(id) init
{
    [NSException raise:@"use a different init" format:nil];
    return nil;
}

-(id) initWithDisplay:(id<OrderSystemDisplayDelegate>)display
{
    self = [super init];
    if (self)
    {
        if (! [display conformsToProtocol:@protocol(OrderSystemDisplayDelegate)])
        {
            [NSException raise:@"Does not conform to protocol" format:@"%@",display];
        }
        _display = display;
        _orderId = 100;

        [self setup];

    }
    return self;
}

-(void) setup
{
    OrderState *beforeOrderState = [[OrderState alloc] initWithStateId:BeforeOrderStateId
                                                              tabLabel:@"Start new order"];
//    beforeOrderState.stateId = BeforeOrderStateId;
    InputNameState *inputNameState = [[InputNameState alloc]initWithTabLabel:@"Name"];
    ComponentSelectionState *componentSelectionState = [[ComponentSelectionState alloc]initWithTabLabel:@"Ingredients"];
    ReviewOrderState *reviewOrderState = [[ReviewOrderState alloc]initWithTabLabel:@"Review"];
    OrderState *finalizeOrderState = [[OrderState alloc] initWithStateId:FinalizeOrderStateId
                                                                tabLabel:@"Thank you!"];

    
    _states = [NSArray arrayWithObjects:
               beforeOrderState,
               inputNameState,
               componentSelectionState,
               reviewOrderState,
               finalizeOrderState,
               nil];
    
    _currentState = 0;
    _orderId++;
}

-(BOOL)goOnWithOrder
{
    if (self.currentState >= InputNameStateId) [self setName];
    id<StateProtocol> state = self.states[self.currentState];
    if (state.isCompleted)
    {
        self.currentState++;
        [self.display displayState:self.states[self.currentState]];
        state = self.states[self.currentState];
        state.displayed = YES;
        return YES;
    }
    else
    {
       [self.display displayAlertWithText:@"Please enter your name."];
        return NO;
    }
    return NO;

}

-(void) start
{
    if (self.currentState > 1)
    {
        [self setup];
    }
    [self.display displayState:self.states[self.currentState]];
    ((id<StateProtocol>) self.states[self.currentState]).displayed = YES;
    
}

-(void) setName
{
    InputNameState* state = (InputNameState*)self.states[1];
    state.name = [self.display giveName];
}


-(BOOL) addVegetable:(NSString*)vegetable
{
    ComponentSelectionState* state = (ComponentSelectionState*)self.states[2];
    BOOL a = [state addIngredient:vegetable ofType:Vegetables];
    if ([state.vegetables count] >= MAX_VEGETABLE_INGREDIENTS_ALLOWED)
    {
        [self.display disable:Vegetables];
    }
    return a;
}

-(BOOL) addCheese:(NSString*)cheese
{
    ComponentSelectionState* state = (ComponentSelectionState*)self.states[2];
    BOOL a = [state addIngredient:cheese ofType:Cheese];
    if ([state.cheeses count] >= MAX_CHEESE_INGREDIENTS_ALLOWED)
    {
        [self.display disable:Cheese];
    }
    return a;
}

-(BOOL) addMeat:(NSString*)meat
{
    ComponentSelectionState* state = (ComponentSelectionState*)self.states[2];
    BOOL a = [state addIngredient:meat ofType:Meat];
    if ([state.meat count] >= MAX_MEAT_INGREDIENTS_ALLOWED)
    {
        [self.display disable:Meat];
    }
    return a;
}

-(BOOL) removeIngredient:(NSString*)ingredient
{
    ComponentSelectionState* state = (ComponentSelectionState*)self.states[2];
    BOOL a = [state removeIngredient:ingredient];
    if ([state.cheeses count] < MAX_CHEESE_INGREDIENTS_ALLOWED) [self.display enable:Cheese];
    if ([state.meat count] < MAX_MEAT_INGREDIENTS_ALLOWED) [self.display enable:Meat];
    if ([state.vegetables count] < MAX_VEGETABLE_INGREDIENTS_ALLOWED) [self.display enable:Vegetables];
    return a;
}

-(NSDictionary*) giveOrderInformation
{
    [self setName];
    NSString* name = ((InputNameState*)self.states[1]).name;
    if (!name || [name isEqualToString:@""])
    {
        [NSException raise:@"Order should have name" format:nil];
    }
    NSArray* cheese = ((ComponentSelectionState*)self.states[2]).cheeses;
    NSArray* meat = ((ComponentSelectionState*)self.states[2]).meat;
    NSArray* vegetables = ((ComponentSelectionState*)self.states[2]).vegetables;
    
    return [((ReviewOrderState*)self.states[3]) giveOrderInfoForName:name
                                                         extraCheese:cheese
                                                           extraMeat:meat
                                                     extraVegetables:vegetables
                                                     priceCalculator:[[PriceCalculator alloc]init]];
}



@end
