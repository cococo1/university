//
//  StateProtocol.h
//  PizzaAdrianoOrderingSystem
//
//  Created by Maxim Chetrusca on 2/1/14.
//  Copyright (c) 2014 Maxim Chetrusca. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "defines.h"

@protocol StateProtocol <NSObject>

@property (nonatomic, readonly) PizzaOrderingStateId stateId;
@property (nonatomic, getter = isCompleted, readonly) BOOL completed;
@property (nonatomic, getter = isDisplayed) BOOL displayed;
@property (nonatomic, strong, readonly) NSString* tabLabel;

@end
