//
//  Game.m
//  TapTapTap
//
//  Created by Maxim Chetrusca on 1/30/14.
//  Copyright (c) 2014 Maxim Chetrusca. All rights reserved.
//

#import "Game.h"


@interface Game()

@property (nonatomic, strong) NSMutableDictionary* observersForEvents;
@property (nonatomic, strong) NSTimer* timer;


@end

@implementation Game

-(id) init
{
    self = [super init];
    if (self)
    {
        _observersForEvents = [[NSMutableDictionary alloc] init];
        _timer = nil;

    }
    return self;
}

-(void) addAnObserver:(id<ObserverProtocol>)observer
           forEvent:(NSString *)event
{
    if (! [self.observersForEvents objectForKey:event])
    {
        NSMutableArray* observers = [[NSMutableArray alloc]init];
        self.observersForEvents[event] = observers;
    }
    [self.observersForEvents[event] addObject:observer];
}

-(void) removeAnObserver:(id<ObserverProtocol>)observer
             fromEvent:(NSString *)event
{
    [self.observersForEvents[event] removeObject:observer];
}

-(void) notifyObserversAboutEvent:(NSString*) event
{
    if ([self.observersForEvents objectForKey:event])
        for (id<ObserverProtocol> observer in self.observersForEvents[event])
        {
            [observer eventHappened:event];
        }
}

-(void) start
{
    self.timer = [NSTimer scheduledTimerWithTimeInterval:PLAYER_INTERVAL
                                                  target:self
                                                selector:@selector(timesUp)
                                                userInfo:nil
                                                 repeats:YES];
    [self performSelector:@selector(notifyObserversAboutEvent:) withObject:TIME_STARTS_EVENT afterDelay:0.5];
    
}

-(void) timesUp
{
    [self notifyObserversAboutEvent:TIME_ENDS_EVENT];
    [self performSelector:@selector(notifyObserversAboutEvent:) withObject:TIME_STARTS_EVENT afterDelay:0.5];
}

-(void) currentPlayerScores
{
    [self notifyObserversAboutEvent:SCORE_CHANGE_EVENT]; //at the moment we will consider that score changes only when the current player taps the key
}

-(void) stop
{
    [self.timer invalidate];
}



@end
