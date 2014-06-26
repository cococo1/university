//
//  PlayerColleague.m
//  TapTapTap
//
//  Created by Maxim Chetrusca on 11/25/13.
//  Copyright (c) 2013 Maxim Chetrusca. All rights reserved.
//

#import "PlayerColleague.h"


@interface PlayerColleague()

@end

@implementation PlayerColleague

-(id) initWithMediator:(id<MediatorProtocol>)mediator
{
    self = [super initWithMediator:mediator];
    if (self)
    {
        //
    }
    return self;
}

-(void) receiveMessage:(NSString*) message
{
    NSLog(@"Player received a message: %@", message);
    
    if ([message isEqualToString:@"your turn"])
    {
        //Player x, start tapping, it's your turn...
        [self sendMessage:@"I am playing!"];
    }
    else if ([message isEqualToString:@"time's up"])
    {
        //Player x, stop tapping, time is over...
        [self sendMessage:@"I am done."];
    }
    else if ([message isEqualToString:@"you tapped"])
    {
        //Oh, so if you tapped, I guess that means you scored one point. Notify mediator that YOU SCORED ONE POINT, HE DOESN'T KNOW ABOUT THAT (he only knows that you tapped...)
        [self sendMessage:@"I scored!"];
    }
}




@end
