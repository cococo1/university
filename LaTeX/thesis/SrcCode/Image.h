//
//  Image.h
//  naoClustering
//
//  Created by Maxim Chetrusca on 2/13/14.
//  Copyright (c) 2014 Maxim Chetrusca. All rights reserved.
//

#ifndef __naoClustering__Image__
#define __naoClustering__Image__

#include <iostream>
#include "opencv2/core/core.hpp"
#include "opencv2/opencv.hpp"


const int IMAGE_WIDTH = 1280;
const int IMAGE_HEIGHT = 960;

const int SHOW_IMAGES = 1;


//Used to identify an image. 
class Image
{
public:
//Getters:
    cv::Mat getMatrix();
    cv::Rect getBoundingRect();
    //    center of the image in its superimage coordinates:
    cv::Point2d getCenter();

//Setters:
    void setBoundingRect(cv::Rect boundingRect);
    
//Constructors:
//    creates (0, 0, 1280, 960) default bounding rect:
    Image(const cv::Mat& matrix);
//    copies the rect of image object:
    Image(const Image& image);
    

//Destructor:
    virtual ~Image();
    
//Overloaded operators:
    Image& operator=(const Image& image);
    friend std::ostream& operator<< (std::ostream& stream, const Image& image);

//Member variables:
private:
    //    matrix of pixels:
    cv::Mat matrix;
    //    the rectangle which bounds this image in its superimage:
    cv::Rect boundingRect;
    
    
};

#endif /* defined(__naoClustering__Image__) */
