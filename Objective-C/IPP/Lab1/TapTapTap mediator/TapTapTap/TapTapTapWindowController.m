//
//  TapTapTapWindowController.m
//  TapTapTap
//
//  Created by Maxim Chetrusca on 11/25/13.
//  Copyright (c) 2013 Maxim Chetrusca. All rights reserved.
//

#import "TapTapTapWindowController.h"
#import "ScoreboardColleague.h"

#define SOME_DIFFERENT_KEY 'z'

@interface TapTapTapWindowController()
@property (weak) IBOutlet NSTextField *score1Label;
@property (weak) IBOutlet NSTextField *score2Label;

@property (nonatomic) int currentEnabledKey;

@property (nonatomic, strong) Mediator* mediator;

@end

@implementation TapTapTapWindowController

- (IBAction)startGamePressed:(NSButton *)sender
{
    [self.mediator startGame];
}

-(id)init
{
    self = [super initWithWindowNibName:@"MainMenu"];
    if (self)
    {
        _mediator = [[Mediator alloc] init];
        _mediator.delegate = self;
        _currentEnabledKey = SOME_DIFFERENT_KEY;
    }
    return self;
}

- (void)windowDidLoad
{
    [super windowDidLoad];
    
    //Your code here...
}

-(void) keyDown:(NSEvent *)theEvent
{
    NSString *string = [theEvent characters];
    unichar c = [string characterAtIndex:0];
    if ((c == PLAYER_1_KEYSTROKE) && (self.currentEnabledKey == PLAYER_1_KEYSTROKE)) [self.mediator oneTapped];
    else if (( c == PLAYER_2_KEYSTROKE) && (self.currentEnabledKey == PLAYER_2_KEYSTROKE)) [self.mediator zeroTapped];
//    NSLog(@"%@",string);
}


#pragma mark Mediator Delegate:

-(void) enableKeystroke:(unichar)keystroke
{
    //Enable keystroke... & present a message box:
    self.currentEnabledKey = keystroke;
    NSAlert *alert = [[NSAlert alloc] init];
    if (self.currentEnabledKey == PLAYER_1_KEYSTROKE) alert.messageText = @"Player 1: Go! (Tap 1)";
    else if (self.currentEnabledKey == PLAYER_2_KEYSTROKE) alert.messageText = @"Player 2: Go! (Tap 0)";
    [alert runModal];
}

-(void) updateDisplay
{
    self.score1Label.stringValue = [NSString stringWithFormat:@"%i",((ScoreboardColleague*)self.mediator.scoreboard).score1];
    self.score2Label.stringValue = [NSString stringWithFormat:@"%i",((ScoreboardColleague*)self.mediator.scoreboard).score2];

    //Update...
}

-(void) player1StoppedPlaying
{
    NSLog(@"player 1 is done."); //message box
}

-(void) player2StoppedPlaying
{
    NSLog(@"player 2 is done."); //message box
    self.currentEnabledKey = SOME_DIFFERENT_KEY;
    NSAlert *alert = [[NSAlert alloc] init];
    alert.messageText = @"Time's up. This is the end";
    [alert runModal];

    
}

@end
