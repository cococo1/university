//
//  ObjectDetector.cpp
//  naoClustering
//
//  Created by Maxim Chetrusca on 2/14/14.
//  Copyright (c) 2014 Maxim Chetrusca. All rights reserved.
//

#include "ObjectDetector.h"

#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/video/background_segm.hpp"
#include "opencv2/opencv.hpp"

//Public methods:
std::vector<Object>& ObjectDetector::
detectObjectsFromImage(Image& image, Image& background)
{
    // 1. Extract background and preprocess;
    // 2. Detect bounding edges and rects;
    // 3. Create "objects" from those rects.
    
    cv::Mat src_gray;
    extractForegroundAndPreprocess(image, background).copyTo(src_gray);

    // Detect contours/edges using Threshold;
    // Approximate contours to polygons + get bounding rects:
    cv::Mat threshold_output;
    cv::vector<cv::Rect> goodRects;
    detectBoundingRectsAndEdges(threshold_output, goodRects, src_gray);
    
    // Create the objects from those rects:
    cv::Mat src = image.getMatrix();
    std::vector<Object>* detectedObjects = new std::vector<Object>();

    getObjectsFromRects(detectedObjects,
                        goodRects,
                        threshold_output,
                        src);

    return *detectedObjects;
}

//Constructors:
ObjectDetector:: ObjectDetector()
{
    
}

ObjectDetector:: ObjectDetector(const ObjectDetector& detector)
{
    
}

//Destructors:
ObjectDetector:: ~ObjectDetector()
{
    
}

//Overloaded operators:
ObjectDetector& ObjectDetector:: operator=(const ObjectDetector& detector)
{
    if (this != &detector)
    {
        
    }
    
    return *this;
}


std::ostream& operator<<(std::ostream& stream, const ObjectDetector& detector)
{
    return stream;
}

//Private methods:
bool ObjectDetector:: rectIsInsideAnotherRect(int index,
                                              cv::vector<cv::Rect> rectangles)
{
    bool result = false;
    cv::Rect currentRectangle = rectangles[index];
    cv::Point2d center;
    center.x = currentRectangle.x + currentRectangle.width/2;
    center.y = currentRectangle.y + currentRectangle.height/2;
    for( int i = 0; i < rectangles.size(); i++ )
    {
        if (i != index)
        {

            if (rectangles[i].contains(center) &&
                (currentRectangle.area() < rectangles[i].area()))
            {
                result = true;
                break;
            }
        }
    }
    return result;
}

cv::Mat ObjectDetector:: computeForegroundMask(Image& image, Image& background)
{
    cv::Mat mask;
    int history = 20;
    int varThreshold = 50;
    bool shadowDetection = true;
    cv::Ptr<cv::BackgroundSubtractor> subtractor =
    new cv::BackgroundSubtractorMOG2(history,
                                     varThreshold,
                                     shadowDetection);
    subtractor->set("fVarInit", 100);
    subtractor->set("fTau", 0);
    
    subtractor->operator()(background.getMatrix(), mask);
    subtractor->operator()(image.getMatrix(), mask);
    subtractor.release();
    
    if (SHOW_IMAGES)
    {
    cv::imshow("background", background.getMatrix());
    cv::waitKey(0);
    cv::destroyWindow("background");
    
    cv::imshow("objects", image.getMatrix());
    cv::waitKey(0);
    cv::destroyWindow("objects");
    
    cv::imshow("mask with shadow", mask);
    cv::waitKey(0);
    cv::destroyWindow("mask with shadow");
    }
    
    //the subtractor recolors the shadow into 127 intensity;
    //so to eliminate the shadow, just recolor these pixels:
    for (int i = 0; i < mask.rows; i++)
    {
        for (int j = 0; j < mask.cols; j++)
        {
            if (mask.at<uchar>(i,j) == 127)
            {
                mask.at<uchar>(i,j) = 0;
            }
        }
    }
    if (SHOW_IMAGES)
    {
    imshow("mask without shadow", mask);
    cv::waitKey(0);
    cv::destroyWindow("mask without shadow");
    }
    return mask;
}

void ObjectDetector:: recolorDetectedPixels(cv::Mat& mat)
{
    for( int y = 0; y < mat.rows; y++ )
    {
        for( int x = 0; x < mat.cols; x++ )
        {
            cv::Vec3b pixel = mat.at<cv::Vec3b>(y,x);
            
            if ((pixel.val[0] == 0) && (pixel.val[1] == 0) &&
                (pixel.val[2] == 0) )
            {
                pixel.val[0] = 255;
                pixel.val[1] = 255;
                pixel.val[2] = 255;
                
                mat.at<cv::Vec3b>(y,x) = pixel;
                
            }
            else
            {
                pixel.val[0] = 0;
                pixel.val[1] = 0;
                pixel.val[2] = 0;
                
                mat.at<cv::Vec3b>(y,x) = pixel;
                
            }
        }
    }
}

void ObjectDetector:: detectContoursInMatrixWithThresholdOutput(
    cv::vector<cv::vector<cv::Point> >& bestContours,
    cv::Mat gray,
    cv::Mat& threshold_output)
{
    int maxNumberOfContours = 0;
    for (int i = 0; i < 256; i++)
    {
        threshold( gray, threshold_output, i, 255, cv::THRESH_BINARY );

        cv::vector<cv::vector<cv::Point> > contours;
        cv::vector<cv::Vec4i> hierarchy;
        findContours( threshold_output,
                     contours,
                     hierarchy,
                     CV_RETR_TREE,
                     CV_CHAIN_APPROX_SIMPLE,
                     cv::Point(0, 0) );
        int currentNumberOfContours = 0;
        for (int j = 0; j < contours.size(); j++)
        {
            float area = contourArea(contours[j]);
            if ((area > MINIMAL_AREA_FOR_OBJECT_IDENTIFICATION) &&
                (area < MAXIMAL_AREA_FOR_OBJECT_IDENTIFICATION))
            {
                currentNumberOfContours++;
            }
        }
        if (currentNumberOfContours > maxNumberOfContours)
        {
            maxNumberOfContours = currentNumberOfContours;
            bestContours = contours;
        }
    }
}

void ObjectDetector::
getGoodBoundingRectsOfContours(
    cv::vector<cv::Rect>& goodRects,
    cv::vector<cv::vector<cv::Point> > contours)
{
    // Approximate contours to polygons + get bounding rects
    cv::vector<cv::vector<cv::Point> > contours_poly( contours.size() );
    cv::vector<cv::Rect> boundRect( contours.size() );
    
    for( int i = 0; i < contours.size(); i++ )
    {
        approxPolyDP( cv::Mat(contours[i]),
                     contours_poly[i],
                     3,
                     true );
        boundRect[i] = boundingRect( cv::Mat(contours_poly[i]) );
    }
    
    for( int i = 0; i< contours.size(); i++ )
    {
        float area = contourArea(contours[i]);
        if ((area > MINIMAL_AREA_FOR_OBJECT_IDENTIFICATION) &&
            (area < MAXIMAL_AREA_FOR_OBJECT_IDENTIFICATION))// && !isInside)
        {
            std::cout << "Rect: " << boundRect[i] << std::endl;
            if (boundRect[i].br().y < 900)
            goodRects.push_back(boundRect[i]);
        }
    }
}

void ObjectDetector::
getObjectsFromRects(std::vector<Object>* detectedObjects,
                    cv::vector<cv::Rect> goodRects,
                    cv::Mat threshold_output,
                    cv::Mat src)
{
    //Random Number Generator class
    int state = 12345; //just followed the tutorial
    cv::RNG rng(state);
    cv::Mat drawing = cv::Mat::zeros( threshold_output.size(), CV_8UC3 );
    
    //            cout << area << endl;
    for( int i = 0; i< goodRects.size(); i++ )
    {
        cv::Scalar color =
        cvScalar(rng.uniform(0, 255),
                 rng.uniform(0,255),
                 rng.uniform(0,255) );
        
        if (! rectIsInsideAnotherRect(i, goodRects))
        {
            rectangle( drawing,
                      goodRects[i].tl(),
                      goodRects[i].br(),
                      color,
                      2,
                      8,
                      0 );
            cv::Mat objectMat;
            src(goodRects[i]).copyTo(objectMat); //or recolored_src ???
            if (objectMat.cols > objectMat.rows)
            {
                //perform rotation
                objectMat = objectMat.t();
            }
            
            Image objectImage(objectMat);
            objectImage.setBoundingRect(goodRects[i]);
            Object detectedObject(objectImage);
            detectedObjects->push_back(detectedObject);
        }
    }
    if (SHOW_IMAGES)
    {
    cv::imshow("after detection", drawing);
    cv::waitKey();
    cv::destroyWindow("after detection");
    }
//    std::cout << "after detection" << std::endl;
    
}

cv::Mat ObjectDetector:: extractForegroundAndPreprocess(Image& image,
                                                        Image& background)
{
    cv::Mat mask;
    computeForegroundMask(image, background).copyTo(mask);
    
    cv::Mat src = image.getMatrix();
    cv::Mat recolored_src;
    src.copyTo(recolored_src, mask); //copy using mask.
    
    //  Recolor the detected pixels:
    recolorDetectedPixels(recolored_src);
    if (SHOW_IMAGES)
    {
    cv::imshow( "After background sub", recolored_src );
    cv::waitKey();
    cv::destroyWindow("After background sub");
    }

    cv::Mat src_gray;
    // Convert image to gray and blur it
    cvtColor( recolored_src, src_gray, CV_BGR2GRAY );
    blur(src_gray,
         src_gray,
         cv::Size(3,3) );
    if (SHOW_IMAGES)
    {
    cv::imshow( "Gray", src_gray );
    cv::waitKey();
    cv::destroyWindow("Gray");
    }

    return src_gray;
}

void ObjectDetector:: detectBoundingRectsAndEdges(cv::Mat& threshold_output,
                                            cv::vector<cv::Rect>& goodRects,
                                                  cv::Mat src_gray)
{
    // Detect contours/edges using Threshold
    cv::vector<cv::vector<cv::Point> > bestContours;
    detectContoursInMatrixWithThresholdOutput(bestContours,
                                              src_gray,
                                              threshold_output);
    
    cv::vector<cv::vector<cv::Point> > contours;
    contours = bestContours;
    
    // Approximate contours to polygons + get bounding rects:
    getGoodBoundingRectsOfContours(goodRects, contours);
}


