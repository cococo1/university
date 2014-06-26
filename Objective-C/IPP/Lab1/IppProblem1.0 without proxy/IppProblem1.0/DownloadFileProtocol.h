//
//  DownloadFileDelegate.h
//  IppProblem1.0
//
//  Created by Maxim Chetrusca on 11/21/13.
//  Copyright (c) 2013 Maxim Chetrusca. All rights reserved.
//

#import <Foundation/Foundation.h>

@protocol DownloadFileProtocol <NSObject>

-(UIImage*) downloadImageFromURL:(NSURL*)imageUrl;

@end
