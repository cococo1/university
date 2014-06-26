//
//  OrderingSystemProtocol.h
//  PizzaAdrianoOrderingSystem
//
//  Created by Maxim Chetrusca on 1/31/14.
//  Copyright (c) 2014 Maxim Chetrusca. All rights reserved.
//

#import <Foundation/Foundation.h>

@protocol OrderSystemProtocol <NSObject>

-(void) start;
-(BOOL) goOnWithOrder; 
-(BOOL) addVegetable:(NSString*)vegetable;
-(BOOL) addCheese:(NSString*)cheese;
-(BOOL) addMeat:(NSString*)meat;
-(BOOL) removeIngredient:(NSString*)ingredient;
-(NSDictionary*) giveOrderInformation;

@property (nonatomic, readonly) int orderId;

@end
