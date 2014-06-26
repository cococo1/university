//
//  PriceCalculatorTests.m
//  PizzaAdrianoOrderingSystem
//
//  Created by Maxim Chetrusca on 2/1/14.
//  Copyright (c) 2014 Maxim Chetrusca. All rights reserved.
//

#import <XCTest/XCTest.h>
#import "PriceCalculator.h"

@interface PriceCalculatorTests : XCTestCase

@end

@implementation PriceCalculatorTests

- (void)setUp
{
    [super setUp];
    // Put setup code here. This method is called before the invocation of each test method in the class.
}

- (void)tearDown
{
    // Put teardown code here. This method is called after the invocation of each test method in the class.
    [super tearDown];
}

-(void)testInit
{
    XCTAssertNotNil([[PriceCalculator alloc]init], @"is nil");
    XCTAssertNoThrow([[PriceCalculator alloc] init], @"should not throw");
}

-(void)testPriceCalculator
{
    PriceCalculator* calculator = [[PriceCalculator alloc]init];
    float price = [calculator computePriceGivenIngredents:[NSArray arrayWithObjects:@"Pizza", @"Feta", @"Bacon", @"Fresh mushrooms", nil]];
    Pricelist *pl = [[Pricelist alloc] init];

    
    NSNumber* pizza = (NSNumber*)pl.pricelist[@"Pizza"];
    NSNumber* feta = (NSNumber*)pl.pricelist[@"Feta"];
    NSNumber* bacon = (NSNumber*)pl.pricelist[@"Bacon"];
    NSNumber* mush = (NSNumber*)pl.pricelist[@"Fresh mushrooms"];
    
    
    
    float price2 = ([pizza floatValue] + [feta floatValue] + [bacon floatValue] + [mush floatValue]);
    
    XCTAssertEqual(price, price2, @"prices differ");
    
    XCTAssertNoThrow([calculator computePriceGivenIngredents:nil], @"should return 0");
    XCTAssertEqualWithAccuracy([calculator computePriceGivenIngredents:nil], 0.0, 0.1, @"should return 0");
    XCTAssertThrows([calculator computePriceGivenIngredents:([NSArray arrayWithObjects:@"Feta", @"Cheese", nil])],
                    @"Cheese is not ingredient, should have thrown an exception");
    
}


@end
