//
//  SpaceOrientation.h
//  naoClusteringMac
//
//  Created by Maxim Chetrusca on 5/15/14.
//  Copyright (c) 2014 Maxim Chetrusca. All rights reserved.
//

#ifndef __naoClusteringMac__SpaceOrientation__
#define __naoClusteringMac__SpaceOrientation__

#include <math.h>
#include "opencv2/opencv.hpp"
#include "Object.h"
#ifdef __linux__
#include <alerror/alerror.h>
#include <alproxies/altexttospeechproxy.h>
#include <alproxies/almotionproxy.h>
//#include <alproxies/almemoryproxy.h>
#include <alproxies/alspeechrecognitionproxy.h>
#endif

//StandZero:
//Bottom camera: [0.0536997, -3.12786e-05, 0.457903, 0.000140562, 1.0594, 0.000122512]

//StandInit:
//Bottom camera: [0.0753794, -2.93803e-05, 0.43919, 0.000171116, 1.15945, 0.000163295]


const float NAO_POSITION_ON_IMAGE_AT_START_Y = 1070.43;
const float NAO_POSITION_ON_IMAGE_AT_START_X = 640;

const float LATERAL_DISTANCE_CORRECTION_FOR_HAND_GRASPING = -0.06;
const float FORWARD_DISTANCE_CORRECTION_FOR_HAND_GRASPING = -0.18 ;

const float NAO_TORSO_OFFSET_Y = 0.0163891;
const float NAO_TORSO_OFFSET_X = -0.0286617;

class SpaceOrientation
{
public:
//    Public methods:
    std::vector<float> getBottomCameraPosition();
    Object findClosestObjectFromObjects(std::vector<Object>& objects);

    cv::Point2d computePointInRobotFrameGivenPointOnImage(
                                          cv::Point2d pointOnImage);


    float computeDistance(Object object);
    void initializePosition();

//    Getters:
    cv::Point2d& getNaoPositionOnImage();
    std::vector<float>& getNaoPositionInRobotFrame();

//Constructors:
    SpaceOrientation(std::string robotIp);
    SpaceOrientation(const SpaceOrientation& orientation);
    
//Destructor:
    virtual ~SpaceOrientation();
    
//   Overloaded operators:
    SpaceOrientation& operator=(const SpaceOrientation& orientation);
    friend std::ostream& operator<<(std::ostream& stream,
                                    const SpaceOrientation& orientation);
    
//    Private members:
private:
    cv::Point2d pointFromRobotFrameToWorldFrame(cv::Point2d pointInRobotFrame);
    cv::Point2d pointFromWorldFrameToRobotFrame(cv::Point2d pointInRobotFrame);

    float distanceBetweenPoints(cv::Point2d one, cv::Point2d two);
    float angleFromPoints(cv::Point2d one,
                                 cv::Point2d middle,
                                 cv::Point2d two);
    cv::Point2d rotatePoint(cv::Point2d point, double angleInRad);
    
    
//    Private getters:
    std::vector<float>& getNaoPreviousPositionInRobotFrame();
    std::vector<float>& getNaoPositionOnStartInRobotFrame();

//    Member variables:
    cv::Point2d naoPositionOnImage; //in the image
    std::vector<float> naoPositionInSpace;
    std::vector<float> naoPreviousPositionInSpace;
    std::vector<float> naoPositionOnStartInSpace;
    std::string robotIp;

};


#endif /* defined(__naoClusteringMac__SpaceOrientation__) */
