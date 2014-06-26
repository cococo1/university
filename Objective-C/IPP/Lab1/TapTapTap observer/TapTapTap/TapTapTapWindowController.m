//
//  TapTapTapWindowController.m
//  TapTapTap
//
//  Created by Maxim Chetrusca on 11/25/13.
//  Copyright (c) 2013 Maxim Chetrusca. All rights reserved.
//

#import "TapTapTapWindowController.h"
#import "Scoreboard.h"
#import "Game.h"
#import "Player.h"


#define SOME_DIFFERENT_KEY 'z'

@interface TapTapTapWindowController()

@property (weak) IBOutlet NSTableView *playersTableView;
@property (weak) IBOutlet NSTextField *playerNameTextField;

@property (nonatomic) int currentEnabledKey;
@property (nonatomic, strong) Scoreboard* scoreboard;
@property (nonatomic, strong) Game* game;

@property (weak) IBOutlet NSButton *addPlayerButton;

@property (nonatomic) int nextPlayerID;
@property (nonatomic) int lastPlayerID;

@end

@implementation TapTapTapWindowController


@synthesize currentPlayerID = _currentPlayerID;

-(id)init
{
    self = [super initWithWindowNibName:@"MainMenu"];
    if (self)
    {
        _currentEnabledKey = SOME_DIFFERENT_KEY;
        _game = [[Game alloc] init];
        _scoreboard = [[Scoreboard alloc] init];
        _currentPlayerID = -1;
        _nextPlayerID = 0;
        _lastPlayerID = 0;
        
        //!!! this is actually set in XIB !!!
        [_playersTableView setDataSource:self];
    }
    return self;
}

- (IBAction)startGamePressed:(NSButton *)sender
{
    [self.addPlayerButton setEnabled:NO];
    [self.playerNameTextField setEnabled:NO];
    [self.game start];
}

-(void) updateTable
{
    [self.playersTableView reloadData];
}

- (IBAction)addPlayerPressed:(NSButton *)sender
{
    NSString *playerName = [self.playerNameTextField stringValue];
    if ([playerName isEqualToString:@""])
    {
        playerName = @"Player";
    }
    
    [self addNewPlayerWithName:playerName];
}

-(BOOL)isTimeForPlayerWithId:(int) pid
{
    if (self.nextPlayerID == pid)
    {
        self.currentPlayerID = self.nextPlayerID;
        return YES;
    }
    else
    {
        return NO;
    }
}

-(void) addNewPlayerWithName:(NSString*) name
{
    Player *player = [[Player alloc]initWithName:name];
    player.subject = self;
    [self.scoreboard addPlayerWithId:player.pid
                                name:player.name];
    [self.game addAnObserver:player forEvent:TIME_STARTS_EVENT];
    [self.game addAnObserver:player forEvent:TIME_ENDS_EVENT];
    self.lastPlayerID = player.pid;

    [self.playersTableView reloadData];
}

-(void)enablePlayer:(NSString*) name
{
    NSAlert *alert = [[NSAlert alloc] init];
    alert.messageText = [NSString stringWithFormat:@"%@: Go! (Tap 1)",name];
    [alert runModal];
}

-(void)disablePlayer:(NSString*) name
{
    self.nextPlayerID++;
    NSAlert *alert = [[NSAlert alloc] init];
    alert.messageText = [NSString stringWithFormat:@"%@: Stop.",name];
    [alert runModal];
    if (self.currentPlayerID == self.lastPlayerID)
    {
        [self.game stop];
        [self.game removeAnObserver:self.scoreboard fromEvent:SCORE_CHANGE_EVENT];
    }
    
}

-(void) awakeFromNib
{
    [super awakeFromNib];
    self.scoreboard.subject = self;
    [self.game addAnObserver:self.scoreboard
                  forEvent:SCORE_CHANGE_EVENT];
}

- (void)windowDidLoad
{

    //Your code here...
}

-(void) keyDown:(NSEvent *)theEvent
{
        NSString *string = [theEvent characters];
        unichar c = [string characterAtIndex:0];
        if (c == PLAYER_KEYSTROKE) [self.game currentPlayerScores];
}

#pragma mark NSTableView delegate

- (NSInteger)numberOfRowsInTableView:(NSTableView *)aTableView
{
    NSDictionary* playersAndScores = [self.scoreboard getPlayersAndScores];
    return [[playersAndScores allKeys] count];
}

- (id)tableView:(NSTableView *)aTableView
objectValueForTableColumn:(NSTableColumn *)aTableColumn
            row:(NSInteger)rowIndex
{
    
    // The return value is typed as (id) because it will return a string in most cases.
    id returnValue = nil;
    
    // The column identifier string is the easiest way to identify a table column.
    NSString *columnIdentifer = [aTableColumn identifier];
    

    
    NSDictionary* playersAndScores = [self.scoreboard getPlayersAndScores];
    NSArray* players = [playersAndScores allKeys];
    NSArray* scores = [playersAndScores allValues];
    
    if ([columnIdentifer isEqualToString:@"player"])
    {
        returnValue = [players objectAtIndex:rowIndex];
    }
    else if ([columnIdentifer isEqualToString:@"score"])
    {
        returnValue = [scores objectAtIndex:rowIndex];
    }
    
    return returnValue;
}

@end
