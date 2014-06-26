//
//  OrderingSystemWindowController.m
//  PizzaAdrianoOrderingSystem
//
//  Created by Maxim Chetrusca on 1/31/14.
//  Copyright (c) 2014 Maxim Chetrusca. All rights reserved.
//

#import "OrderSystemWindowController.h"

@interface OrderSystemWindowController ()




@property (nonatomic, strong) OrderSystem* system;


@end

@implementation OrderSystemWindowController

- (id)initWithWindow:(NSWindow *)window
{
    self = [super initWithWindow:window];
    if (self)
    {
        _system = [[OrderSystem alloc]initWithDisplay:self];
    }
    return self;
}


- (IBAction)newOrderPressed:(NSButton *)sender
{
    [self.stagesTabView removeTabViewItem:[self.stagesTabView tabViewItemAtIndex:0]];
    [self.stagesTabView removeTabViewItem:[self.stagesTabView tabViewItemAtIndex:0]];
    [self.system start];
    
}



- (IBAction)vegetableSelected:(NSButton *)sender
{
    if (sender.state == NSOnState)
    {
        [self.system addVegetable:sender.title];
    }
    if (sender.state == NSOffState)
    {
        [self.system removeIngredient:sender.title];
    }
}



- (IBAction)cheeseSelected:(NSButton *)sender
{
    if (sender.state == NSOnState)
    {
        [self.system addCheese:sender.title];
    }
    if (sender.state == NSOffState)
    {
        [self.system removeIngredient:sender.title];
    }
    
    
    
}


- (IBAction)meatSelected:(NSButton *)sender
{
    if (sender.state == NSOnState)
    {
        [self.system addMeat:sender.title];
    }
    if (sender.state == NSOffState)
    {
        [self.system removeIngredient:sender.title];
    }
}


- (IBAction)next1Pressed:(NSButton *)sender
{
    BOOL result = [self.system goOnWithOrder];
    if (result)
    {
        [sender setEnabled:NO];
    }
    
    if ([sender.title isEqualToString:@"Confirm Order"])
    {
        for (NSTabViewItem* item in [self.stagesTabView tabViewItems])
        {
            if ([item.label isEqualToString:@"Name"] || [item.label isEqualToString:@"Ingredients"])
            {
                [self.stagesTabView removeTabViewItem:item];
            }
        }

    }
}

-(NSString*) giveName
{
    return [self.nameTextField stringValue];
}

-(void) displayAlertWithText:(NSString*)text
{
    if (!text || [text isEqualToString:@""])
    {
        [NSException raise:@"text cannot be empty" format:nil];
    }
    NSAlert *alert = [[NSAlert alloc] init];
    alert.messageText = text;
    [alert runModal];
}

// the tight between self.window and the .xib window is done in Interface Builder
-(void) awakeFromNib
{
    [super awakeFromNib];
    [self start];
}

-(void) start
{
    [self.system start];
}

-(void) displayState:(id<StateProtocol>)state
{
    NSTabViewItem* tab = [[NSTabViewItem alloc] init];
    
    
    if (state.stateId < BeforeOrderStateId || state.stateId > FinalizeOrderStateId)
    {
        [NSException raise:@"Unknown state." format:@"%i",state.stateId];
    }
    
    switch (state.stateId)
    {
        case BeforeOrderStateId:
            tab.view = self.beforeOrderView;
            
            break;
        case InputNameStateId:
            tab.view = self.inputNameView;
            [self.stagesTabView removeTabViewItem:[self.stagesTabView tabViewItemAtIndex:0]];
            

            break;
        case PizzaComponentSelectionStateId:
            tab.view = self.selectIngredientsView;

            break;
        case ReviewOrderStateId:
            tab.view = self.reviewOrderView;

            break;
        case FinalizeOrderStateId:
            tab.view = self.finalizeOrderView;
            self.idTextField.stringValue = [NSString stringWithFormat:@"%i", self.system.orderId];

            break;
        default:
            [NSException raise:@"State not implemented yet." format:@"%i",state.stateId];
    }
    for (NSView* aView in [tab.view subviews])
    {
        if ([aView isKindOfClass:[NSButton class]])
        {
            NSButton* button = (NSButton*)aView;
            button.state = NSOffState;
            [button setEnabled:YES];
        }
    }
    tab.label = state.tabLabel;
    
    [self.stagesTabView addTabViewItem:tab];
    [self.stagesTabView selectNextTabViewItem:nil];
//    self.stagesTabView ta
}

-(void) disable:(IngredientType)type
{
    switch (type)
    {
        case Cheese:
            for (id object in [self.selectIngredientsView subviews])
            {
                if ([object isKindOfClass:[NSButton class]])
                {
                    NSButton* button = (NSButton*)object;
                    if ([button.identifier isEqualToString:@"cheese"])
                    {
                        if (button.state == NSOffState)
                        {
                            [button setEnabled:NO];
                        }
                    }
                }
            }
            break;
        case Meat:
            for (id object in [self.selectIngredientsView subviews])
            {
                if ([object isKindOfClass:[NSButton class]])
                {
                    NSButton* button = (NSButton*)object;
                    if ([button.identifier isEqualToString:@"meat"])
                    {
                        if (button.state == NSOffState)
                        {
                            [button setEnabled:NO];
                        }
                    }
                }
            }
            break;
        case Vegetables:
            for (id object in [self.selectIngredientsView subviews])
            {
                if ([object isKindOfClass:[NSButton class]])
                {
                    NSButton* button = (NSButton*)object;
                    if ([button.identifier isEqualToString:@"vegetable"])
                    {
                        if (button.state == NSOffState)
                        {
                            [button setEnabled:NO];
                        }
                    }
                }
            }
            break;
            
        default:
            [NSException raise:@"No such ingredient" format:nil];
            break;
    }
}

-(void) enable:(IngredientType)type
{
    switch (type)
    {
        case Cheese:
            for (id object in [self.selectIngredientsView subviews])
            {
                if ([object isKindOfClass:[NSButton class]])
                {
                    NSButton* button = (NSButton*)object;
                    if ([button.identifier isEqualToString:@"cheese"])
                    {
                        if (button.state == NSOffState)
                        {
                            [button setEnabled:YES];
                        }
                    }
                }
            }
            break;
        case Meat:
            for (id object in [self.selectIngredientsView subviews])
            {
                if ([object isKindOfClass:[NSButton class]])
                {
                    NSButton* button = (NSButton*)object;
                    if ([button.identifier isEqualToString:@"meat"])
                    {
                        if (button.state == NSOffState)
                        {
                            [button setEnabled:YES];
                        }
                    }
                }
            }
            break;
        case Vegetables:
            for (id object in [self.selectIngredientsView subviews])
            {
                if ([object isKindOfClass:[NSButton class]])
                {
                    NSButton* button = (NSButton*)object;
                    if ([button.identifier isEqualToString:@"vegetable"])
                    {
                        if (button.state == NSOffState)
                        {
                            [button setEnabled:YES];
                        }
                    }
                }
            }
            break;
            
        default:
            [NSException raise:@"No such ingredient" format:nil];
            break;
    }
    
}


#pragma TableView data source

- (NSInteger)numberOfRowsInTableView:(NSTableView *)aTableView
{
    NSDictionary* order = [self.system giveOrderInformation];
    self.nameLabel.stringValue = order[ORDER_NAME];
    self.totalPriceTextField.stringValue = order[ORDER_PRICE];
    
    return [order[ORDER_INGREDIENTS] count];
}

- (id)tableView:(NSTableView *)aTableView
objectValueForTableColumn:(NSTableColumn *)aTableColumn
            row:(NSInteger)rowIndex
{
    
    // The return value is typed as (id) because it will return a string in most cases.
    id returnValue = nil;
    
    // The column identifier string is the easiest way to identify a table column.
    NSString *columnIdentifer = [aTableColumn identifier];
    
    NSDictionary* order = [self.system giveOrderInformation];
    NSArray* ingredients = order[ORDER_INGREDIENTS];
    NSArray* prices = order[ORDER_PRICES];
    
    if ([columnIdentifer isEqualToString:@"ingredients"])
    {
        returnValue = [ingredients objectAtIndex:rowIndex];
    }
    else if ([columnIdentifer isEqualToString:@"prices"])
    {
        returnValue = [prices objectAtIndex:rowIndex];
    }
    
    return returnValue;
}




@end
