//
//  FileDownloader.m
//  IppProblem1.0
//
//  Created by Maxim Chetrusca on 11/21/13.
//  Copyright (c) 2013 Maxim Chetrusca. All rights reserved.
//

#import "FileDownloader.h"


@implementation FileDownloader


-(id) init
{
    self = [super init];
    if (self)
    {

    }
    return self;
}

#pragma mark DownloadFileDelegate implementation
-(UIImage*) downloadImageFromURL:(NSURL*)imageUrl
{
//    NSLog(@"download");
    NSData* imageData = [[NSData alloc] initWithContentsOfURL: imageUrl];
    sleep(1 + arc4random() % 3); // simulate a time-consuming task
    UIImage* image = [UIImage imageWithData: imageData];
    
    return image;
}


@end
