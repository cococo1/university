//
//  PriceCalculatorProtocol.h
//  PizzaAdrianoOrderingSystem
//
//  Created by Maxim Chetrusca on 2/1/14.
//  Copyright (c) 2014 Maxim Chetrusca. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "Pricelist.h"

@protocol PriceCalculatorProtocol <NSObject>


-(float) computePriceGivenIngredents:(NSArray*)ingredients;
@property (nonatomic,strong, readonly) Pricelist* pricelist;


@end
