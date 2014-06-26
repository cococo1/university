//
//  PriceList.h
//  PizzaAdrianoOrderingSystem
//
//  Created by Maxim Chetrusca on 2/2/14.
//  Copyright (c) 2014 Maxim Chetrusca. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface Pricelist : NSObject

@property (strong, nonatomic, readonly) NSDictionary* pricelist;
@property (strong, nonatomic, readonly) NSArray* cheese;
@property (strong, nonatomic, readonly) NSArray* meat;
@property (strong, nonatomic, readonly) NSArray* vegetables;

@end
