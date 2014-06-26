//
//  Scoreboard.m
//  TapTapTap
//
//  Created by Maxim Chetrusca on 1/30/14.
//  Copyright (c) 2014 Maxim Chetrusca. All rights reserved.
//

#import "Scoreboard.h"
#import "defines.h"

@interface Scoreboard()

@property (nonatomic, strong) NSMutableDictionary* playerIDsAndScores;
@property (nonatomic, strong) NSMutableDictionary* playerIDsAndNames;

@end

@implementation Scoreboard

@synthesize subject = _subject;

-(id) init
{
    self = [super init];
    if (self)
    {
        _playerIDsAndScores = [[NSMutableDictionary alloc] init];
        _playerIDsAndNames = [[NSMutableDictionary alloc] init];

    }
    return self;
}

-(void) eventHappened:(NSString*)event
{
    long score = [self.playerIDsAndScores[@(self.subject.currentPlayerID)] integerValue] + 1;
    self.playerIDsAndScores[@(self.subject.currentPlayerID)] = [NSNumber numberWithInt:score];
    [self.subject updateTable];
}


-(NSDictionary*) getPlayersAndScores
{
    return [NSDictionary dictionaryWithObjects:[self.playerIDsAndScores allValues]
                                       forKeys:[self.playerIDsAndNames allValues]];
}

-(void) addPlayerWithId:(int) pid
                   name:(NSString*)name
{
    self.playerIDsAndNames[@(pid)] = name;
    self.playerIDsAndScores[@(pid)] = [NSNumber numberWithInt:0];
}

@end
