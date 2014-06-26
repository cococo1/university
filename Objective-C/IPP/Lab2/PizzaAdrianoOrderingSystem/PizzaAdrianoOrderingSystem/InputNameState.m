//
//  InputNameState.m
//  PizzaAdrianoOrderingSystem
//
//  Created by Maxim Chetrusca on 2/1/14.
//  Copyright (c) 2014 Maxim Chetrusca. All rights reserved.
//

#import "InputNameState.h"

@implementation InputNameState

-(void) setName:(NSString *)name
{
    if (self.name && (![self.name isEqualToString:@""]))
    {
        _completed = YES;
    }
    else
    {
        _completed = NO;
    }
   _name = name;
    
}

-(BOOL) isCompleted
{
    _completed = (self.name && (![self.name isEqualToString:@""]));
    
    return _completed;
}

-(id) initWithTabLabel:(NSString*)tabLabel
{
    self = [super initWithStateId:InputNameStateId tabLabel:tabLabel];
    return self;
}

-(id) initWithStateId:(PizzaOrderingStateId)stateId
             tabLabel:(NSString *)tabLabel
{
    [NSException raise:@"do not use this init" format:nil];
    return nil;
}

@end
