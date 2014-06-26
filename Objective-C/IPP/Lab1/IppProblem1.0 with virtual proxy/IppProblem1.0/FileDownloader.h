//
//  FileDownloader.h
//  IppProblem1.0
//
//  Created by Maxim Chetrusca on 11/21/13.
//  Copyright (c) 2013 Maxim Chetrusca. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "DownloadFileProtocol.h"

@interface FileDownloader : NSObject <DownloadFileProtocol> //The real subject

@end
