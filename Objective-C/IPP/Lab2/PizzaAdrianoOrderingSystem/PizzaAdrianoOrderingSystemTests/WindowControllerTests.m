//
//  WindowControllerTests.m
//  PizzaAdrianoOrderingSystem
//
//  Created by Maxim Chetrusca on 1/31/14.
//  Copyright (c) 2014 Maxim Chetrusca. All rights reserved.
//

#import <XCTest/XCTest.h>
#import "OrderSystemWindowController.h"
#import "OrderState.h"

@interface WindowControllerTests : XCTestCase

@end

@implementation WindowControllerTests

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
    NSWindow* window = [[NSWindow alloc]init];
    XCTAssertNotNil([[OrderSystemWindowController alloc]initWithWindow:window], @"nil after init");
    XCTAssertNoThrow([[OrderSystemWindowController alloc]initWithWindow:window], @"exception thrown");
    
}

-(void)testAwakeFromNib
{
    OrderSystemWindowController *vc = [[OrderSystemWindowController alloc]initWithWindow:[[NSWindow alloc]init]];
    XCTAssertNoThrow([vc awakeFromNib], @"exception thrown");

}

-(void)testNextPressed
{
    OrderSystemWindowController *vc = [[OrderSystemWindowController alloc]initWithWindow:[[NSWindow alloc]init]];
    XCTAssertNoThrow([vc next1Pressed:nil], @"exception thrown");
}

-(void)testDisplayState
{
    OrderSystemWindowController *vc = [[OrderSystemWindowController alloc]initWithWindow:[[NSWindow alloc]init]];
    OrderState *state = [[OrderState alloc]initWithStateId:BeforeOrderStateId
                                                  tabLabel:@"label"];
    XCTAssertNoThrow([vc displayState:state], @"should not throw");
}

-(void)testGiveName
{
    OrderSystemWindowController *vc = [[OrderSystemWindowController alloc]initWithWindow:[[NSWindow alloc]init]];
    XCTAssertNoThrow([vc giveName], @"exception thrown");
    XCTAssertNil([vc giveName], @"should return nil");
//    XCTAssertThrows([vc displayState:-1], @"exception not thrown");
//    XCTAssertThrows([vc displayState:100], @"exception not thrown");
}

-(void)testAlert
{
    OrderSystemWindowController *vc = [[OrderSystemWindowController alloc]initWithWindow:[[NSWindow alloc]init]];
    XCTAssertThrows([vc displayAlertWithText:@""], @"exception thrown");
    XCTAssertThrows([vc displayAlertWithText:nil], @"exception thrown");
    XCTAssertNoThrow([vc displayAlertWithText:@"asda"], @"exception thrown");
}

-(void)testDisable
{
    OrderSystemWindowController *vc = [[OrderSystemWindowController alloc]initWithWindow:[[NSWindow alloc]init]];
    XCTAssertNoThrow([vc disable:Cheese], @"should not throw");
    XCTAssertNoThrow([vc disable:Meat], @"should not throw");
    XCTAssertNoThrow([vc disable:Vegetables], @"should not throw");
    XCTAssertThrows([vc disable:Cheese-1], @"should throw");
    XCTAssertThrows([vc disable:Vegetables+1], @"should throw");
}

-(void)testEnable
{
    OrderSystemWindowController *vc = [[OrderSystemWindowController alloc]initWithWindow:[[NSWindow alloc]init]];
    XCTAssertNoThrow([vc enable:Cheese], @"should not throw");
    XCTAssertNoThrow([vc enable:Meat], @"should not throw");
    XCTAssertNoThrow([vc enable:Vegetables], @"should not throw");
    XCTAssertThrows([vc enable:Cheese-1], @"should throw");
    XCTAssertThrows([vc enable:Vegetables+1], @"should throw");
}

@end
