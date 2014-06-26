//
//  Game.h
//  TapTapTap
//
//  Created by Maxim Chetrusca on 1/30/14.
//  Copyright (c) 2014 Maxim Chetrusca. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "ObservableProtocol.h"
#import "defines.h"


@interface Game : NSObject <ObservableProtocol>

-(void) start;
-(void) stop;
-(void) currentPlayerScores;

@end
