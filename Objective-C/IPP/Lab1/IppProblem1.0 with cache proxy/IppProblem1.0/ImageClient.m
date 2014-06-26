//
//  ImageClient.m
//  IppProblem1.0
//
//  Created by Maxim Chetrusca on 11/22/13.
//  Copyright (c) 2013 Maxim Chetrusca. All rights reserved.
//

#import "ImageClient.h"
#import "DownloadFileProtocol.h"
#import "CacheProxyDownloader.h"


@interface ImageClient()

@property (strong, nonatomic) id<DownloadFileProtocol> someDownloader;

@end

@implementation ImageClient

-(void) setup
{
    _someDownloader = [[CacheProxyDownloader alloc]init];
    
}

-(id) init
{
    
    self = [super init];
    if (self)
    {
        [self setup];
    }
    return self;
}

-(UIImage*) gimmeYourImageForNumber:(NSInteger)number
{
    NSString *stringForURL;
    
    switch (number)
    {
        case 1:
            stringForURL = @"https://imagesonline.bl.uk/imgcon3/590/496/cropped/jpg/152003.jpg";
            break;
        case 2:
            stringForURL = @"https://imagesonline.bl.uk/assets/thumbnails/3/3/b58a98e451574019bf8082356d7087b4.jpg";
            break;
        case 3:
            stringForURL = @"http://cdn.zmescience.com/wp-content/uploads/2011/02/Blue-Planet-Earth.jpg";
            break;
        case 4:
            stringForURL = @"http://www.thepledgetree.com/wp-content/uploads/2013/11/Tree-11.jpg";
            break;
        case 5:
            stringForURL = @"http://wallpapers.birdsnanimals.com/wp-content/uploads/2014/01/car-images-clip-art-.png";
            break;
        case 6:
            stringForURL = @"http://www.petiquettedog.com/wp-content/uploads/2010/04/sadpug.jpg";
            break;
        default:
            stringForURL = @"http://wallpapers.birdsnanimals.com/wp-content/uploads/2014/01/car-images-clip-art-.png";
            break;
    }
    NSURL* imageURL = [NSURL URLWithString: stringForURL];
    
    return [self.someDownloader downloadImageFromURL: imageURL];
}

@end
