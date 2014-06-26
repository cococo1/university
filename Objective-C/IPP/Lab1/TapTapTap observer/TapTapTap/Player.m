//
//  Player.m
//  TapTapTap
//
//  Created by Maxim Chetrusca on 1/30/14.
//  Copyright (c) 2014 Maxim Chetrusca. All rights reserved.
//

#import "Player.h"
#import "defines.h"

@interface Player()


@end

@implementation Player 

@synthesize subject = _subject;

-(id) initWithName:(NSString*)name
{
    static int ID = 0;
    self = [super init];
    if (self)
    {
        _name = [NSString stringWithString:name];
        _pid = ID;
        ID++;
    }
    return self;
}

-(void) eventHappened:(NSString*)event
{
    if ([event isEqualToString:TIME_STARTS_EVENT] && [self.subject isTimeForPlayerWithId:self.pid])
    {
        [self.subject enablePlayer:self.name];
    }
    else if ([event isEqualToString:TIME_ENDS_EVENT] && (self.subject.currentPlayerID == self.pid))
    {
        [self.subject disablePlayer:self.name];
    }
}

@end
