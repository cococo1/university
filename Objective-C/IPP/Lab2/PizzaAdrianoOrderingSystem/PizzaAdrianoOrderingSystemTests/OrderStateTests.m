//
//  OrderStateTests.m
//  PizzaAdrianoOrderingSystem
//
//  Created by Maxim Chetrusca on 2/1/14.
//  Copyright (c) 2014 Maxim Chetrusca. All rights reserved.
//

#import <XCTest/XCTest.h>
#import "OrderState.h"

@interface OrderStateTests : XCTestCase

@end

@implementation OrderStateTests

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
    XCTAssertNotNil([[OrderState alloc]initWithStateId:BeforeOrderStateId tabLabel:@"some"], @"nil after init");
    XCTAssertNoThrow([[OrderState alloc]initWithStateId:BeforeOrderStateId tabLabel:@"some"], @"exception thrown");
    XCTAssertThrows([[OrderState alloc]init], @"should throw an exception");
    XCTAssertThrows([[OrderState alloc]initWithTabLabel:@"asda"], @"should throw an exception");
    
    OrderState* state = [[OrderState alloc]initWithStateId:FinalizeOrderStateId tabLabel:@"tab"];
    XCTAssertEqual(state.stateId, FinalizeOrderStateId, @"state ids not equal");
    XCTAssertEqualObjects(state.tabLabel, @"tab", @"strings not equal");
    XCTAssertFalse(state.isCompleted, @"should not be completed");
    XCTAssertFalse(state.isDisplayed, @"should not be displayed");
    
    XCTAssertThrows([[OrderState alloc]initWithStateId:BeforeOrderStateId-1 tabLabel:@"asda"], @"asda");
    XCTAssertThrows([[OrderState alloc]initWithStateId:FinalizeOrderStateId+1 tabLabel:@"asda"], @"asda");

}

-(void)testCompletion
{
    OrderState* state = [[OrderState alloc]initWithStateId:FinalizeOrderStateId tabLabel:@"tab"];
    state.displayed = YES;
    XCTAssertTrue(state.isCompleted, @"should be completed");
}
//- (void)testExample
//{
//    XCTFail(@"No implementation for \"%s\"", __PRETTY_FUNCTION__);
//}

@end
