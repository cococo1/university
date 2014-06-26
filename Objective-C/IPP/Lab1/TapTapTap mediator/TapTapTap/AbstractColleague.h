//
//  AbstractColleague.h
//  TapTapTap
//
//  Created by Maxim Chetrusca on 11/25/13.
//  Copyright (c) 2013 Maxim Chetrusca. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "MediatorProtocol.h"


//Abstract class. Subclass it and define the receiveMessage: method.

@interface AbstractColleague : NSObject



-(id) initWithMediator:(id<MediatorProtocol>)mediator;

-(void) receiveMessage:(NSString*) message;
-(void) sendMessage:(NSString*) message;

@end
