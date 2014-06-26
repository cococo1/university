//
//  ComponentSelectionState.h
//  PizzaAdrianoOrderingSystem
//
//  Created by Maxim Chetrusca on 2/1/14.
//  Copyright (c) 2014 Maxim Chetrusca. All rights reserved.
//

#import "OrderState.h"

@interface ComponentSelectionState : OrderState

@property (nonatomic, readonly) BOOL extraIngredientsSelected;
@property (nonatomic, readonly) BOOL cheesesSelected;
@property (nonatomic, readonly) BOOL meatSelected;
@property (nonatomic, readonly) BOOL vegetablesSelected;

@property (nonatomic, strong, readonly) NSMutableArray* cheeses;
@property (nonatomic, strong, readonly) NSMutableArray* meat;
@property (nonatomic, strong, readonly) NSMutableArray* vegetables;

-(BOOL) addIngredient:(NSString*)ingredient
               ofType:(IngredientType)ingredientType;
-(BOOL) removeIngredient:(NSString*)ingredient;

@end
