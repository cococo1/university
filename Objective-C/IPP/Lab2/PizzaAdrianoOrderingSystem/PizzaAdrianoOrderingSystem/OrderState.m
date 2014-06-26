//
//  BeforeOrderState.m
//  PizzaAdrianoOrderingSystem
//
//  Created by Maxim Chetrusca on 2/1/14.
//  Copyright (c) 2014 Maxim Chetrusca. All rights reserved.
//

#import "OrderState.h"

@interface OrderState()




@end

@implementation OrderState

@synthesize completed = _completed;
@synthesize stateId = _stateId;
@synthesize displayed = _displayed;
@synthesize tabLabel = _tabLabel;

-(void) setDisplayed:(BOOL)displayed
{
    _displayed = displayed;
    if (displayed)
    {
        _completed = YES;
    }
}

-(id) initWithStateId:(PizzaOrderingStateId)stateId
             tabLabel:(NSString *)tabLabel
{
    self = [super init];
    if (self)
    {
        if (stateId < BeforeOrderStateId || stateId > FinalizeOrderStateId)
        {
            [NSException raise:@"No such state" format:nil];
        }
        _stateId = stateId;
        _displayed = NO;
        _completed = NO;
        _tabLabel = tabLabel;
    }
    return self;
}

-(id) init
{
    [NSException raise:@"Use a different init" format:nil];
    return nil;
}

-(id) initWithTabLabel:(NSString*)tabLabel
{
    [NSException raise:@"Use a different init" format:nil];
    return nil;
}



@end
