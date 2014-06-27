//
//  SpaceOrientation.cpp
//  naoClusteringMac
//
//  Created by Maxim Chetrusca on 5/15/14.
//  Copyright (c) 2014 Maxim Chetrusca. All rights reserved.
//

#include "SpaceOrientation.h"
//#include "Image.h"

//    Public methods:
std::vector<float> SpaceOrientation:: getBottomCameraPosition()
{
    //Computed experimentally in position Stand:
    std::vector<float> position;
    position.push_back(0.0188118);
    position.push_back(0.0357351);
    position.push_back(0.481532);
    position.push_back(0);
    position.push_back(0);
    position.push_back(0);

#ifdef __linux__
    try
    {
        AL::ALMotionProxy motion(robotIp);
//        std::cout << motion.getSensorNames() << std::endl;
//        std::cout << motion.() << std::endl;
        bool useSensorValues = true;
        int space = 2; //FRAME_ROBOT
        position = motion.getPosition("CameraBottom",
                                                     space,
                                                     useSensorValues);
        std::cout << "Bottom camera: " << position << std::endl;
//        std::cout << "Bottom camera height angle: " << position[4]*180 / M_PI << std::endl;
//        std::cout << "Bottom camera width angle: " << position[3]*180 / M_PI << std::endl;


//        position.x = pos[1];
//        position.y = pos[0];
//        position.z = pos[2];
    }
    catch (const AL::ALError& e)
    {
        std::cerr << "Caught exception: " << e.what() << std::endl;
        exit(EXIT_FAILURE);
    }

#endif
    return position;
}

Object SpaceOrientation:: findClosestObjectFromObjects(
                                                  std::vector<Object>& objects)
{
    std::cout << "find the closest object" << std::endl;
    float minDistance = 10000;
    std::vector<Object>::iterator closestObjectIt;
    Object closestObject = objects[0];
    
    for(std::vector<Object>::iterator it = objects.begin();
        it != objects.end();
        ++it)
    {
        float distance = computeDistance((*it));
        if (distance < minDistance)
        {
            minDistance = distance;
            closestObject = (*it);
            closestObjectIt = it;
        }
    }
    objects.erase(closestObjectIt);

    return closestObject;
}

cv::Point2d SpaceOrientation:: computePointInRobotFrameGivenPointOnImage(
                                                cv::Point2d pointOnImage)
{
    // How do we compute a point in space?
    // 1. We should have a reference in the image - that is, NAO's position;
    // 2. We know the size of the image;
    // 3. We know the coordinates in pixels of that point on image;
    // 4. We know what is height of the camera and its angle =>
    // 5. We can compute the max. forward distance in the image;
    // 6. We know the lateral angle of view of the camera, thus we can compute
//    the max. lateral distance;
    // 7. Knowing max. forward and lateral distances, we can compute the lateral
//    and forward
    //    distance of the point on image;
    // 8. We add those two to the reference in the image - but only taking into
//    account the orientation;
    
    cv::Point2d naoOnImage = getNaoPositionOnImage();
   
    float centerYPercentage = (naoOnImage.y - pointOnImage.y) /
    NAO_POSITION_ON_IMAGE_AT_START_Y;
    float centerXPercentage = (pointOnImage.x - IMAGE_WIDTH/2 + naoOnImage.x)  /
    IMAGE_WIDTH;
    
//    float angleAtZeroHeight = 26.48; // all angles are in degrees
    std::vector<float> cameraPos = getBottomCameraPosition();
    float currentCameraYAngle = cameraPos[4] * 180 / M_PI;
    float cameraViewHeightAngle = 47.64;
    float cameraViewWidthAngle = 60.97;
    float angleAtZeroWidth = cameraViewWidthAngle / 2;
    
//    float alpha = 21.0; //head pitch degree
    float objectHeightAngle = 90 - currentCameraYAngle -
            cameraViewHeightAngle/2 +
            //angleAtZeroHeight - alpha +
    centerYPercentage*cameraViewHeightAngle;//beta
    float objectHeightAngleRads = objectHeightAngle * M_PI / 180;

//    std::cout << "Camera height view angle: " << objectHeightAngleRads << std::endl;


    float cameraHeight = cameraPos[2];
            //0.45959; //in meters ; should be 452 mm
    //    float cameraNeckDistance = 0.05071; //should be 5 mm
    // fabs(tan...) //b:
    float forwardDistance = cameraHeight * tan(objectHeightAngleRads) +
            cameraPos[0] - 0.0537006; //correction
//        forwardDistance += 0.0077;
    
    // !!! Whoa, forward distance is recomputed below.
//    Do we need to adjust it???
    float cameraProjectionDistance = sqrt(forwardDistance*forwardDistance +
                                          cameraHeight*cameraHeight); //a
    float objectWidthAngle = -angleAtZeroWidth - 0 +
    centerXPercentage*cameraViewWidthAngle; //alpha
    float objectWidthAngleRads =  objectWidthAngle * M_PI / 180;

//    std::cout << "Camera width view angle: " << objectWidthAngleRads << std::endl;



    //!!! Work here!
    float lateralDistance = cameraProjectionDistance *
            tan(objectWidthAngleRads) - cameraPos[1];
    //forwardDistance * tan(-angleOfTurnRad);
    
//    std::cout << "Distances: " << lateralDistance << " " << forwardDistance
//    << std::endl;
    
    cv::Point2d distanceInWorldSpace = pointFromRobotFrameToWorldFrame(
                           cv::Point2d(lateralDistance, forwardDistance));
////    Corrections for StandZero:
//    distanceInWorldSpace.y += 0.0077;
//    distanceInWorldSpace.x += -0.0016;

//    Corrections for Stand:
      distanceInWorldSpace.y += 0.0059;
      distanceInWorldSpace.x += 0.0113;


////     Corrections for StandInit:
//    distanceInWorldSpace.y -= 0.0035;
//    distanceInWorldSpace.x += 0.0036;

    std::cout << "Distances in world space: " << distanceInWorldSpace.x << " "
    << distanceInWorldSpace.y << std::endl;

    std::vector<float> currentPosition = getNaoPositionInRobotFrame();
    cv::Point2d naoCurrentPosition(currentPosition[1], currentPosition[0]);

    cv::Point2d result(-distanceInWorldSpace.x + naoCurrentPosition.x,
                       distanceInWorldSpace.y + naoCurrentPosition.y);
    
    return result;
}



float SpaceOrientation:: computeDistance(Object object)
{
    //computePointInRobotFrameGivenPointOnImage(object.getImage().getCenter());
    cv::Point2d one1 = object.getPositionInRobotFrame();

//    //    To correct for grasping, let's update the position where we need to go:
//        one1.x += LATERAL_DISTANCE_CORRECTION_FOR_HAND_GRASPING;
//        one1.y += FORWARD_DISTANCE_CORRECTION_FOR_HAND_GRASPING;
//        // What would happen when    two.y gets negative? test it.

    std::vector<float> nao = getNaoPositionInRobotFrame();
    cv::Point2d two1(nao[1], nao[0]);
    return distanceBetweenPoints(one1, two1);

}

void SpaceOrientation:: initializePosition()
{
#ifdef __linux__
    try
    {
        AL::ALMotionProxy motion(robotIp);
        bool useSensors = true;
        naoPositionOnStartInSpace = motion.getRobotPosition(useSensors);
//        std::cout << "sensors: " << naoPositionOnStartInSpace << std::endl;
        cv::Point2d startPosition(naoPositionOnStartInSpace[1],
                                  naoPositionOnStartInSpace[0]);
        startPosition = rotatePoint(startPosition,
                                    naoPositionOnStartInSpace[2]);
//        std::cout << "rotation: " << rotatePoint(cv::Point2d(1,1), -M_PI/2);
        naoPositionOnStartInSpace[0] = startPosition.y;
        naoPositionOnStartInSpace[1] = startPosition.x;

//        std::cout << "Start position: " << startPosition << std::endl;

        naoPositionInSpace.push_back(0);
        naoPositionInSpace.push_back(0);
        naoPositionInSpace.push_back(0);
        naoPreviousPositionInSpace = naoPositionInSpace;

    }
    catch (const AL::ALError& e)
    {
        std::cerr << "Caught exception: " << e.what() << std::endl;
        exit(EXIT_FAILURE);
    }
#else
    std::cout << "initializePosition() not on Linux." << std::endl;
    naoPositionInSpace.push_back(0);
    naoPositionInSpace.push_back(0);
    naoPositionInSpace.push_back(0);
    naoPreviousPositionInSpace = naoPositionInSpace;
    naoPositionOnStartInSpace = naoPositionInSpace;

#endif
}

cv::Point2d& SpaceOrientation:: getNaoPositionOnImage()
{
    
    //        naoPositionOnImage
    //        recomputeNAOPositionOnImage();
    //        naoPreviousPositionInSpace = naoPositionInSpace;
    //        std::cout << "NAO on image: " << naoPositionOnImage << std::endl;
    return naoPositionOnImage;
}

std::vector<float>& SpaceOrientation:: getNaoPositionInRobotFrame()
{
#ifdef __linux__
    try
    {
        AL::ALMotionProxy motion(robotIp);
        bool useSensors = true;
        std::vector<float> sensorsPosition =
        motion.getRobotPosition(useSensors);
        //        std::cout << "sensors: " << sensorsPosition << std::endl;
        cv::Point2d position(sensorsPosition[1], sensorsPosition[0]);
        position = rotatePoint(position, naoPositionOnStartInSpace[2]);
        //        if (! naoPreviousPositionInSpace.size())
        //        {
        //            naoPreviousPositionInSpace.push_back(0);
        //            naoPreviousPositionInSpace.push_back(0);
        //            naoPreviousPositionInSpace.push_back(0);
        //        }
        
        //        std::cout << "Position after rotation: " <<
//        position << std::endl;
        naoPositionInSpace[0] = position.y - naoPositionOnStartInSpace[0];
        naoPositionInSpace[1] = position.x - naoPositionOnStartInSpace[1];
        // - naoPositionOnStartInSpace[1];
        naoPositionInSpace[2] = sensorsPosition[2] -
        naoPositionOnStartInSpace[2];
        
        //        cv::Point2d naoPoint(naoPositionInSpace[1],
//        naoPositionInSpace[0]);
        
    }
    catch (const AL::ALError& e)
    {
        std::cerr << "Caught exception: " << e.what() << std::endl;
        exit(EXIT_FAILURE);
    }
#else
    std::cout << "getNaoPositionInRobotFrame() not on Linux." << std::endl;
#endif
    return naoPositionInSpace;
}


//Constructors:
SpaceOrientation:: SpaceOrientation(std::string robotIp):
naoPositionOnImage(cv::Point2d(NAO_POSITION_ON_IMAGE_AT_START_X,
                               NAO_POSITION_ON_IMAGE_AT_START_Y)),
    robotIp(robotIp)
{
    
}

SpaceOrientation:: SpaceOrientation(const SpaceOrientation& orientation):
naoPositionOnImage(orientation.naoPositionOnImage),
naoPositionInSpace(orientation.naoPositionInSpace),
naoPreviousPositionInSpace(orientation.naoPreviousPositionInSpace),
    robotIp(orientation.robotIp),
    naoPositionOnStartInSpace(orientation.naoPositionOnStartInSpace)

{
    
}

//Destructors:
SpaceOrientation:: ~SpaceOrientation()
{
    
}

//    Overloaded operators:
SpaceOrientation& SpaceOrientation:: operator=(
                                   const SpaceOrientation& orientation)
{
    if (this != &orientation)
    {
        //Destructor stuff:
        
    
        //... copy constructor stuff:
        naoPositionOnImage = orientation.naoPositionOnImage;
        naoPositionInSpace = orientation.naoPositionInSpace;
        naoPreviousPositionInSpace = orientation.naoPreviousPositionInSpace;
        naoPositionOnStartInSpace = orientation.naoPositionOnStartInSpace;
        robotIp = orientation.robotIp;
        
    }
    return *this;
}

std::ostream& operator<<(std::ostream& stream,
                                const SpaceOrientation& orientation)
{
    stream << orientation.naoPositionOnImage << " " << orientation.robotIp <<
    std::endl;
    return stream;
}

//    Private members:
cv::Point2d SpaceOrientation:: pointFromRobotFrameToWorldFrame(
                                           cv::Point2d pointInRobotFrame)
{
    double theta = 0;
    std::vector<float> currentPosition = getNaoPositionInRobotFrame();
    theta = currentPosition[2];

    
    cv::Mat rotationMatrix = (cv::Mat_<double>(4,4) <<
                              cos(theta), -sin(theta), 0, 0,
                              sin(theta), cos(theta),  0, 0,
                              0,          0,           1, 0,
                              0,          0,           0, 1
                              );
    cv::Mat pointMatrix = (cv::Mat_<double>(4, 1) <<
                           pointInRobotFrame.x,
                           pointInRobotFrame.y,
                           0, //we do not use z
                           1
                           );
    cv::Mat result = rotationMatrix * pointMatrix;
    //    std::cout << "Result of rotation: " << result << std::endl;
    return cv::Point2d(result.at<double>(0), result.at<double>(1));
    
    //    rotationMatrix.at
}

cv::Point2d SpaceOrientation:: pointFromWorldFrameToRobotFrame(
                                           cv::Point2d pointInWorldFrame)
{
    double theta = 0;
    std::vector<float> currentPosition = getNaoPositionInRobotFrame();
    theta = -currentPosition[2];
    
    cv::Mat rotationMatrix = (cv::Mat_<double>(4,4) <<
                              cos(theta), -sin(theta), 0, 0,
                              sin(theta), cos(theta),  0, 0,
                              0,          0,           1, 0,
                              0,          0,           0, 1
                              );
    cv::Mat pointMatrix = (cv::Mat_<double>(4, 1) <<
                           pointInWorldFrame.x,
                           pointInWorldFrame.y,
                           0, //we do not use z
                           1
                           );
    cv::Mat result = rotationMatrix * pointMatrix;
    std::cout << "Result of rotation (to robot frame): " << result << std::endl;
    return cv::Point2d(result.at<double>(0), result.at<double>(1));
    
    //    rotationMatrix.at
}

float SpaceOrientation:: distanceBetweenPoints(cv::Point2d one, cv::Point2d two)
{
    float dx = one.x - two.x;
    float dy = one.y - two.y;
    return sqrt( dx*dx + dy*dy);
}

float SpaceOrientation:: angleFromPoints(cv::Point2d one,
                                                cv::Point2d middle,
                                                cv::Point2d two)
{
    
    //    float dx = two.x - one.x;
    //    float dy = two.y - one.y;
    //    float yy = middle.y - dy;
    //    return -atan(dx/yy);
    float a = distanceBetweenPoints(one, middle);
    float b = distanceBetweenPoints(two, middle);
    float c = distanceBetweenPoints(one, two);
    //    std::cout << a << " " << b " " <<
    float angleInRads = 0;
    if ( (a > 0) && (b > 0) ) angleInRads = acos((a*a + b*b - c*c) / (2*a*b));
    else std::cout << "Distances are equal or less than zero!" << std::endl;
    
    
    if (angleInRads < 0 ) std::cout << "Angle is less than zero!" << std::endl;
    return angleInRads;
}


cv::Point2d SpaceOrientation:: rotatePoint(cv::Point2d point, double angleInRad)
{
    double theta = angleInRad;

    cv::Mat rotationMatrix = (cv::Mat_<double>(2,2) <<
                              cos(theta), -sin(theta),
                              sin(theta), cos(theta)
                              );
    cv::Mat pointMatrix = (cv::Mat_<double>(2, 1) <<
                           point.x,
                           point.y
                           );
    cv::Mat result = rotationMatrix * pointMatrix;
//    std::cout << "Result of rotation (to robot frame): " << result <<
//    std::endl;
    return cv::Point2d(result.at<double>(0), result.at<double>(1));

}


std::vector<float>& SpaceOrientation:: getNaoPreviousPositionInRobotFrame()
{
    return naoPreviousPositionInSpace;
}

std::vector<float>& SpaceOrientation:: getNaoPositionOnStartInRobotFrame()
{
    return naoPositionOnStartInSpace;
}



