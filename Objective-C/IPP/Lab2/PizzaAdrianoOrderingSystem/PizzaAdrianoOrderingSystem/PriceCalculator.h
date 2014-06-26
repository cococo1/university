//
//  PriceCalculator.h
//  PizzaAdrianoOrderingSystem
//
//  Created by Maxim Chetrusca on 2/1/14.
//  Copyright (c) 2014 Maxim Chetrusca. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "PriceCalculatorProtocol.h"

@interface PriceCalculator : NSObject <PriceCalculatorProtocol>

#pragma mark PriceCalculatorProtocol
-(float) computePriceGivenIngredents:(NSArray*)ingredients;
@property (nonatomic,strong, readonly) Pricelist* pricelist;


@end
