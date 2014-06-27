//
//  ImageFetcherOnOSX.h
//  naoClusteringMac
//
//  Created by Maxim Chetrusca on 5/14/14.
//  Copyright (c) 2014 Maxim Chetrusca. All rights reserved.
//

#ifndef __naoClusteringMac__ImageFetcherOnOSX__
#define __naoClusteringMac__ImageFetcherOnOSX__

#include "AbstractImageFetcher.h"

//This project is supposed to run on Mac OS X and Linux.
//On Mac OS X NAO SDK would not work, so images are aquired from filesystem:
//define the path for the images:
const char BACKGROUND_IMAGE[] = "/Users/Max/Desktop/classify/test11.png";
//classify/IMG_3149.jpg" ;
const char OBJECTS_IMAGE[] = "/Users/Max/Desktop/classify/test12.png";
//classify/IMG_3149.jpg" ;

//Because on Mac OS X NAO SDK does not run, this class is an alternative to
//access NAO camera's API, fetching images from the file system.
class ImageFetcherOnOSX: public AbstractImageFetcher
{
public:
//Getters:
    //just reads an image from the above-indicated location:
    virtual Image& getImage();
    
//Constructors:
    ImageFetcherOnOSX();
    ImageFetcherOnOSX(const ImageFetcherOnOSX& fetcher);
    
//Destructor:
    virtual ~ImageFetcherOnOSX();
    
//Overloaded Operators:
    ImageFetcherOnOSX& operator=(const ImageFetcherOnOSX& fetcher);
    friend std::ostream& operator<<(std::ostream& stream,
                                    const ImageFetcherOnOSX& fetcher);
    
};

#endif /* defined(__naoClusteringMac__ImageFetcherOnOSX__) */
