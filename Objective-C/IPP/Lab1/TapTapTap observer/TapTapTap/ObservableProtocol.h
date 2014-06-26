//
//  ObservableProtocol.h
//  TapTapTap
//
//  Created by Maxim Chetrusca on 1/30/14.
//  Copyright (c) 2014 Maxim Chetrusca. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "ObserverProtocol.h"


@protocol ObservableProtocol <NSObject>

-(void) addAnObserver:(id<ObserverProtocol>)observer
           forEvent:(NSString*)event;
-(void) removeAnObserver:(id<ObserverProtocol>)observer
             fromEvent:(NSString*)event;
-(void) notifyObserversAboutEvent:(NSString*) event;



@end
