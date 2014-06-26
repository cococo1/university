//
//  PricelistTests.m
//  PizzaAdrianoOrderingSystem
//
//  Created by Maxim Chetrusca on 2/2/14.
//  Copyright (c) 2014 Maxim Chetrusca. All rights reserved.
//

#import <XCTest/XCTest.h>
#import "Pricelist.h"

@interface PricelistTests : XCTestCase

@end

@implementation PricelistTests

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
    XCTAssertNoThrow([[Pricelist alloc]init],@"exc thrown");
    XCTAssertNotNil([[Pricelist alloc]init], @"nil");
    Pricelist *pl = [[Pricelist alloc]init];
    NSDictionary *d = [[NSDictionary alloc] initWithObjectsAndKeys:
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
    NSArray *cheese = [[NSArray alloc] initWithObjects:
               @"Feta",
               @"Parmesan",
               @"Mozarella",
               @"Dor Blue",
               @"Edam",
               @"Brânză",
               nil];
    NSArray *meat = [[NSArray alloc]initWithObjects:
             @"Bacon",
             @"Prosciutto",
             @"Salami",
             @"Chicken Breast",
             @"Ham",
             nil];
    NSArray *vegetables = [[NSArray alloc] initWithObjects:
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
    XCTAssertEqualObjects(pl.pricelist, d, @"pls difer");
    XCTAssertEqualObjects(pl.cheese, cheese, @"pls difer");
    XCTAssertEqualObjects(pl.meat, meat, @"pls difer");
    XCTAssertEqualObjects(pl.vegetables, vegetables, @"pls difer");

}

@end
