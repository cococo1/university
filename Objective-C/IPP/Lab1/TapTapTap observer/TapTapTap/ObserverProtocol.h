//
//  ObserverProtocol.h
//  TapTapTap
//
//  Created by Maxim Chetrusca on 1/30/14.
//  Copyright (c) 2014 Maxim Chetrusca. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "SubjectProtocol.h"



@protocol ObserverProtocol <NSObject>

-(void) eventHappened:(NSString*)event;
@property (nonatomic, weak) id<SubjectProtocol> subject;

@end
