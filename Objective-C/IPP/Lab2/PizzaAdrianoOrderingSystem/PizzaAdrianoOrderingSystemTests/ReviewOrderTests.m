//
//  ReviewOrderTests.m
//  PizzaAdrianoOrderingSystem
//
//  Created by Maxim Chetrusca on 2/3/14.
//  Copyright (c) 2014 Maxim Chetrusca. All rights reserved.
//

#import <XCTest/XCTest.h>
#import "ReviewOrderState.h"
#import "PriceCalculator.h"

@interface ReviewOrderTests : XCTestCase

@end

@implementation ReviewOrderTests

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
    XCTAssertNoThrow([[ReviewOrderState alloc]initWithTabLabel:@"ahoj"], @"should not throw");
    XCTAssertNotNil([[ReviewOrderState alloc]initWithTabLabel:@"ahoj"], @"should not be nil");
}

-(void)testOrderInfo
{
    ReviewOrderState* state = [[ReviewOrderState alloc]initWithTabLabel:@"state"];
    NSString* name = @"Alex";
    NSMutableArray* meat = [[NSMutableArray alloc] init];
    NSMutableArray* cheese = [[NSMutableArray alloc]init];
    NSMutableArray* vegetables = [[NSMutableArray alloc] init];
    PriceCalculator* calc = [[PriceCalculator alloc]init];
    
    XCTAssertThrows([state giveOrderInfoForName:nil
                                    extraCheese:cheese
                                      extraMeat:meat
                                extraVegetables:vegetables
                                priceCalculator:calc], @"should throw");
    XCTAssertThrows([state giveOrderInfoForName:name
                                    extraCheese:cheese
                                      extraMeat:meat
                                extraVegetables:vegetables
                                priceCalculator:nil], @"should throw");
    XCTAssertNoThrow([state giveOrderInfoForName:name
                                    extraCheese:nil
                                      extraMeat:meat
                                extraVegetables:vegetables
                                priceCalculator:calc], @"should not throw");
    XCTAssertNoThrow([state giveOrderInfoForName:name
                                     extraCheese:cheese
                                       extraMeat:meat
                                 extraVegetables:nil
                                 priceCalculator:calc], @"should not throw");
    XCTAssertNoThrow([state giveOrderInfoForName:name
                                     extraCheese:cheese
                                       extraMeat:nil
                                 extraVegetables:vegetables
                                 priceCalculator:calc], @"should not throw");
    
    
    
    
    NSDictionary* order = [state giveOrderInfoForName:name
                                          extraCheese:cheese
                                            extraMeat:meat
                                      extraVegetables:vegetables
                                      priceCalculator:calc];
    XCTAssert([order[ORDER_NAME] isEqualToString:name], @"should be equal");
    Pricelist* p = [[Pricelist alloc] init];
    XCTAssert([order[ORDER_PRICE] isEqualToNumber:p.pricelist[@"Pizza"]], @"should be equal");
    
    [cheese addObject:@"Feta"];
    [meat addObject:@"Bacon"];
    [vegetables addObject:@"Corn"];
    order = [state giveOrderInfoForName:name
                            extraCheese:cheese
                              extraMeat:meat
                        extraVegetables:vegetables
                        priceCalculator:calc];
    float result = [(NSNumber*)p.pricelist[@"Pizza"] floatValue] + [(NSNumber*)p.pricelist[@"Feta"] floatValue] + [(NSNumber*)p.pricelist[@"Bacon"] floatValue] + [(NSNumber*)p.pricelist[@"Corn"] floatValue];
    
                                                
    XCTAssert([order[ORDER_PRICE] isEqualToNumber:[NSNumber numberWithFloat:result]], @"should be equal");
    
}









@end
