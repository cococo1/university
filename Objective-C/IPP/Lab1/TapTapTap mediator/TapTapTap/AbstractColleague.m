//
//  AbstractColleague.m
//  TapTapTap
//
//  Created by Maxim Chetrusca on 11/25/13.
//  Copyright (c) 2013 Maxim Chetrusca. All rights reserved.
//

#import "AbstractColleague.h"

@interface AbstractColleague()

@property (nonatomic, weak) id <MediatorProtocol> mediator;



@end

@implementation AbstractColleague

@synthesize mediator = _mediator;

-(id) initWithMediator:(id<MediatorProtocol>)mediator
{
    self = [super init];
    if (self)
    {
        _mediator = mediator;
    }
    return self;
}



-(void) receiveMessage:(NSString*) message
{
    //Kinda goofy, but Objective-C does not have abstract classes. So, let's raise an exception:
    NSLog(@"this should not be called.");
    [NSException raise:@"Define this method. This is an 'abstract' class." format:@""];
}

-(void) sendMessage:(NSString*) message
{
    [self.mediator receiveMessage:message fromColleague:self];
}

@end
