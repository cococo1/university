//
//  PlayerColleague.h
//  TapTapTap
//
//  Created by Maxim Chetrusca on 11/25/13.
//  Copyright (c) 2013 Maxim Chetrusca. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "AbstractColleague.h"


@interface PlayerColleague : AbstractColleague

-(id) initWithMediator:(id<MediatorProtocol>)mediator;

@end
