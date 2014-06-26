//
//  OrderingSystemWindowController.h
//  PizzaAdrianoOrderingSystem
//
//  Created by Maxim Chetrusca on 1/31/14.
//  Copyright (c) 2014 Maxim Chetrusca. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import "OrderSystem.h"

@interface OrderSystemWindowController : NSWindowController <OrderSystemDisplayDelegate, NSTableViewDataSource>

@property (weak) IBOutlet NSTabView *stagesTabView;

//Tabs:
@property (weak) IBOutlet NSView *beforeOrderView;
@property (weak) IBOutlet NSView *inputNameView;
@property (weak) IBOutlet NSView *selectIngredientsView;
@property (weak) IBOutlet NSView *reviewOrderView;
@property (weak) IBOutlet NSView *finalizeOrderView;

//From name input tab:
@property (weak) IBOutlet NSTextField *nameTextField; //input field

//From review tab:
@property (weak) IBOutlet NSTextField *nameLabel; //from Review page
@property (weak) IBOutlet NSScrollView *ingredientScrollView;
@property (weak) IBOutlet NSTextField *totalPriceTextField;

//From finalize tab:
@property (weak) IBOutlet NSTextField *idTextField;


@property (nonatomic, strong, readonly) OrderSystem* system;



- (IBAction)newOrderPressed:(NSButton *)sender;
- (IBAction)vegetableSelected:(NSButton *)sender;
- (IBAction)next1Pressed:(NSButton *)sender;
- (IBAction)cheeseSelected:(NSButton *)sender;
- (IBAction)meatSelected:(NSButton *)sender;

#pragma mark OrderSystemDisplayDelegate
-(void) displayState:(id<StateProtocol>)state;
-(NSString*) giveName;
-(void) displayAlertWithText:(NSString*)text;
-(void) disable:(IngredientType)type;
-(void) enable:(IngredientType)type;


- (id)initWithWindow:(NSWindow *)window;
-(void) awakeFromNib;

#pragma mark NSTableViewDataSource
- (NSInteger)numberOfRowsInTableView:(NSTableView *)aTableView;
- (id)tableView:(NSTableView *)aTableView
objectValueForTableColumn:(NSTableColumn *)aTableColumn
            row:(NSInteger)rowIndex;












@end
