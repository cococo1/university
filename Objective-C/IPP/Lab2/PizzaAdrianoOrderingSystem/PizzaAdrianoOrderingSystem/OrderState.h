//
//  BeforeOrderState.h
//  PizzaAdrianoOrderingSystem
//
//  Created by Maxim Chetrusca on 2/1/14.
//  Copyright (c) 2014 Maxim Chetrusca. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "StateProtocol.h"


@interface OrderState : NSObject <StateProtocol>
{
@protected
    BOOL _completed;
}

#pragma mark StateProtocol
@property (nonatomic, readonly) PizzaOrderingStateId stateId;
@property (nonatomic, getter = isCompleted, readonly) BOOL completed;
@property (nonatomic, getter = isDisplayed) BOOL displayed;
@property (nonatomic, strong, readonly) NSString* tabLabel;


-(id) initWithStateId:(PizzaOrderingStateId)stateId
             tabLabel:(NSString*)tabLabel;

-(id) initWithTabLabel:(NSString*)tabLabel; // use this init only in subclasses


@end
