//
//  Locomotion.cpp
//  naoClusteringMac
//
//  Created by Maxim Chetrusca on 5/16/14.
//  Copyright (c) 2014 Maxim Chetrusca. All rights reserved.
//

#include "Locomotion.h"
//#include "opencv2/opencv.hpp"

//    Public methods:
void Locomotion:: setStiffnessOnAndStand()
{
#ifdef __linux__
    const AL::ALValue jointName = AL::ALValue::array("Body");
    try
    {
        AL::ALMotionProxy motion(robotIp);
        AL::ALValue stiffness = 1.0f;
        AL::ALValue time = 1.0f;
        
        motion.stiffnessInterpolation(jointName, stiffness, time);
        
        AL::ALRobotPostureProxy robotPosture(robotIp);
        float maxSpeedFraction = 0.5f; //[0;1]
        bool postureReached = robotPosture.goToPosture("Stand",
                                                       maxSpeedFraction);
        if (! postureReached) speech->say("Could not Stand");
    }
    catch (const AL::ALError& e) {
        std::cerr << "Caught exception: " << e.what() << std::endl;
        exit(EXIT_FAILURE);
    }
#else
    std::cout << "setStiffnessOnAndStand not on linux" << std::endl;
#endif
}

void Locomotion:: lookDown()
{
#ifdef __linux__
    /** The name of the joint to be moved. */
    const AL::ALValue jointName = AL::ALValue::array("HeadPitch", "HeadYaw");
    try {
        
        AL::ALRobotPostureProxy robotPosture(robotIp);
        AL::ALMotionProxy motion(robotIp);

        float maxSpeedFraction = 0.5f; //[0;1]
        bool postureReached = robotPosture.goToPosture("Stand",
                                                       maxSpeedFraction);
        motion.waitUntilMoveIsFinished();
        if (! postureReached)
            speech->say("Could not reach posture Stand.");
        AL::ALNavigationProxy navigationProxy(robotIp);
        float x = .5 ,y = 0, theta = 0;
        //        navigationProxy.moveTo(x, y, theta);
        
        
        /** Make sure the head is stiff to be able to move it.
         * To do so, make the stiffness go to the maximum in one second.
         */
//        /** Target stiffness. */
//        AL::ALValue stiffness = 1.0f;
//        /** Time (in seconds) to reach the target. */
//        AL::ALValue time = 1.0f;
//        /** Call the stiffness interpolation method. */
//        motion.stiffnessInterpolation(jointName, stiffness, time);
        
        /** Set the target angle list, in radians.
         Max pitch: 29.5 degrees = 0.514872129 rad
         */
        float degrees  = 21.0f;
        float rads = degrees * M_PI / 180;
        AL::ALValue targetAngles = AL::ALValue::array(rads, 0.0f);
        /** Set the corresponding time lists, in seconds. */
        AL::ALValue targetTimes = AL::ALValue::array(1.0f, 1.0f);
        /** Specify that the desired angles are absolute. */
        bool isAbsolute = true;
        
        /** Call the angle interpolation method. The joint will reach the
         * desired angles at the desired times.
         */
        motion.angleInterpolation(jointName,
                                  targetAngles,
                                  targetTimes,
                                  isAbsolute);
        motion.waitUntilMoveIsFinished();
        
//        /** Remove the stiffness on the head. */
//        stiffness = 0.0f;
//        time = 1.0f;
//        motion.stiffnessInterpolation(jointName, stiffness, time);
        
    }
    catch (const AL::ALError& e) {
        std::cerr << "Caught exception: " << e.what() << std::endl;
        exit(EXIT_FAILURE);
    }
#else
    std::cout << "lookDown not on linux" << std::endl;
#endif
}

void Locomotion:: move(float x, float y, float theta)
{
#ifdef __linux__
    try
    {
        
        AL::ALMotionProxy motion(robotIp);
        
        motion.moveInit();
        
        AL::ALNavigationProxy navigationProxy(robotIp,9559);
        if (USE_CORRECTION)
        {
            std::cout << "x, y before correction: " << x << " "
                      << y << std::endl;
            //Lateral correction: -3/20 = -0.15;
            //LATERAL_CORRECTION = 0.15;
            //=>
            //lateralDistance =
//            forwardDistance*LATERAL_CORRECTION_FOR_FORWARD_MOVEMENT;
            //forwardDistance *= FORWARD_CORRECTION;
            //lateralDistance *= LATERAL_CORRECTION;
            y += x*LATERAL_CORRECTION_FOR_FORWARD_MOVEMENT;
            y *= LATERAL_CORRECTION;
            x *= FORWARD_CORRECTION;

            std::cout << "x, y after correction: " << x << " "
                      << y << std::endl;
        }
        bool positionReached = navigationProxy.moveTo(x, y, theta);
        //, AL::ALValue::array("MaxStepX", 0.06));
        motion.waitUntilMoveIsFinished();
        if (! positionReached) speech->say("Could not walk to the object");
    }
    catch (const AL::ALError& e)
    {
        std::cerr << "Caught exception: " << e.what() << std::endl;
        exit(1);
    }
#endif
}

bool Locomotion:: moveObjects(std::vector<Object>& objects,
                              SpaceOrientation& spaceOrientation)
{
    
    //Compute positions of objects in world space;
    //Find the closest object.
    //Pick it and say in which group it goes;
    //Give it to me.
    //Repeat until done.
    int numberOfObjects = (int)objects.size();
    //Compute positions of each object:
    for (int k = 0; k < numberOfObjects; k++)
    {
        cv::Point2d center = objects[k].getImage().getCenter();
        cv::Point2d position =
        spaceOrientation.computePointInRobotFrameGivenPointOnImage(center);
        objects[k].setPositionInRobotFrame(position);
        std::cout << objects[k].getImage().getCenter() << std::endl;
        std::cout << "Objects: " <<
                     objects[k].getPositionInRobotFrame() << std::endl;
    }
    //    std::cout << "NAO in space: " << head->getNaoPositionInRobotFrame()
    //    << std::endl;
    std::cout << "NAO on image: " <<
    spaceOrientation.getNaoPositionOnImage() << std::endl;
    for (int k = 0; k < numberOfObjects; k++)
    {
        std::cout << "next object" << std::endl;
        Object object =
        spaceOrientation.findClosestObjectFromObjects(objects);
//        cv::destroyAllWindows();
        if (SHOW_IMAGES)
        {
        cv::imshow( "Image", object.getImage().getMatrix() );
        cv::waitKey();
        cv::destroyWindow("Image");
        }

        std::cout << "lets walk" << std::endl;
        walkToObject(object, spaceOrientation); // Needs to be adjusted.
//        spaceOrientation.getBottomCameraPosition();

        // Recompute object position.
        // Repeat if needed.


        //        head->getNaoPositionOnImage();
        pickObject(object);
        giveObjectAndSayResult(object);
//                pickObject(object); // Needs to be adjusted!
        //        giveObject(object);// Needs to be created!
        
        //        AL::ALNavigationProxy navigationProxy(robotIp,9559);
        //        bool positionReached =
        //        navigationProxy.moveTo(0,
        //        -LATERAL_DISTANCE_CORRECTION_FOR_HAND_GRASPING ,
        //        0); //Come back to position before grasping.
        //        if (! positionReached) say("Could not move lateral distance back.");
        
        
    }
    
    return true;
}

void Locomotion:: walkToObject(Object& object,
                               SpaceOrientation& spaceOrientation)
{
    std::cout << "1Object position: " << object.getPositionInRobotFrame() << std::endl;
//    std::cout << "1NAO position: " << spaceOrientation.getNaoPositionInRobotFrame() << std::endl;

//    turnToObject(object, spaceOrientation);
    
//    float distance = spaceOrientation.computeDistance(object);
//    std::cout << "computed distance" << distance << std::endl;
    cv::Point2d obj = object.getPositionInRobotFrame();
        obj.x += LATERAL_DISTANCE_CORRECTION_FOR_HAND_GRASPING;
        obj.y += FORWARD_DISTANCE_CORRECTION_FOR_HAND_GRASPING;
        std::vector<float> naoInSpace =
        spaceOrientation.getNaoPositionInRobotFrame();
        cv::Point2d nao(naoInSpace[1], naoInSpace[0]);
    cv::Point2d distance = obj - nao;

    move(distance.y, distance.x, 0.0);


#ifdef __linux__
    try
    {
        AL::ALRobotPostureProxy robotPosture(robotIp);
        AL::ALMotionProxy motion(robotIp);
        bool postureReached = robotPosture.goToPosture("Stand", 0.5f);
        motion.waitUntilMoveIsFinished();
        if (! postureReached) speech->say("Could not stand");
        
        std::cout << "NAO position after walk: " <<
        spaceOrientation.getNaoPositionInRobotFrame() << std::endl;

    }
    catch (const AL::ALError& e)
    {
        std::cerr << "Caught exception: " << e.what() << std::endl;
        exit(1);
    }
#else
    std::cout << "walkToObject run not on linux" << std::endl;
#endif
}

float Locomotion:: turnToObject(Object& object,
                                 SpaceOrientation& spaceOrientation)
{
    
    static cv::Point2d previousDirection(0,1);
    std::vector<float> naoInSpace =
    spaceOrientation.getNaoPositionInRobotFrame();

//    static float previousAngleRad = 0;
//    float x = naoInSpace[1];
//    float y = naoInSpace[0];
//    float theta = naoInSpace[2];
//    //    std::cout << "theta: " << theta << std::endl;
//    
//    float anotherX;
//    float anotherY;
//    
//    //    if (fabs(theta) < 0.01)
//    //    {
//    //        anotherX = x;
//    //        anotherY = y+1;
//    //    }
//    //    else
//    //    {
//    //    if ((theta >= 0.1) && (theta <= (M_PI/2 - 0.1)))
//    //    theta = M_PI/2 - theta;
//    //    if ( (theta <= 0.1) && (theta >= (-M_PI/2 + 0.1)) )
//    //    theta = -M_PI/2 - theta;
//    
//    //    float slope = tan(theta);
//    //    std::cout << "slope: " << slope << std::endl;
//    //    float n = y - slope*x;
//    //    if (slope > 0) anotherX += 0.2;
//    //    else anotherX -= 0.2;
//    //    anotherY = slope*anotherX + n;
//    //    }
//    
//    //    else
//    //    {
//    //        float a = (slope*slope + 1);
//    //        float b = (-2*x - 2*(y - n)*slope);
//    //        float c = x*x - 1 + (y - n)*(y - n);
//    //        float delta = b*b - 4*a*c;
//    //        if (delta < 0)
//    //        {
//    //            std::cout << "delta < 0" << std::endl;
//    //            exit(EXIT_FAILURE);
//    //        }
//    //        if (slope < 0) anotherX = (-b + sqrt(delta)) / (2*a);
//    //        else anotherX = (-b - sqrt(delta)) / (2*a);
//    //        anotherY = n + slope*anotherX;
//    //    }
    
    cv::Point2d one = previousDirection*2;//(anotherX, anotherY);
    //    one = head->computePointInRobotFrameGivenPointOnImage(one);
    cv::Point2d nao(naoInSpace[1], naoInSpace[0]);
    cv::Point2d two = object.getPositionInRobotFrame();

//    To correct for grasping, let's update the position where we need to go:
//    two.x += LATERAL_DISTANCE_CORRECTION_FOR_HAND_GRASPING;
//    two.y += FORWARD_DISTANCE_CORRECTION_FOR_HAND_GRASPING;
//    std::cout << two << std::endl;
    // What would happen when    two.y gets negative? test it.

    //    two = head->pointFromWorldFrameToRobotFrame(two);
    
    
    cv::Point2d direction  = two - nao;
    //    cv::normalize(previousDirection);
    //    cv::norm(previousDirection);
    //    cv::normalize(direction);
    float angle = acos(previousDirection.dot(direction) /
                       ( norm(previousDirection) * norm(direction) ));
    //nao.dot(two));
    previousDirection = direction;
    std::cout << angle << std::endl;
    
    
    //!!! set the correct sign to the angle.
    
    
    
    
    
    
    
    
    
    //    two = head->computePointOnImageGivenPointInRobotFrame(two);
    //head->computePointInRobotFrameGivenPointOnImage(
    //    object.getImage().getCenter());
    //    two.x += LATERAL_DISTANCE_CORRECTION_FOR_HAND_GRASPING;
    //    two.y += FORWARD_DISTANCE_CORRECTION_FOR_HAND_GRASPING;
    std::cout << "Points: "<<one << std::endl << nao << std::endl <<
    two << std::endl;
    //    cv::Point2d middle(1280/2, 960);
    
    //    cv::Point2d oneOnImage =
    //    head->computePointOnImageGivenPointInRobotFrame(one);
    
    float angleRad = angle;//head->angleFromPoints(one, nao, two);
    std::cout << angleRad*180/M_PI << std::endl;
    
    
    
    {
        float x1 = nao.x, x2 = two.x, y1 = nao.y, y2 = two.y;
        float a = x2 - x1;
        float b = y2 - y1;
        if (a)
        {
            float slope2 = b/a;
            float oneOnLine = slope2*one.x - slope2*x1 + y1;
            if ((slope2 < 0) && (oneOnLine < one.y)) angleRad = -angleRad;
            if ((slope2 > 0 ) && (oneOnLine > one.y)) angleRad = -angleRad;
        }
    }
    
    
    //    float twoXOnLine = slope*two.x + n;
    //    if (twoXOnLine < two.y) angleRad = -angleRad;
    //    if (nao.x > two.x) angleRad  = -angleRad;
    //        else if ((nao.x == one.x) && (nao.x > two.x)) angleRad =
//    -angleRad;
    //    angleRad = -angleRad;
    
    //    std::cout << "Previous angle: " << naoInSpace[2] << std::endl;
    //    angleRad += -naoInSpace[2];
    //    std::cout << "Previous angle to turn in degrees: " <<
    //    previousAngleRad*180/M_PI << std::endl;
    std::cout << "Angle to turn in degrees: " << angleRad*180/M_PI << std::endl;
    
    //        navigationProxy.setSecurityDistance(.1);
    //        float degrees  = 20.0f;
    //        float rads = degrees * 3.1415 / 180;
    //        for (int i = 0; i < 10; i++)
    
#ifdef __linux__
    try
    {
        
        //        lookDown(robotIp);
        
        
        
        AL::ALNavigationProxy navigationProxy(robotIp,9559);
        AL::ALMotionProxy motion(robotIp);
        
        bool positionReached;// = navigationProxy.moveTo(0,0,-previousAngleRad);
        //        if (! positionReached) say("Could not turn to the previous
//        angle");
        motion.moveInit();
        positionReached = navigationProxy.moveTo(0, 0.0, angleRad);//,
        //        AL::ALValue::array("MaxStepX", 0.06));
        motion.waitUntilMoveIsFinished();
        if (! positionReached) speech->say("Could not turn to the object");
        else std::cout << "Turned." << std::endl;
//        previousAngleRad = angleRad;
        
        return angleRad;
    }
    catch (const AL::ALError& e)
    {
        std::cerr << "Caught exception: " << e.what() << std::endl;
        exit(EXIT_FAILURE);
    }
#else
    std::cout << "turnToObject not on Linux" << std::endl;
    return angleRad;
#endif
}

void Locomotion:: pickObject(Object& object)
{
   customMoves.goDown();
    ///
#ifdef __linux__
    sleep(2);
#endif
    
    customMoves.goUp();
}

void Locomotion:: giveObjectAndSayResult(Object& object)
{
    customMoves.riseHandUp();
    
    
    std::stringstream sstm1;
    sstm1 << "Catch this object. ";
    std::string result = sstm1.str();
    speech->say(result);
    
    //Give the object...
    customMoves.openHandAndMoveItDown();
    
    std::stringstream sstm2;
    sstm2 << "It belongs to group " << object.getGroup();
    result = sstm2.str();
    speech->say(result);
    
}




//Constructors:
Locomotion:: Locomotion(const std::string& robotIp, Speech *speech):
robotIp(robotIp),
speech(speech),
customMoves(robotIp, speech)
{
    
}

Locomotion:: Locomotion(const Locomotion& locomotion):
robotIp(locomotion.robotIp),
speech(locomotion.speech),
customMoves(locomotion.customMoves)
{
    
}

//Destructor:
Locomotion:: ~Locomotion()
{
    
}

//    Overloaded operators:
Locomotion& Locomotion:: operator=(const Locomotion& locomotion)
{
    if (this != &locomotion)
    {
        robotIp = locomotion.robotIp;
        speech = locomotion.speech;
        customMoves = locomotion.customMoves;
    }
    return *this;
}

std::ostream&  operator<<(std::ostream& stream,
                                      const Locomotion& locomotion)
{
    stream << locomotion.robotIp << " " << locomotion.speech << " " <<
     locomotion.customMoves << std::endl;
    return stream;
}

//Private members:






