//
//  VirtualProxyDownloader.m
//  IppProblem1.0
//
//  Created by Maxim Chetrusca on 11/21/13.
//  Copyright (c) 2013 Maxim Chetrusca. All rights reserved.
//

#import "CacheProxyDownloader.h"
#import "FileDownloader.h"

@interface CacheProxyDownloader()

@property (strong, nonatomic) FileDownloader* fileDownloader; //pointer to the real subject
@property (strong, nonatomic) NSMutableArray* toDownload;
@property (strong, nonatomic) NSMutableDictionary* downloadedFiles;

@end

@implementation CacheProxyDownloader

-(id) init
{
    self = [super init];
    if (self)
    {
        _fileDownloader = [[FileDownloader alloc]init];
        _toDownload = [[NSMutableArray alloc] init];
        _downloadedFiles = [[NSMutableDictionary alloc]init];
    }
    return self;
}

#pragma mark DownloadFileDelegate implementation
-(UIImage*) downloadImageFromURL:(NSURL *)imageUrl
{
    if ([self.downloadedFiles objectForKey:imageUrl])
    {
        return [self.downloadedFiles objectForKey:imageUrl];
    }
    
    
    [self.toDownload addObject:imageUrl];
    
    if ([self.toDownload count] > 2) //magic number
    {
        UIImage *image;
        for (NSURL* url in self.toDownload)
        {
            NSLog(@"started download");
            image = [self.fileDownloader downloadImageFromURL:url];
            self.downloadedFiles[url] = image;
            
            NSLog(@"stopped download");
        }
        self.toDownload =[[NSMutableArray alloc] init];
        return image;
    }
    
    return NULL;//[self.fileDownloader downloadImageFromURL:imageUrl];
}

@end
