//
//  SubjectProtocol.h
//  TapTapTap
//
//  Created by Maxim Chetrusca on 1/30/14.
//  Copyright (c) 2014 Maxim Chetrusca. All rights reserved.
//

#import <Foundation/Foundation.h>

@protocol SubjectProtocol <NSObject>

-(BOOL)isTimeForPlayerWithId:(int) pid;
-(void)enablePlayer:(NSString*) name;
-(void)disablePlayer:(NSString*) name;

-(void) updateTable;
@property (nonatomic) int currentPlayerID;


@end
