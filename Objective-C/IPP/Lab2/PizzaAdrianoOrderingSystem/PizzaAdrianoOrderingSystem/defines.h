//
//  defines.h
//  PizzaAdrianoOrderingSystem
//
//  Created by Maxim Chetrusca on 1/31/14.
//  Copyright (c) 2014 Maxim Chetrusca. All rights reserved.
//

#ifndef PizzaAdrianoOrderingSystem_defines_h
#define PizzaAdrianoOrderingSystem_defines_h

typedef enum {
    BeforeOrderStateId,
    InputNameStateId,
    PizzaComponentSelectionStateId,
    ReviewOrderStateId,
    FinalizeOrderStateId
}PizzaOrderingStateId;

typedef enum {
    Cheese,
    Meat,
    Vegetables
}IngredientType;

#define MAX_CHEESE_INGREDIENTS_ALLOWED 3
#define MAX_MEAT_INGREDIENTS_ALLOWED 2
#define MAX_VEGETABLE_INGREDIENTS_ALLOWED 5

#define ORDER_NAME @"name"
#define ORDER_PRICE @"finalPrice"
#define ORDER_INGREDIENTS @"ingredients"
#define ORDER_PRICES @"prices"





#endif
