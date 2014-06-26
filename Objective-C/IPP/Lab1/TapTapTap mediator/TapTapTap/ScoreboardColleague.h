//
//  ScoreboardColleague.h
//  TapTapTap
//
//  Created by Maxim Chetrusca on 11/25/13.
//  Copyright (c) 2013 Maxim Chetrusca. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "AbstractColleague.h"

@interface ScoreboardColleague : AbstractColleague

-(id) initWithMediator:(id<MediatorProtocol>)mediator;

@property (nonatomic) int score1;
@property (nonatomic) int score2;


@end
