//
//  PriceList.m
//  PizzaAdrianoOrderingSystem
//
//  Created by Maxim Chetrusca on 2/2/14.
//  Copyright (c) 2014 Maxim Chetrusca. All rights reserved.
//

#import "Pricelist.h"

@implementation Pricelist

-(id) init
{
    self = [super init];
    if (self)
    {
        _cheese = [[NSArray alloc] initWithObjects:
                   @"Feta",
                   @"Parmesan",
                   @"Mozarella",
                   @"Dor Blue",
                   @"Edam",
                   @"Brânză",
                   nil];
        _meat = [[NSArray alloc]initWithObjects:
                 @"Bacon",
                 @"Prosciutto",
                 @"Salami",
                 @"Chicken Breast",
                 @"Ham",
                 nil];
        _vegetables = [[NSArray alloc] initWithObjects:
                       @"Fresh mushrooms",
                       @"Smoked mushrooms",
                       @"Red onion",
                       @"Tomatoes",
                       @"Garlic",
                       @"Rucola",
                       @"Marinated Gogoshars",
                      @"Corn",
                       @"Parsley",
                       @"Chili pepper",
                       nil ];
                   
                   
        _pricelist = [[NSDictionary alloc] initWithObjectsAndKeys:
                      @(100),@"Pizza",
                      @(20),@"Feta",
                      @(15),@"Parmesan",
                      @(35),@"Mozarella",
                      @(99),@"Dor Blue",
                      @(1),@"Edam",
                      @(110),@"Brânză",
                      @(99),@"Bacon",
                      @(45),@"Prosciutto",
                      @(66),@"Salami",
                      @(11),@"Chicken Breast",
                      @(23),@"Ham",
                      @(15),@"Fresh mushrooms",
                      @(15),@"Smoked mushrooms",
                      @(5),@"Red onion",
                      @(15),@"Tomatoes",
                      @(5),@"Garlic",
                      @(20),@"Rucola",
                      @(35),@"Marinated Gogoshars",
                      @(25),@"Corn",
                      @(20),@"Parsley",
                      @(10),@"Chili pepper",
                      nil];
    }
    
    return self;
}


@end
