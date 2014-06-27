//
//  Image.cpp
//  naoClustering
//
//  Created by Maxim Chetrusca on 2/13/14.
//  Copyright (c) 2014 Maxim Chetrusca. All rights reserved.
//

#include "Image.h"

//Getters:
cv::Mat Image:: getMatrix()
{
    return matrix;
}

cv::Rect Image:: getBoundingRect()
{
    return boundingRect;
}

cv::Point2d Image:: getCenter()
{
    cv::Point2d center;
    center.x = boundingRect.x + boundingRect.width/2;
    center.y = boundingRect.y + boundingRect.height/2;
    return center;
}

//Setters:
void Image:: setBoundingRect(cv::Rect boundingRect)
{
    this->boundingRect = boundingRect;
}

//Constructors:
Image::Image(const cv::Mat& matrix):
boundingRect(cv::Rect(0, 0, IMAGE_WIDTH, IMAGE_HEIGHT))
{
    matrix.copyTo(this->matrix);
    
}

Image::Image(const Image& image):
boundingRect(image.boundingRect)
{
    image.matrix.copyTo(this->matrix);
}


//Destructor:
Image::~Image()
{
    
}

//Overloaded operators:
std::ostream& operator<< (std::ostream& stream,
                          const Image& image)
{
    stream << image.boundingRect << std::endl;
    return stream;
}

Image& Image:: operator=(const Image& image)
{
    if (this != &image)
    {
        image.matrix.copyTo(this->matrix);
        boundingRect = image.boundingRect;
    }
    return *this;
}




