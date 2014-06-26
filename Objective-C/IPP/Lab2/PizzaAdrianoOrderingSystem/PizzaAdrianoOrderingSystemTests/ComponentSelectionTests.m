//
//  ComponentSelectionTests.m
//  PizzaAdrianoOrderingSystem
//
//  Created by Maxim Chetrusca on 2/1/14.
//  Copyright (c) 2014 Maxim Chetrusca. All rights reserved.
//

#import <XCTest/XCTest.h>
#import "ComponentSelectionState.h"

@interface ComponentSelectionTests : XCTestCase

@end

@implementation ComponentSelectionTests

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
    ComponentSelectionState* state = [[ComponentSelectionState alloc]initWithTabLabel:@"string"];
    XCTAssertEqual(state.stateId, PizzaComponentSelectionStateId, @"different state id");
    XCTAssertFalse(state.extraIngredientsSelected, @"should be NO");
    XCTAssertFalse(state.cheesesSelected, @"should be NO");
    XCTAssertFalse(state.meatSelected, @"should be NO");
    XCTAssertFalse(state.vegetablesSelected, @"should be NO");
    XCTAssertNotNil(state.cheeses, @"nil");
    XCTAssertNotNil(state.meat, @"nil");
    XCTAssertNotNil(state.vegetables, @"nil");
//    XCTAssertNil(state.name, @"name should be nil");
    XCTAssertThrows([[ComponentSelectionState alloc]initWithStateId:BeforeOrderStateId tabLabel:@"string"], @"state");
}

-(void)testChoice
{
    ComponentSelectionState* state = [[ComponentSelectionState alloc]initWithTabLabel:@"string"];
    
    [state addIngredient:@"Feta" ofType:Cheese];
    XCTAssertTrue(state.extraIngredientsSelected, @"it's false");
    XCTAssertTrue(state.cheesesSelected, @"it's false");
    [state addIngredient:@"Feta" ofType:Cheese];
    [state addIngredient:@"Feta" ofType:Cheese];
    [state addIngredient:@"Feta" ofType:Cheese];
    XCTAssert([state.cheeses count] <= MAX_CHEESE_INGREDIENTS_ALLOWED, @"Jesus, that's too much cheese!");
    [state addIngredient:@"Bacon" ofType:Meat];
    XCTAssertTrue(state.meatSelected, @"it's false");
    [state addIngredient:@"Bacon" ofType:Meat];
    [state addIngredient:@"Bacon" ofType:Meat];
    XCTAssert([state.meat count] <= MAX_MEAT_INGREDIENTS_ALLOWED, @"Jesus, that's too much meat!");
    [state addIngredient:@"Corn" ofType:Vegetables];
    XCTAssertTrue(state.vegetablesSelected, @"it's false");
    [state addIngredient:@"Corn" ofType:Vegetables];
    [state addIngredient:@"Corn" ofType:Vegetables];
    [state addIngredient:@"Corn" ofType:Vegetables];
    [state addIngredient:@"Corn" ofType:Vegetables];
    [state addIngredient:@"Corn" ofType:Vegetables];
    XCTAssert([state.vegetables count] <= MAX_VEGETABLE_INGREDIENTS_ALLOWED, @"Jesus, that's too much vegetables!");
}

-(void)testAddition
{
    ComponentSelectionState* state = [[ComponentSelectionState alloc]initWithTabLabel:@"string"];
    XCTAssertThrows([state addIngredient:@"Feta" ofType:Meat], @"Feta is not meat!");
    XCTAssertThrows([state addIngredient:@"Feta" ofType:Vegetables], @"Feta is not vegetable!");
    XCTAssertThrows([state addIngredient:@"Corn" ofType:Cheese], @"Corn is not cheese!");
    XCTAssertThrows([state addIngredient:@"34r" ofType:Meat], @"Feta is not meat!");
    XCTAssertThrows([state addIngredient:@"34f" ofType:Vegetables], @"Feta is not vegetable!");
    XCTAssertThrows([state addIngredient:@"d44" ofType:Cheese], @"Corn is not cheese!");
    
    
}

-(void)testRemove
{
    ComponentSelectionState* state = [[ComponentSelectionState alloc]initWithTabLabel:@"string"];
    
    XCTAssertFalse([state removeIngredient:@"a"], @"should be false");

    
    [state addIngredient:@"Feta" ofType:Cheese];
    [state addIngredient:@"Parmesan" ofType:Cheese];
    [state removeIngredient:@"Feta"];
    XCTAssertTrue([state.cheeses count] == 1, @"wrong number");
    XCTAssertEqualObjects(@"Parmesan", [state.cheeses lastObject], @"wrong ingredient");
    XCTAssertFalse([state removeIngredient:@"x"], @"should be false");

    [state addIngredient:@"Bacon" ofType:Meat];
    [state addIngredient:@"Salami" ofType:Meat];
    [state removeIngredient:@"Bacon"];
    XCTAssertTrue([state.meat count] == 1, @"wrong number");
    XCTAssertEqualObjects(@"Salami", [state.meat lastObject], @"wrong ingredient");
    
    [state addIngredient:@"Corn" ofType:Vegetables];
    [state addIngredient:@"Garlic" ofType:Vegetables];
    [state removeIngredient:@"Corn"];
    XCTAssertTrue([state.vegetables count] == 1, @"wrong number");
    XCTAssertEqualObjects(@"Garlic", [state.vegetables lastObject], @"wrong ingredient");
    

    
}

@end
