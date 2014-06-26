//
//  OrderSystemTests.m
//  PizzaAdrianoOrderingSystem
//
//  Created by Maxim Chetrusca on 1/31/14.
//  Copyright (c) 2014 Maxim Chetrusca. All rights reserved.
//

#import <XCTest/XCTest.h>
//#import "OrderFlow.h"
#import "OrderSystem.h"
#import "OrderSystemWindowController.h"

@interface OrderSystemTests : XCTestCase

@end

@implementation OrderSystemTests

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
//    OrderFlow *flow = [[OrderFlow alloc] init];
    id<OrderSystemDisplayDelegate> delegate = [[OrderSystemWindowController alloc]init];//[[NSObject alloc]init];
    
    XCTAssertNotNil([[OrderSystem alloc]initWithDisplay:delegate], @"nil after init");
    XCTAssertNoThrow([[OrderSystem alloc]initWithDisplay:delegate], @"exception thrown");
//    XCTAssertThrows([[OrderSystem alloc]initWithDisplay:delegate], @"no exception thrown" );
//    XCTAssertThrows([[OrderSystem alloc]initWithDisplay:delegate], @"no exception thrown" );
    
    XCTAssertThrows([[OrderSystem alloc]initWithDisplay:nil], @"no exception thrown" );
    XCTAssertThrows([[OrderSystem alloc]initWithDisplay:(id)@"hello"], @"no exception thrown" );
    
//    OrderSystem* system = [[OrderSystem alloc]initWithDisplay:delegate];
//    XCTAssertEqualObjects(delegate, system.display, @"These two are not equal");
}

-(void)testStart
{
    id<OrderSystemDisplayDelegate> delegate = [[OrderSystemWindowController alloc]init];
    OrderSystem* system = [[OrderSystem alloc]initWithDisplay:delegate];
    XCTAssertNoThrow([system start], @"exception thrown");
}

-(void)testGoOnWithOrder
{
    id<OrderSystemDisplayDelegate> delegate = [[OrderSystemWindowController alloc]init];
    OrderSystem* system = [[OrderSystem alloc]initWithDisplay:delegate];
    XCTAssertNoThrow([system goOnWithOrder], @"exception thrown");
    system = [[OrderSystem alloc]initWithDisplay:delegate];
    XCTAssertFalse([system goOnWithOrder], @"should be false");
    [system start];
    XCTAssertTrue([system goOnWithOrder], @"should be true");
}

-(void)testAddVegetable
{
    id<OrderSystemDisplayDelegate> delegate = [[OrderSystemWindowController alloc]init];
    OrderSystem* system = [[OrderSystem alloc]initWithDisplay:delegate];
    XCTAssertNoThrow([system addVegetable:@"Corn"], @"exc thrown");
    XCTAssert([system addVegetable:@"Corn"], @"should return true");
    
    system = [[OrderSystem alloc]initWithDisplay:delegate];
    for (int i = 0; i<MAX_VEGETABLE_INGREDIENTS_ALLOWED; i++)
    {
        XCTAssert([system addVegetable:@"Corn"], @"should return true");
    }
    XCTAssertFalse([system addVegetable:@"Corn"], @"should return false");
    
    system = [[OrderSystem alloc]initWithDisplay:delegate];
    XCTAssertThrows([system addVegetable:@"cwe4"], @"should throw an ex. if no such vegetable");

    
}

-(void)testAddCheese
{
    id<OrderSystemDisplayDelegate> delegate = [[OrderSystemWindowController alloc]init];
    OrderSystem* system = [[OrderSystem alloc]initWithDisplay:delegate];
    XCTAssertNoThrow([system addCheese:@"Feta"], @"exc thrown");
    XCTAssert([system  addCheese:@"Feta"], @"should return true");
    
    system = [[OrderSystem alloc]initWithDisplay:delegate];
    for (int i = 0; i<MAX_CHEESE_INGREDIENTS_ALLOWED; i++)
    {
        XCTAssert([system  addCheese:@"Feta"], @"should return true");
    }
    XCTAssertFalse([system  addCheese:@"Feta"], @"should return false");
    
    system = [[OrderSystem alloc]initWithDisplay:delegate];
    XCTAssertThrows([system  addCheese:@"d34"], @"should throw an ex. if no such cheese");
    
    
}


-(void)testAddMeat
{
    id<OrderSystemDisplayDelegate> delegate = [[OrderSystemWindowController alloc]init];
    OrderSystem* system = [[OrderSystem alloc]initWithDisplay:delegate];
    XCTAssertNoThrow([system addMeat:@"Bacon"], @"exc thrown");
    XCTAssert([system  addMeat:@"Bacon"], @"should return true");
    
    system = [[OrderSystem alloc]initWithDisplay:delegate];
    for (int i = 0; i<MAX_MEAT_INGREDIENTS_ALLOWED; i++)
    {
        XCTAssert([system  addMeat:@"Bacon"], @"should return true");
    }
    XCTAssertFalse([system  addMeat:@"Bacon"], @"should return false");
    
    system = [[OrderSystem alloc]initWithDisplay:delegate];
    XCTAssertThrows([system  addMeat:@"3f5"], @"should throw an ex. if no such cheese");
    
    
}

-(void)testRemove
{
    id<OrderSystemDisplayDelegate> delegate = [[OrderSystemWindowController alloc]init];
    OrderSystem* system = [[OrderSystem alloc]initWithDisplay:delegate];
    XCTAssertNoThrow([system removeIngredient:@"asda"], @"should not throw ");
    XCTAssertFalse([system removeIngredient:@"asd"], @"should be false");
    [system addCheese:@"Feta"];
    [system removeIngredient:@"Feta"];
}

-(void)testGiveOrder
{
    id<OrderSystemDisplayDelegate> delegate = [[OrderSystemWindowController alloc]init];
    OrderSystem* system = [[OrderSystem alloc]initWithDisplay:delegate];
    XCTAssertThrows([system giveOrderInformation], @"order should have a name");
    
    
    
}









@end
