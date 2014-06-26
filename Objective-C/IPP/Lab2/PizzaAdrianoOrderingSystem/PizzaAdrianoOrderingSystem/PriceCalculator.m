//
//  PriceCalculator.m
//  PizzaAdrianoOrderingSystem
//
//  Created by Maxim Chetrusca on 2/1/14.
//  Copyright (c) 2014 Maxim Chetrusca. All rights reserved.
//

#import "PriceCalculator.h"

@interface PriceCalculator()

@end

@implementation PriceCalculator

@synthesize pricelist = _pricelist;

-(id) init
{
    self = [super init];
    if (self)
    {
        _pricelist = [[Pricelist alloc]init];
    }
    return self;
}


-(float) computePriceGivenIngredents:(NSArray *)ingredients
{
    float price = 0;
    for (id object in ingredients)
    {
        NSString* ingredient = object;
        if (! [self.pricelist.pricelist objectForKey:ingredient])
        {
            [NSException raise:@"No such ingredient" format:nil];
        }
        price += [((NSNumber*)self.pricelist.pricelist[ingredient]) floatValue];
    }
    return price;
}

@end
