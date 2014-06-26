//
//  Mediator.m
//  TapTapTap
//
//  Created by Maxim Chetrusca on 11/25/13.
//  Copyright (c) 2013 Maxim Chetrusca. All rights reserved.
//

#import "Mediator.h"
#import "PlayerColleague.h"
#import "ScoreboardColleague.h"

@interface Mediator()


@property (nonatomic, strong) NSTimer* timer;
@property (nonatomic, getter = isPlayer1Turn) BOOL player1Turn;
//@property (nonatomic, strong) NSMutableArray* colleagues;



@end

@implementation Mediator

-(id) init
{
    self = [super init];
    if (self)
    {
        _player1 = [[PlayerColleague alloc] initWithMediator:self];
        _player2 = [[PlayerColleague alloc] initWithMediator:self];
        _scoreboard = [[ScoreboardColleague alloc] initWithMediator:self];
        _timer = nil;
        _player1Turn = NO;
//        _colleagues = [[NSMutableArray alloc]init];
    }
    return self;
}

-(void) startGame
{
    self.timer = [NSTimer scheduledTimerWithTimeInterval:PLAYER_INTERVAL
                                                  target:self
                                                selector:@selector(timesUp)
                                                userInfo:nil
                                                 repeats:YES];
    [self sendMessage:@"your turn" toColleague:self.player1];
    self.player1Turn = YES;
    
}

-(void) timesUp
{
    static BOOL changed = NO;
    if (!changed)    //change the turn:
    {
        changed = YES;
        [self sendMessage:@"time's up" toColleague:self.player1];
        [self sendMessage:@"your turn" toColleague:self.player2];
        self.player1Turn = NO;
    }
    else
    {
        [self sendMessage:@"time's up" toColleague:self.player2];
        [self.timer invalidate];
    }
    
}

-(void) oneTapped
{
    if (self.isPlayer1Turn)
    {
        [self sendMessage:@"you tapped" toColleague:self.player1];
    }
}
-(void) zeroTapped
{
    if (! self.isPlayer1Turn)
    {
        [self sendMessage:@"you tapped" toColleague:self.player2];
    }
}

-(void) sendMessage:(NSString*) message
        toColleague:(AbstractColleague*)colleague
{
    [colleague receiveMessage:message];
}

-(void) receiveMessage:(NSString*) message
         fromColleague:(AbstractColleague*)colleague
{
    if ([message isEqualToString:@"I am playing!"])
    {
        if ([colleague isEqual:self.player1])
        {
            NSLog(@"enable keystroke 1");
            //Enable keystroke 1...
            [self.delegate enableKeystroke:PLAYER_1_KEYSTROKE];
        }
        else if ([colleague isEqual:self.player2])
        {
            //Enable keystroke 2...
            [self.delegate enableKeystroke:PLAYER_2_KEYSTROKE];
        }
    }
    
    if ([message isEqualToString:@"I scored!"])
    {
        if ([colleague isEqual:self.player1])
        {
            [self sendMessage:@"increase score1" toColleague:self.scoreboard];
        }
        else if ([colleague isEqual:self.player2])
        {
            [self sendMessage:@"increase score2" toColleague:self.scoreboard];
        }
        [self.delegate updateDisplay];
    }
    
    if ([message isEqualToString:@"I am done."])
    {
        if ([colleague isEqual:self.player1])
        {
            [self.delegate player1StoppedPlaying];
        }
        else if ([colleague isEqual:self.player2])
        {
            [self.delegate player2StoppedPlaying];
        }
    }
    
}

//-(void) addColleague:(AbstractColleague*) colleague
//{
////    [self.colleagues addObject:colleague];
//}

@end
