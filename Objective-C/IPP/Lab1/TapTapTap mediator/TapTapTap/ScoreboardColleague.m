//
//  ScoreboardColleague.m
//  TapTapTap
//
//  Created by Maxim Chetrusca on 11/25/13.
//  Copyright (c) 2013 Maxim Chetrusca. All rights reserved.
//

#import "ScoreboardColleague.h"

@interface ScoreboardColleague()

@end

@implementation ScoreboardColleague

-(id) initWithMediator:(id<MediatorProtocol>)mediator
{
    self = [super initWithMediator:mediator];
    if (self)
    {
        _score1 = 0;
        _score2 = 0;
    }
    return self;
}

-(void) receiveMessage:(NSString*) message
{
    if ([message isEqualToString:@"increase score1"])
    {
        self.score1++;
        
    }
    else if ([message isEqualToString:@"increase score2"])
    {
        self.score2++;
    }
}


@end
