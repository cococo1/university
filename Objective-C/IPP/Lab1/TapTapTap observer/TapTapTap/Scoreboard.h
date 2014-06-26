//
//  Scoreboard.h
//  TapTapTap
//
//  Created by Maxim Chetrusca on 1/30/14.
//  Copyright (c) 2014 Maxim Chetrusca. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "ObserverProtocol.h"

@interface Scoreboard : NSObject <ObserverProtocol>

-(NSDictionary*) getPlayersAndScores;
-(void) addPlayerWithId:(int) pid
                   name:(NSString*)name;

@end
