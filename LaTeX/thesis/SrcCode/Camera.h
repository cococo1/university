//
//  Camera.h
//  naoClustering
//
//  Created by Maxim Chetrusca on 2/14/14.
//  Copyright (c) 2014 Maxim Chetrusca. All rights reserved.
//

#ifndef __naoClustering__Camera__
#define __naoClustering__Camera__

#include "AbstractImageFetcher.h"




//!!! This class should be used on Linux only.
//On Mac OS X, use ImageFetcherOnOSX.

//Camera uses NAO API to get the image.
class Camera: public AbstractImageFetcher
{
public:
//Getters:
//    this uses NAO API to get an image from camera;
//    gets a (1280 x 960) image;
    virtual Image& getImage();
    
//Constructors:
//    cannot access NAO API without robot's IP
    Camera(const std::string& robotIp);
    Camera(const Camera& camera);
    
//Destructor:
    virtual ~Camera();
    
//Overloaded Operators:
    Camera& operator=(const Camera& camera);
    friend std::ostream& operator<<(std::ostream& stream, const Camera& camera);
    
//Member Variables:
private:
    std::string robotIp;

};

#endif /* defined(__naoClustering__Camera__) */
