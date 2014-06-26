//
//  UIDrawView.h
//  DrawME
//
//  Created by Alexandr Macari on 21/04/2012.
//  Copyright (c) 2012 Acasa. All rights reserved.
//

#import <UIKit/UIKit.h>
typedef struct USER
{
    int r,g,b;
    float ratio;
    CGPoint *points;
    int numberOfPoints;
    BOOL clear;
}USER;

@interface UIDrawView : UIView

  -(void) setBezier;

@property (assign) USER* users;
@property (retain) NSArray* pathsToDraw;
@property (retain) NSArray* colors;
@property (assign) int numberOfUsers;

@end
