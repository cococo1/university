//
//  UIDrawView.m
//  DrawME
//
//  Created by Alexandr Macari on 21/04/2012.
//  Copyright (c) 2012 Acasa. All rights reserved.
//

#import "UIDrawView.h"

@implementation UIDrawView

@synthesize pathsToDraw;
@synthesize colors;
@synthesize users,numberOfUsers;

- (id)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    if (self) {
        // Initialization code
        self.backgroundColor=[UIColor whiteColor];
        self.clearsContextBeforeDrawing=NO;

    }
    return self;
}

-(void) setBezier
{
    UIColor *color;
    
    for (int i=0; i<self.numberOfUsers; i++)
    {
        if (self.users[i].numberOfPoints>0)
        {
            UIBezierPath *path = [UIBezierPath bezierPath];

            color=[[UIColor alloc]initWithRed:self.users[i].r/255.0 green:self.users[i].g/255.0 blue:self.users[i].b/255.0 alpha:1];
            NSMutableArray *newColors=[NSMutableArray arrayWithArray:self.colors];
            [newColors addObject:color];
            [color release];
            self.colors=[NSArray arrayWithArray:newColors];
            [path moveToPoint:self.users[i].points[0]];
            for (int j=1; j<self.users[i].numberOfPoints; j++)
            {
                [path addLineToPoint:self.users[i].points[j]];
            }
            path.lineWidth=2;
            free(self.users[i].points);
            self.users[i].points=NULL;
            self.users[i].numberOfPoints=0;

            NSMutableArray *newPaths=[NSMutableArray arrayWithArray:self.pathsToDraw];
            [newPaths addObject:path];
            self.pathsToDraw=[NSArray arrayWithArray:newPaths];
        }

    }
}

-(void) drawBezier
{
    UIBezierPath *path;// = [UIBezierPath bezierPath];
    int i=0;
    for (path in self.pathsToDraw )
    {
        [[self.colors objectAtIndex:i] setStroke];
        i++;
        
        [path stroke];
    }
    
}



-(void) drawLines
{
    UIColor *color;
    CGContextRef context = UIGraphicsGetCurrentContext();


    
    for (int i=0; i<self.numberOfUsers; i++)
    {
        UIGraphicsPushContext(context);
        CGContextBeginPath(context);
        color=[[UIColor alloc]initWithRed:self.users[i].r/255.0 green:self.users[i].g/255.0 blue:self.users[i].b/255.0 alpha:1];
        [color setStroke];
        [color release];
        CGContextSetLineWidth(context, 2);
        if (self.users[i].numberOfPoints>=2)
        {
            CGContextMoveToPoint(context, self.users[i].points[0].x, self.users[i].points[0].y);
            for (int j=1; j<self.users[i].numberOfPoints; j++)
            {

                    CGContextAddLineToPoint(context, self.users[i].points[j].x, self.users[i].points[j].y);
            }
            CGContextStrokePath(context);

        }
        UIGraphicsPopContext();

    }
   }


// Only override drawRect: if you perform custom drawing.
// An empty implementation adversely affects performance during animation.
- (void)drawRect:(CGRect)rect
{
    // Drawing code
    [self drawBezier];
    [self drawLines];
    
    

}


@end
