//
//  MediatorProtocol.h
//  TapTapTap
//
//  Created by Maxim Chetrusca on 11/25/13.
//  Copyright (c) 2013 Maxim Chetrusca. All rights reserved.
//

#import <Foundation/Foundation.h>

@class AbstractColleague;

@protocol MediatorProtocol <NSObject>

-(void) sendMessage:(NSString*) message
        toColleague:(AbstractColleague*)colleague;

-(void) receiveMessage:(NSString*) message
         fromColleague:(AbstractColleague*)colleague;

//-(void) addColleague:(AbstractColleague*) colleague;

@end
