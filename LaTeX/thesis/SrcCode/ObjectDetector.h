//
//  ObjectDetector.h
//  naoClustering
//
//  Created by Maxim Chetrusca on 2/14/14.
//  Copyright (c) 2014 Maxim Chetrusca. All rights reserved.
//

#ifndef __naoClustering__ObjectDetector__
#define __naoClustering__ObjectDetector__

#include "Object.h"

const float MINIMAL_AREA_FOR_OBJECT_IDENTIFICATION = 2000; //pixels
const float MAXIMAL_AREA_FOR_OBJECT_IDENTIFICATION = 50000;


//Detects the objects by comparing 2 images: background and foreground;
//then extracts the subimages of objects and returns a vector of Objects
class ObjectDetector
{
public:
//Public methods:
    std::vector<Object>& detectObjectsFromImage(Image& image,
                                                Image& background);
    
//Constructors:
    ObjectDetector();
    ObjectDetector(const ObjectDetector& detector);
    
//Destructors:
    virtual ~ObjectDetector();
    
//Overloaded operators:
    ObjectDetector& operator=(const ObjectDetector& detector);
    friend std::ostream& operator<<(std::ostream& stream,
                                    const ObjectDetector& detector);
    
//Private methods:
private:
    bool rectIsInsideAnotherRect(int index,
                                 cv::vector<cv::Rect> rectangles);
    cv::Mat computeForegroundMask(Image& image,
                                  Image& background);
    void recolorDetectedPixels(cv::Mat& mat);
    
    void detectContoursInMatrixWithThresholdOutput(cv::vector<cv::vector<cv::Point> >& bestContours,
     cv::Mat gray,
     cv::Mat& threshold_output);
    
    void getGoodBoundingRectsOfContours
    (cv::vector<cv::Rect>& goodRects,
     cv::vector<cv::vector<cv::Point> > contours);
    
    void getObjectsFromRects(std::vector<Object>* detectedObjects,
                             cv::vector<cv::Rect> goodRects,
                             cv::Mat threshold_output,
                             cv::Mat src);
    cv::Mat extractForegroundAndPreprocess(Image& image,
                                           Image& background);
    void detectBoundingRectsAndEdges(cv::Mat& threshold_output,
                                     cv::vector<cv::Rect>& goodRects,
                                     cv::Mat src_gray);
    
    
};

#endif /* defined(__naoClustering__ObjectDetector__) */
