//
//  Player.h
//  TapTapTap
//
//  Created by Maxim Chetrusca on 1/30/14.
//  Copyright (c) 2014 Maxim Chetrusca. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "ObserverProtocol.h"

@interface Player : NSObject <ObserverProtocol>

-(id) initWithName:(NSString*)name;
@property (nonatomic, readonly) int pid;
@property (nonatomic, readonly, strong) NSString* name;


@end
