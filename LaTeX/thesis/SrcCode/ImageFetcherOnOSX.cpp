//
//  ImageFetcherOnOSX.cpp
//  naoClusteringMac
//
//  Created by Maxim Chetrusca on 5/14/14.
//  Copyright (c) 2014 Maxim Chetrusca. All rights reserved.
//

#include "ImageFetcherOnOSX.h"


//Getters:
//just reads an image from the above-indicated location:
Image& ImageFetcherOnOSX:: getImage()
{
    cv::Mat mat;
    // we take two shots: one of the background then the second of objects.
    static bool firstShoot = true;
    if (firstShoot)
    {
        mat = cv::imread( BACKGROUND_IMAGE, CV_LOAD_IMAGE_COLOR );
        firstShoot = false;
    }
    else mat = cv::imread(OBJECTS_IMAGE, CV_LOAD_IMAGE_COLOR);
    return *new Image(mat);
}

//Constructors:
ImageFetcherOnOSX:: ImageFetcherOnOSX():
AbstractImageFetcher()
{
    
}

ImageFetcherOnOSX:: ImageFetcherOnOSX(const ImageFetcherOnOSX& fetcher):
AbstractImageFetcher(fetcher)
{
    
}

//Destructor:
ImageFetcherOnOSX:: ~ImageFetcherOnOSX()
{
    
}

//Overloaded Operators:
ImageFetcherOnOSX& ImageFetcherOnOSX:: operator=
(const ImageFetcherOnOSX& fetcher)
{
    if (this != &fetcher)
    {
        this->AbstractImageFetcher::operator=(fetcher);

    }
    return *this;
}

std::ostream& operator<<(std::ostream& stream,
                         const ImageFetcherOnOSX& fetcher)
{
    stream << (AbstractImageFetcher&)fetcher << " " << std::endl;
    return stream;
}





