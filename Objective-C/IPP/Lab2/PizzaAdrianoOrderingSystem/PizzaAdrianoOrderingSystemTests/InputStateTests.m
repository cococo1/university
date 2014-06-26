//
//  InputStateTests.m
//  PizzaAdrianoOrderingSystem
//
//  Created by Maxim Chetrusca on 2/1/14.
//  Copyright (c) 2014 Maxim Chetrusca. All rights reserved.
//

#import <XCTest/XCTest.h>
#import "InputNameState.h"

@interface InputStateTests : XCTestCase

@end

@implementation InputStateTests

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
    InputNameState* state = [[InputNameState alloc]initWithTabLabel:@"string"];
    XCTAssertNil(state.name, @"name should be nil");
    XCTAssertThrows([[InputNameState alloc]initWithStateId:BeforeOrderStateId tabLabel:@"string"], @"state");
}

-(void)testCompletion
{
   InputNameState* state = [[InputNameState alloc]initWithTabLabel:@"string"];
    state.displayed = YES;
    XCTAssertFalse(state.isCompleted, @"should not be completed");
    state.name = @"";
    XCTAssertFalse(state.isCompleted, @"should not be completed");
    state.name = nil;
    XCTAssertFalse(state.isCompleted, @"should not be completed");
    state.name = @"max";
    XCTAssertTrue(state.isCompleted, @"should be completed");
}

-(void)testName
{
    InputNameState* state = [[InputNameState alloc]initWithTabLabel:@"string"];
    state.name = nil;
    XCTAssertFalse(state.completed, @"should be false");
    state.name = @"";
    XCTAssertFalse(state.completed, @"should be false");
}

@end
