//
//  Mediator.h
//  TapTapTap
//
//  Created by Maxim Chetrusca on 11/25/13.
//  Copyright (c) 2013 Maxim Chetrusca. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "MediatorProtocol.h"

#define PLAYER_1_KEYSTROKE '1'
#define PLAYER_2_KEYSTROKE '0'
#define PLAYER_INTERVAL 30.0


//In my case, Mediator isn't really responsable for keystrokes and stuff... That would mean one class - two responsabilities..
//So, when it finds out that a player starts playing, and he needs to enable a keystroke,
//HE DELEGATES THIS RESPONSABILITY to someone else, which imlements this protocol:
@protocol MediatorDelegate <NSObject>

-(void) enableKeystroke:(unichar)keystroke;
-(void) updateDisplay; //score changed, update it.

//Some MessageBoxes for UI:
-(void) player1StoppedPlaying;
-(void) player2StoppedPlaying;

@end

@interface Mediator : NSObject <MediatorProtocol>

@property (nonatomic, strong) AbstractColleague* player1;
@property (nonatomic, strong) AbstractColleague* player2;
@property (nonatomic, strong) AbstractColleague* scoreboard;
@property (nonatomic, weak) id <MediatorDelegate> delegate;

-(void) sendMessage:(NSString*) message
        toColleague:(AbstractColleague*)colleague;

-(void) receiveMessage:(NSString*) message
         fromColleague:(AbstractColleague*)colleague;

-(void) startGame;
-(void) oneTapped;
-(void) zeroTapped;

//-(void) addColleague:(AbstractColleague*) colleague;



@end
