//
//  OrderingSystem.h
//  PizzaAdrianoOrderingSystem
//
//  Created by Maxim Chetrusca on 1/31/14.
//  Copyright (c) 2014 Maxim Chetrusca. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "OrderSystemProtocol.h"
#import "StateProtocol.h"

@protocol OrderSystemDisplayDelegate  <NSObject>

-(void) displayState:(id<StateProtocol>)state;
-(NSString*) giveName;
-(void) displayAlertWithText:(NSString*)text;
-(void) disable:(IngredientType)type;
-(void) enable:(IngredientType)type;

@end

@interface OrderSystem : NSObject <OrderSystemProtocol>

#pragma mark OrderSystemProtocol:
-(void) start;
-(BOOL) goOnWithOrder;
-(BOOL) addVegetable:(NSString*)vegetable;
-(BOOL) addCheese:(NSString*)cheese;
-(BOOL) addMeat:(NSString*)meat;
-(BOOL) removeIngredient:(NSString*)ingredient;
-(NSDictionary*) giveOrderInformation;
@property (nonatomic, readonly) int orderId;



-(id) initWithDisplay:(id<OrderSystemDisplayDelegate>)display;
@property (nonatomic, weak) id<OrderSystemDisplayDelegate> display;


@end
