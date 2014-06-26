//
//  IntegrationTests.m
//  PizzaAdrianoOrderingSystem
//
//  Created by Maxim Chetrusca on 2/3/14.
//  Copyright (c) 2014 Maxim Chetrusca. All rights reserved.
//

#import <XCTest/XCTest.h>
#import "OrderSystemWindowController.h"

@interface IntegrationTests : XCTestCase

@end

@implementation IntegrationTests

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

-(void)testA
{
    OrderSystemWindowController *vc = [[OrderSystemWindowController alloc]initWithWindow:[[NSWindow alloc]init]];
    [vc awakeFromNib];
    NSTextField* nameTextField = [[NSTextField alloc]init];
    vc.nameTextField = nameTextField;
    [vc next1Pressed:nil];
    nameTextField.stringValue = @"Maxim";
    [vc next1Pressed:nil];
    NSButton* button = [[NSButton alloc]init];
    button.state = NSOnState;
    button.title = @"Feta";
    [vc cheeseSelected:button];
    button.title = @"Bacon";
    [vc meatSelected:button];
    button.title = @"Corn";
    [vc vegetableSelected:button];
    [vc next1Pressed:nil];
    float price = [[vc.system giveOrderInformation][ORDER_PRICE] floatValue];
    XCTAssertEqualWithAccuracy(244, price, 0.1, @"not equal");
    NSString* name = [vc.system giveOrderInformation][ORDER_NAME];
    XCTAssertEqualObjects(name, @"Maxim", @"not equal");
    
    
}

-(void)testB
{
    OrderSystemWindowController *vc = [[OrderSystemWindowController alloc]initWithWindow:[[NSWindow alloc]init]];
    [vc awakeFromNib];
    NSTextField* nameTextField = [[NSTextField alloc]init];
    vc.nameTextField = nameTextField;
    [vc next1Pressed:nil];
    nameTextField.stringValue = @"Maxim";
    [vc next1Pressed:nil];
    NSButton* button = [[NSButton alloc]init];
    button.state = NSOnState;
    button.title = @"Feta";
    [vc cheeseSelected:button];
    button.title = @"Bacon";
    [vc meatSelected:button];
    button.title = @"Corn";
    [vc vegetableSelected:button];
    button.title = @"Feta";
    button.state = NSOffState;
    [vc cheeseSelected:button];
    [vc next1Pressed:nil];
    float price = [[vc.system giveOrderInformation][ORDER_PRICE] floatValue];
    XCTAssertEqualWithAccuracy(224, price, 0.1, @"not equal");
}

-(void)testC
{
    OrderSystemWindowController *vc = [[OrderSystemWindowController alloc]initWithWindow:[[NSWindow alloc]init]];
    [vc awakeFromNib];
    NSTextField* nameTextField = [[NSTextField alloc]init];
    vc.nameTextField = nameTextField;
    [vc next1Pressed:nil];
    nameTextField.stringValue = @"Maxim";
    [vc next1Pressed:nil];
    [vc next1Pressed:nil];
    float price = [[vc.system giveOrderInformation][ORDER_PRICE] floatValue];
    XCTAssertEqualWithAccuracy(100, price, 0.1, @"not equal");
}

-(void)testD
{
    OrderSystemWindowController *vc = [[OrderSystemWindowController alloc]initWithWindow:[[NSWindow alloc]init]];
    [vc awakeFromNib];
    NSTextField* nameTextField = [[NSTextField alloc]init];
    vc.nameTextField = nameTextField;
    [vc next1Pressed:nil];
    nameTextField.stringValue = @"Maxim";
    [vc next1Pressed:nil];
    [vc next1Pressed:nil];
    [vc next1Pressed:nil];
    XCTAssertEqual(101, vc.system.orderId, @"not equal");
    [vc newOrderPressed:nil];
    XCTAssertEqual(102, vc.system.orderId, @"not equal");
}

-(void)testE
{
    OrderSystemWindowController *vc = [[OrderSystemWindowController alloc]initWithWindow:[[NSWindow alloc]init]];
    [vc awakeFromNib];
    NSTextField* nameTextField = [[NSTextField alloc]init];
    vc.nameTextField = nameTextField;
    [vc next1Pressed:nil];
    nameTextField.stringValue = @"Maxim";
    [vc next1Pressed:nil];
    NSButton* button = [[NSButton alloc]init];
    button.state = NSOnState;
    button.title = @"Feta";
    [vc cheeseSelected:button];
    button.title = @"Edam";
    [vc cheeseSelected:button];
    button.title = @"Dor Blue";
    [vc cheeseSelected:button];
    button.title = @"Parmesan";
    [vc cheeseSelected:button];
    button.title = @"Mozarella";
    [vc cheeseSelected:button];
    [vc next1Pressed:nil];
    float price = [[vc.system giveOrderInformation][ORDER_PRICE] floatValue];
    XCTAssertEqualWithAccuracy(220, price, 0.1, @"not equal");
}

@end
