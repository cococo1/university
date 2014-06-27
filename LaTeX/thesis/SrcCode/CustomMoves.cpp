//
//  CustomMoves.cpp
//  naoClusteringMac
//
//  Created by Maxim Chetrusca on 5/16/14.
//  Copyright (c) 2014 Maxim Chetrusca. All rights reserved.
//

#include "CustomMoves.h"

//Constructors:
CustomMoves:: CustomMoves(const std::string& robotIp, Speech *speech):
robotIp(robotIp),
speech(speech)
{
    
}

CustomMoves:: CustomMoves(const CustomMoves& customMoves):
robotIp(customMoves.robotIp),
speech(customMoves.speech)
{
    
}

//Destructor:
CustomMoves:: ~CustomMoves()
{
    
}

//    Overloaded operators:
CustomMoves& CustomMoves:: operator=(const CustomMoves& customMoves)
{
    if (this != &customMoves)
    {
        robotIp = customMoves.robotIp;
        speech = customMoves.speech;
    }
    return *this;
}

std::ostream&  operator<<(std::ostream& stream,
                          const CustomMoves& customMoves)
{
    stream << customMoves.robotIp << " " << customMoves.speech << std::endl;
    return stream;
}

//Public methods:
void CustomMoves:: goDown()
{
#ifdef __linux__
    // Choregraphe bezier export in c++.
    // Add #include <alproxies/almotionproxy.h> at the beginning of this file.
    std::vector<std::string> names;
    AL::ALValue times, keys;
    names.reserve(26);
    times.arraySetSize(26);
    keys.arraySetSize(26);
    
    names.push_back("HeadPitch");
    times[0].arraySetSize(2);
    keys[0].arraySetSize(2);
    
    times[0][0] = 1.00000;
    keys[0][0] = AL::ALValue::array(-0.170000,
                                    AL::ALValue::array(3, -0.333333, -0.00000),
                                    AL::ALValue::array(3, 1.00000, 0.00000));
    times[0][1] = 4.00000;
    keys[0][1] = AL::ALValue::array(-0.671952,
                                    AL::ALValue::array(3, -1.00000, -0.00000),
                                    AL::ALValue::array(3, 0.00000, 0.00000));
    
    names.push_back("HeadYaw");
    times[1].arraySetSize(2);
    keys[1].arraySetSize(2);
    
    times[1][0] = 1.00000;
    keys[1][0] = AL::ALValue::array(0.00000,
                                    AL::ALValue::array(3, -0.333333, -0.00000),
                                    AL::ALValue::array(3, 1.00000, 0.00000));
    times[1][1] = 4.00000;
    keys[1][1] = AL::ALValue::array(-0.0153821,
                                    AL::ALValue::array(3, -1.00000, -0.00000),
                                    AL::ALValue::array(3, 0.00000, 0.00000));
    
    names.push_back("LAnklePitch");
    times[2].arraySetSize(2);
    keys[2].arraySetSize(2);
    
    times[2][0] = 1.00000;
    keys[2][0] = AL::ALValue::array(0.0900000,
                                    AL::ALValue::array(3, -0.333333, -0.00000),
                                    AL::ALValue::array(3, 1.00000, 0.00000));
    times[2][1] = 4.00000;
    keys[2][1] = AL::ALValue::array(-0.698011,
                                    AL::ALValue::array(3, -1.00000, -0.00000),
                                    AL::ALValue::array(3, 0.00000, 0.00000));
    
    names.push_back("LAnkleRoll");
    times[3].arraySetSize(2);
    keys[3].arraySetSize(2);
    
    times[3][0] = 1.00000;
    keys[3][0] = AL::ALValue::array(-0.130000,
                                    AL::ALValue::array(3, -0.333333, -0.00000),
                                    AL::ALValue::array(3, 1.00000, 0.00000));
    times[3][1] = 4.00000;
    keys[3][1] = AL::ALValue::array(0.133500,
                                    AL::ALValue::array(3, -1.00000, -0.00000),
                                    AL::ALValue::array(3, 0.00000, 0.00000));
    
    names.push_back("LElbowRoll");
    times[4].arraySetSize(2);
    keys[4].arraySetSize(2);
    
    times[4][0] = 1.00000;
    keys[4][0] = AL::ALValue::array(-0.404262,
                                    AL::ALValue::array(3, -0.333333, -0.00000),
                                    AL::ALValue::array(3, 1.00000, 0.00000));
    times[4][1] = 4.00000;
    keys[4][1] = AL::ALValue::array(-0.616627,
                                    AL::ALValue::array(3, -1.00000, -0.00000),
                                    AL::ALValue::array(3, 0.00000, 0.00000));
    
    names.push_back("LElbowYaw");
    times[5].arraySetSize(2);
    keys[5].arraySetSize(2);
    
    times[5][0] = 1.00000;
    keys[5][0] = AL::ALValue::array(-1.18636,
                                    AL::ALValue::array(3, -0.333333, -0.00000),
                                    AL::ALValue::array(3, 1.00000, 0.00000));
    times[5][1] = 4.00000;
    keys[5][1] = AL::ALValue::array(-0.805393,
                                    AL::ALValue::array(3, -1.00000, -0.00000),
                                    AL::ALValue::array(3, 0.00000, 0.00000));
    
    names.push_back("LHand");
    times[6].arraySetSize(2);
    keys[6].arraySetSize(2);
    
    times[6][0] = 1.00000;
    keys[6][0] = AL::ALValue::array(0.00523599,
                                    AL::ALValue::array(3, -0.333333, -0.00000),
                                    AL::ALValue::array(3, 1.00000, 0.00000));
    times[6][1] = 4.00000;
    keys[6][1] = AL::ALValue::array(0.0174533,
                                    AL::ALValue::array(3, -1.00000, -0.00000),
                                    AL::ALValue::array(3, 0.00000, 0.00000));
    
    names.push_back("LHipPitch");
    times[7].arraySetSize(2);
    keys[7].arraySetSize(2);
    
    times[7][0] = 1.00000;
    keys[7][0] = AL::ALValue::array(0.130000,
                                    AL::ALValue::array(3, -0.333333, -0.00000),
                                    AL::ALValue::array(3, 1.00000, 0.00000));
    times[7][1] = 4.00000;
    keys[7][1] = AL::ALValue::array(-1.33607,
                                    AL::ALValue::array(3, -1.00000, -0.00000),
                                    AL::ALValue::array(3, 0.00000, 0.00000));
    
    names.push_back("LHipRoll");
    times[8].arraySetSize(2);
    keys[8].arraySetSize(2);
    
    times[8][0] = 1.00000;
    keys[8][0] = AL::ALValue::array(0.100000,
                                    AL::ALValue::array(3, -0.333333, -0.00000),
                                    AL::ALValue::array(3, 1.00000, 0.00000));
    times[8][1] = 4.00000;
    keys[8][1] = AL::ALValue::array(-0.312894,
                                    AL::ALValue::array(3, -1.00000, -0.00000),
                                    AL::ALValue::array(3, 0.00000, 0.00000));
    
    names.push_back("LHipYawPitch");
    times[9].arraySetSize(2);
    keys[9].arraySetSize(2);
    
    times[9][0] = 1.00000;
    keys[9][0] = AL::ALValue::array(-0.170000,
                                    AL::ALValue::array(3, -0.333333, -0.00000),
                                    AL::ALValue::array(3, 1.00000, 0.00000));
    times[9][1] = 4.00000;
    keys[9][1] = AL::ALValue::array(-1.03234,
                                    AL::ALValue::array(3, -1.00000, -0.00000),
                                    AL::ALValue::array(3, 0.00000, 0.00000));
    
    names.push_back("LKneePitch");
    times[10].arraySetSize(2);
    keys[10].arraySetSize(2);
    
    times[10][0] = 1.00000;
    keys[10][0] = AL::ALValue::array(-0.0900000,
                                     AL::ALValue::array(3, -0.333333, -0.00000),
                                     AL::ALValue::array(3, 1.00000, 0.00000));
    times[10][1] = 4.00000;
    keys[10][1] = AL::ALValue::array(2.10461,
                                     AL::ALValue::array(3, -1.00000, -0.00000),
                                     AL::ALValue::array(3, 0.00000, 0.00000));
    
    names.push_back("LShoulderPitch");
    times[11].arraySetSize(2);
    keys[11].arraySetSize(2);
    
    times[11][0] = 1.00000;
    keys[11][0] = AL::ALValue::array(1.49930,
                                     AL::ALValue::array(3, -0.333333, -0.00000),
                                     AL::ALValue::array(3, 1.00000, 0.00000));
    times[11][1] = 4.00000;
    keys[11][1] = AL::ALValue::array(0.547595,
                                     AL::ALValue::array(3, -1.00000, -0.00000),
                                     AL::ALValue::array(3, 0.00000, 0.00000));
    
    names.push_back("LShoulderRoll");
    times[12].arraySetSize(2);
    keys[12].arraySetSize(2);
    
    times[12][0] = 1.00000;
    keys[12][0] = AL::ALValue::array(0.151592,
                                     AL::ALValue::array(3, -0.333333, -0.00000),
                                     AL::ALValue::array(3, 1.00000, 0.00000));
    times[12][1] = 4.00000;
    keys[12][1] = AL::ALValue::array(0.457090,
                                     AL::ALValue::array(3, -1.00000, -0.00000),
                                     AL::ALValue::array(3, 0.00000, 0.00000));
    
    names.push_back("LWristYaw");
    times[13].arraySetSize(2);
    keys[13].arraySetSize(2);
    
    times[13][0] = 1.00000;
    keys[13][0] = AL::ALValue::array(-0.0993071,
                                     AL::ALValue::array(3, -0.333333, -0.00000),
                                     AL::ALValue::array(3, 1.00000, 0.00000));
    times[13][1] = 4.00000;
    keys[13][1] = AL::ALValue::array(0.566003,
                                     AL::ALValue::array(3, -1.00000, -0.00000),
                                     AL::ALValue::array(3, 0.00000, 0.00000));
    
    names.push_back("RAnklePitch");
    times[14].arraySetSize(2);
    keys[14].arraySetSize(2);
    
    times[14][0] = 1.00000;
    keys[14][0] = AL::ALValue::array(0.0900000,
                                     AL::ALValue::array(3, -0.333333, -0.00000),
                                     AL::ALValue::array(3, 1.00000, 0.00000));
    times[14][1] = 4.00000;
    keys[14][1] = AL::ALValue::array(0.673468,
                                     AL::ALValue::array(3, -1.00000, -0.00000),
                                     AL::ALValue::array(3, 0.00000, 0.00000));
    
    names.push_back("RAnkleRoll");
    times[15].arraySetSize(2);
    keys[15].arraySetSize(2);
    
    times[15][0] = 1.00000;
    keys[15][0] = AL::ALValue::array(0.130000,
                                     AL::ALValue::array(3, -0.333333, -0.00000),
                                     AL::ALValue::array(3, 1.00000, 0.00000));
    times[15][1] = 4.00000;
    keys[15][1] = AL::ALValue::array(-0.0275701,
                                     AL::ALValue::array(3, -1.00000, -0.00000),
                                     AL::ALValue::array(3, 0.00000, 0.00000));
    
    names.push_back("RElbowRoll");
    times[16].arraySetSize(2);
    keys[16].arraySetSize(2);
    
    times[16][0] = 1.00000;
    keys[16][0] = AL::ALValue::array(0.404681,
                                     AL::ALValue::array(3, -0.333333, -0.00000),
                                     AL::ALValue::array(3, 1.00000, 0.00000));
    times[16][1] = 4.00000;
    keys[16][1] = AL::ALValue::array(0.574213,
                                     AL::ALValue::array(3, -1.00000, -0.00000),
                                     AL::ALValue::array(3, 0.00000, 0.00000));
    
    names.push_back("RElbowYaw");
    times[17].arraySetSize(2);
    keys[17].arraySetSize(2);
    
    times[17][0] = 1.00000;
    keys[17][0] = AL::ALValue::array(1.18597,
                                     AL::ALValue::array(3, -0.333333, -0.00000),
                                     AL::ALValue::array(3, 1.00000, 0.00000));
    times[17][1] = 4.00000;
    keys[17][1] = AL::ALValue::array(0.332836,
                                     AL::ALValue::array(3, -1.00000, -0.00000),
                                     AL::ALValue::array(3, 0.00000, 0.00000));
    
    names.push_back("RHand");
    times[18].arraySetSize(2);
    keys[18].arraySetSize(2);
    
    times[18][0] = 1.00000;
    keys[18][0] = AL::ALValue::array(0.00523599,
                                     AL::ALValue::array(3, -0.333333, -0.00000),
                                     AL::ALValue::array(3, 1.00000, 0.00000));
    times[18][1] = 4.00000;
    keys[18][1] = AL::ALValue::array(0.0144862,
                                     AL::ALValue::array(3, -1.00000, -0.00000),
                                     AL::ALValue::array(3, 0.00000, 0.00000));
    
    names.push_back("RHipPitch");
    times[19].arraySetSize(2);
    keys[19].arraySetSize(2);
    
    times[19][0] = 1.00000;
    keys[19][0] = AL::ALValue::array(0.130000,
                                     AL::ALValue::array(3, -0.333333, -0.00000),
                                     AL::ALValue::array(3, 1.00000, 0.00000));
    times[19][1] = 4.00000;
    keys[19][1] = AL::ALValue::array(-1.23798,
                                     AL::ALValue::array(3, -1.00000, -0.00000),
                                     AL::ALValue::array(3, 0.00000, 0.00000));
    
    names.push_back("RHipRoll");
    times[20].arraySetSize(2);
    keys[20].arraySetSize(2);
    
    times[20][0] = 1.00000;
    keys[20][0] = AL::ALValue::array(-0.100000,
                                     AL::ALValue::array(3, -0.333333, -0.00000),
                                     AL::ALValue::array(3, 1.00000, 0.00000));
    times[20][1] = 4.00000;
    keys[20][1] = AL::ALValue::array(0.357464,
                                     AL::ALValue::array(3, -1.00000, -0.00000),
                                     AL::ALValue::array(3, 0.00000, 0.00000));
    
    names.push_back("RHipYawPitch");
    times[21].arraySetSize(2);
    keys[21].arraySetSize(2);
    
    times[21][0] = 1.00000;
    keys[21][0] = AL::ALValue::array(-0.170000,
                                     AL::ALValue::array(3, -0.333333, -0.00000),
                                     AL::ALValue::array(3, 1.00000, 0.00000));
    times[21][1] = 4.00000;
    keys[21][1] = AL::ALValue::array(-1.03234,
                                     AL::ALValue::array(3, -1.00000, -0.00000),
                                     AL::ALValue::array(3, 0.00000, 0.00000));
    
    names.push_back("RKneePitch");
    times[22].arraySetSize(2);
    keys[22].arraySetSize(2);
    
    times[22][0] = 1.00000;
    keys[22][0] = AL::ALValue::array(-0.0900000,
                                     AL::ALValue::array(3, -0.333333, -0.00000),
                                     AL::ALValue::array(3, 1.00000, 0.00000));
    times[22][1] = 4.00000;
    keys[22][1] = AL::ALValue::array(0.724090,
                                     AL::ALValue::array(3, -1.00000, -0.00000),
                                     AL::ALValue::array(3, 0.00000, 0.00000));
    
    names.push_back("RShoulderPitch");
    times[23].arraySetSize(2);
    keys[23].arraySetSize(2);
    
    times[23][0] = 1.00000;
    keys[23][0] = AL::ALValue::array(1.49941,
                                     AL::ALValue::array(3, -0.333333, -0.00000),
                                     AL::ALValue::array(3, 1.00000, 0.00000));
    times[23][1] = 4.00000;
    keys[23][1] = AL::ALValue::array(2.06996,
                                     AL::ALValue::array(3, -1.00000, -0.00000),
                                     AL::ALValue::array(3, 0.00000, 0.00000));
    
    names.push_back("RShoulderRoll");
    times[24].arraySetSize(2);
    keys[24].arraySetSize(2);
    
    times[24][0] = 1.00000;
    keys[24][0] = AL::ALValue::array(-0.150376,
                                     AL::ALValue::array(3, -0.333333, -0.00000),
                                     AL::ALValue::array(3, 1.00000, 0.00000));
    times[24][1] = 4.00000;
    keys[24][1] = AL::ALValue::array(-0.366519,
                                     AL::ALValue::array(3, -1.00000, -0.00000),
                                     AL::ALValue::array(3, 0.00000, 0.00000));
    
    names.push_back("RWristYaw");
    times[25].arraySetSize(2);
    keys[25].arraySetSize(2);
    
    times[25][0] = 1.00000;
    keys[25][0] = AL::ALValue::array(-0.100588,
                                     AL::ALValue::array(3, -0.333333, -0.00000),
                                     AL::ALValue::array(3, 1.00000, 0.00000));
    times[25][1] = 4.00000;
    keys[25][1] = AL::ALValue::array(-0.378736,
                                     AL::ALValue::array(3, -1.00000, -0.00000),
                                     AL::ALValue::array(3, 0.00000, 0.00000));
    
    
    try
    {
        AL::ALRobotPostureProxy robotPosture(robotIp);
        bool postureReached = robotPosture.goToPosture("Stand", 0.5f);
        if (! postureReached) speech->say("Could not stand");
        
        AL::ALMotionProxy motion(robotIp);
        
        //        const AL::ALValue jointNames = names;
        ////        std:: cout << jointNames << std::endl;
        
        //        /** Make sure the head is stiff to be able to move it.
        //        * To do so, make the stiffness go to the maximum in one second.
        //        */
        //        /** Target stiffness. */
        //        AL::ALValue stiffness = 1.0f;
        //        /** Time (in seconds) to reach the target. */
        //        AL::ALValue time = 1.0f;
        //        /** Call the stiffness interpolation method. */
        //        motion.stiffnessInterpolation(jointNames, stiffness, time);
        motion.openHand("LHand");
        motion.waitUntilMoveIsFinished();
        
        //                motion.openHand("RHand");
        
        //        const AL::ALValue jointName =  AL::ALValue::array("RHand",
//        "LHand");
        //        /** Target stiffness. */
        //        AL::ALValue stiffness = 1.0f;
        //        /** Time (in seconds) to reach the target. */
        //        AL::ALValue time = 1.0f;
        //        /** Call the stiffness interpolation method. */
        //        motion.stiffnessInterpolation(jointName, stiffness, time);
        
        
        
        motion.angleInterpolationBezier(names, times, keys);
        motion.waitUntilMoveIsFinished();
        
        
        //        /** Remove the stiffness on the head. */
        //        stiffness = 0.0f;
        //        time = 1.0f;
        //        motion.stiffnessInterpolation(jointNames, stiffness, time);
        
    }
    catch(const std::exception& e)
    {
        std::cerr << "Caught exception: " << e.what() << std::endl;
        exit(EXIT_FAILURE);
        
    }
#else
    std::cout << "goDown not on linux." << std::endl;
#endif
}

void CustomMoves:: goUp()
{
#ifdef __linux__
    
    // Choregraphe bezier export in c++.
    // Add #include <alproxies/almotionproxy.h> at the beginning of this file.
    std::vector<std::string> names;
    AL::ALValue times, keys;
    names.reserve(26);
    times.arraySetSize(26);
    keys.arraySetSize(26);
    
    names.push_back("HeadPitch");
    times[0].arraySetSize(3);
    keys[0].arraySetSize(3);
    
    times[0][0] = 0.0800000;
    keys[0][0] = AL::ALValue::array(-0.671952,
                                    AL::ALValue::array(3, -0.0266667, -0.00000),
                                    AL::ALValue::array(3, 0.306667, 0.00000));
    times[0][1] = 1.00000;
    keys[0][1] = AL::ALValue::array(-0.671952,
                                    AL::ALValue::array(3, -0.306667, -0.00000),
                                    AL::ALValue::array(3, 1.00000, 0.00000));
    times[0][2] = 4.00000;
    keys[0][2] = AL::ALValue::array(-0.170000,
                                    AL::ALValue::array(3, -1.00000, -0.00000),
                                    AL::ALValue::array(3, 0.00000, 0.00000));
    
    names.push_back("HeadYaw");
    times[1].arraySetSize(3);
    keys[1].arraySetSize(3);
    
    times[1][0] = 0.0800000;
    keys[1][0] = AL::ALValue::array(-0.0153821,
                                    AL::ALValue::array(3, -0.0266667, -0.00000),
                                    AL::ALValue::array(3, 0.306667, 0.00000));
    times[1][1] = 1.00000;
    keys[1][1] = AL::ALValue::array(-0.0153821,
                                    AL::ALValue::array(3, -0.306667, -0.00000),
                                    AL::ALValue::array(3, 1.00000, 0.00000));
    times[1][2] = 4.00000;
    keys[1][2] = AL::ALValue::array(0.00000,
                                    AL::ALValue::array(3, -1.00000, -0.00000),
                                    AL::ALValue::array(3, 0.00000, 0.00000));
    
    names.push_back("LAnklePitch");
    times[2].arraySetSize(3);
    keys[2].arraySetSize(3);
    
    times[2][0] = 0.0800000;
    keys[2][0] = AL::ALValue::array(-0.698011,
                                    AL::ALValue::array(3, -0.0266667, -0.00000),
                                    AL::ALValue::array(3, 0.306667, 0.00000));
    times[2][1] = 1.00000;
    keys[2][1] = AL::ALValue::array(-0.698011,
                                    AL::ALValue::array(3, -0.306667, -0.00000),
                                    AL::ALValue::array(3, 1.00000, 0.00000));
    times[2][2] = 4.00000;
    keys[2][2] = AL::ALValue::array(0.0900000,
                                    AL::ALValue::array(3, -1.00000, -0.00000),
                                    AL::ALValue::array(3, 0.00000, 0.00000));
    
    names.push_back("LAnkleRoll");
    times[3].arraySetSize(3);
    keys[3].arraySetSize(3);
    
    times[3][0] = 0.0800000;
    keys[3][0] = AL::ALValue::array(0.133500,
                                    AL::ALValue::array(3, -0.0266667, -0.00000),
                                    AL::ALValue::array(3, 0.306667, 0.00000));
    times[3][1] = 1.00000;
    keys[3][1] = AL::ALValue::array(0.133500,
                                    AL::ALValue::array(3, -0.306667, -0.00000),
                                    AL::ALValue::array(3, 1.00000, 0.00000));
    times[3][2] = 4.00000;
    keys[3][2] = AL::ALValue::array(-0.130000,
                                    AL::ALValue::array(3, -1.00000, -0.00000),
                                    AL::ALValue::array(3, 0.00000, 0.00000));
    
    names.push_back("LElbowRoll");
    times[4].arraySetSize(3);
    keys[4].arraySetSize(3);
    
    times[4][0] = 0.0800000;
    keys[4][0] = AL::ALValue::array(-0.616627,
                                    AL::ALValue::array(3, -0.0266667, -0.00000),
                                    AL::ALValue::array(3, 0.306667, 0.00000));
    times[4][1] = 1.00000;
    keys[4][1] = AL::ALValue::array(-0.616627,
                                    AL::ALValue::array(3, -0.306667, -0.00000),
                                    AL::ALValue::array(3, 1.00000, 0.00000));
    times[4][2] = 4.00000;
    keys[4][2] = AL::ALValue::array(-0.771435,
                                    AL::ALValue::array(3, -1.00000, -0.00000),
                                    AL::ALValue::array(3, 0.00000, 0.00000));
    
    names.push_back("LElbowYaw");
    times[5].arraySetSize(3);
    keys[5].arraySetSize(3);
    
    times[5][0] = 0.0800000;
    keys[5][0] = AL::ALValue::array(-0.805393,
                                    AL::ALValue::array(3, -0.0266667, -0.00000),
                                    AL::ALValue::array(3, 0.306667, 0.00000));
    times[5][1] = 1.00000;
    keys[5][1] = AL::ALValue::array(-0.805393,
                                    AL::ALValue::array(3, -0.306667, -0.00000),
                                    AL::ALValue::array(3, 1.00000, 0.00000));
    times[5][2] = 4.00000;
    keys[5][2] = AL::ALValue::array(-1.18597,
                                    AL::ALValue::array(3, -1.00000, -0.00000),
                                    AL::ALValue::array(3, 0.00000, 0.00000));
    
    names.push_back("LHand");
    times[6].arraySetSize(3);
    keys[6].arraySetSize(3);
    
    times[6][0] = 0.0800000;
    keys[6][0] = AL::ALValue::array(0.0174533,
                                    AL::ALValue::array(3, -0.0266667, -0.00000),
                                    AL::ALValue::array(3, 0.306667, 0.00000));
    times[6][1] = 1.00000;
    keys[6][1] = AL::ALValue::array(0.00523599,
                                    AL::ALValue::array(3, -0.306667, -0.00000),
                                    AL::ALValue::array(3, 1.00000, 0.00000));
    times[6][2] = 4.00000;
    keys[6][2] = AL::ALValue::array(0.00523599,
                                    AL::ALValue::array(3, -1.00000, -0.00000),
                                    AL::ALValue::array(3, 0.00000, 0.00000));
    
    names.push_back("LHipPitch");
    times[7].arraySetSize(3);
    keys[7].arraySetSize(3);
    
    times[7][0] = 0.0800000;
    keys[7][0] = AL::ALValue::array(-1.33607,
                                    AL::ALValue::array(3, -0.0266667, -0.00000),
                                    AL::ALValue::array(3, 0.306667, 0.00000));
    times[7][1] = 1.00000;
    keys[7][1] = AL::ALValue::array(-1.33607,
                                    AL::ALValue::array(3, -0.306667, -0.00000),
                                    AL::ALValue::array(3, 1.00000, 0.00000));
    times[7][2] = 4.00000;
    keys[7][2] = AL::ALValue::array(0.130000,
                                    AL::ALValue::array(3, -1.00000, -0.00000),
                                    AL::ALValue::array(3, 0.00000, 0.00000));
    
    names.push_back("LHipRoll");
    times[8].arraySetSize(3);
    keys[8].arraySetSize(3);
    
    times[8][0] = 0.0800000;
    keys[8][0] = AL::ALValue::array(-0.312894,
                                    AL::ALValue::array(3, -0.0266667, -0.00000),
                                    AL::ALValue::array(3, 0.306667, 0.00000));
    times[8][1] = 1.00000;
    keys[8][1] = AL::ALValue::array(-0.312894,
                                    AL::ALValue::array(3, -0.306667, -0.00000),
                                    AL::ALValue::array(3, 1.00000, 0.00000));
    times[8][2] = 4.00000;
    keys[8][2] = AL::ALValue::array(0.100000,
                                    AL::ALValue::array(3, -1.00000, -0.00000),
                                    AL::ALValue::array(3, 0.00000, 0.00000));
    
    names.push_back("LHipYawPitch");
    times[9].arraySetSize(3);
    keys[9].arraySetSize(3);
    
    times[9][0] = 0.0800000;
    keys[9][0] = AL::ALValue::array(-1.03234,
                                    AL::ALValue::array(3, -0.0266667, -0.00000),
                                    AL::ALValue::array(3, 0.306667, 0.00000));
    times[9][1] = 1.00000;
    keys[9][1] = AL::ALValue::array(-1.03234,
                                    AL::ALValue::array(3, -0.306667, -0.00000),
                                    AL::ALValue::array(3, 1.00000, 0.00000));
    times[9][2] = 4.00000;
    keys[9][2] = AL::ALValue::array(-0.170000,
                                    AL::ALValue::array(3, -1.00000, -0.00000),
                                    AL::ALValue::array(3, 0.00000, 0.00000));
    
    names.push_back("LKneePitch");
    times[10].arraySetSize(3);
    keys[10].arraySetSize(3);
    
    times[10][0] = 0.0800000;
    keys[10][0] = AL::ALValue::array(2.10461,
                                     AL::ALValue::array(3, -0.0266667, -0.00000),
                                     AL::ALValue::array(3, 0.306667, 0.00000));
    times[10][1] = 1.00000;
    keys[10][1] = AL::ALValue::array(2.10461,
                                     AL::ALValue::array(3, -0.306667, -0.00000),
                                     AL::ALValue::array(3, 1.00000, 0.00000));
    times[10][2] = 4.00000;
    keys[10][2] = AL::ALValue::array(-0.0900000,
                                     AL::ALValue::array(3, -1.00000, -0.00000),
                                     AL::ALValue::array(3, 0.00000, 0.00000));
    
    names.push_back("LShoulderPitch");
    times[11].arraySetSize(3);
    keys[11].arraySetSize(3);
    
    times[11][0] = 0.0800000;
    keys[11][0] = AL::ALValue::array(0.547595,
                                 AL::ALValue::array(3, -0.0266667, -0.00000),
                                     AL::ALValue::array(3, 0.306667, 0.00000));
    times[11][1] = 1.00000;
    keys[11][1] = AL::ALValue::array(0.547595,
                                     AL::ALValue::array(3, -0.306667, -0.00000),
                                     AL::ALValue::array(3, 1.00000, 0.00000));
    times[11][2] = 4.00000;
    keys[11][2] = AL::ALValue::array(1.49941,
                                     AL::ALValue::array(3, -1.00000, -0.00000),
                                     AL::ALValue::array(3, 0.00000, 0.00000));
    
    names.push_back("LShoulderRoll");
    times[12].arraySetSize(3);
    keys[12].arraySetSize(3);
    
    times[12][0] = 0.0800000;
    keys[12][0] = AL::ALValue::array(0.457090,
                                 AL::ALValue::array(3, -0.0266667, -0.00000),
                                     AL::ALValue::array(3, 0.306667, 0.00000));
    times[12][1] = 1.00000;
    keys[12][1] = AL::ALValue::array(0.457090,
                                     AL::ALValue::array(3, -0.306667, -0.00000),
                                     AL::ALValue::array(3, 1.00000, 0.00000));
    times[12][2] = 4.00000;
    keys[12][2] = AL::ALValue::array(0.307178,
                                     AL::ALValue::array(3, -1.00000, -0.00000),
                                     AL::ALValue::array(3, 0.00000, 0.00000));
    
    names.push_back("LWristYaw");
    times[13].arraySetSize(3);
    keys[13].arraySetSize(3);
    
    times[13][0] = 0.0800000;
    keys[13][0] = AL::ALValue::array(0.566003,
                                 AL::ALValue::array(3, -0.0266667, -0.00000),
                                     AL::ALValue::array(3, 0.306667, 0.00000));
    times[13][1] = 1.00000;
    keys[13][1] = AL::ALValue::array(0.566003,
                                     AL::ALValue::array(3, -0.306667, -0.00000),
                                     AL::ALValue::array(3, 1.00000, 0.00000));
    times[13][2] = 4.00000;
    keys[13][2] = AL::ALValue::array(0.100588,
                                     AL::ALValue::array(3, -1.00000, -0.00000),
                                     AL::ALValue::array(3, 0.00000, 0.00000));
    
    names.push_back("RAnklePitch");
    times[14].arraySetSize(3);
    keys[14].arraySetSize(3);
    
    times[14][0] = 0.0800000;
    keys[14][0] = AL::ALValue::array(0.673468,
                                 AL::ALValue::array(3, -0.0266667, -0.00000),
                                     AL::ALValue::array(3, 0.306667, 0.00000));
    times[14][1] = 1.00000;
    keys[14][1] = AL::ALValue::array(0.673468,
                                     AL::ALValue::array(3, -0.306667, -0.00000),
                                     AL::ALValue::array(3, 1.00000, 0.00000));
    times[14][2] = 4.00000;
    keys[14][2] = AL::ALValue::array(0.0900000,
                                     AL::ALValue::array(3, -1.00000, -0.00000),
                                     AL::ALValue::array(3, 0.00000, 0.00000));
    
    names.push_back("RAnkleRoll");
    times[15].arraySetSize(3);
    keys[15].arraySetSize(3);
    
    times[15][0] = 0.0800000;
    keys[15][0] = AL::ALValue::array(-0.0275701,
                                 AL::ALValue::array(3, -0.0266667, -0.00000),
                                     AL::ALValue::array(3, 0.306667, 0.00000));
    times[15][1] = 1.00000;
    keys[15][1] = AL::ALValue::array(-0.0275701,
                                     AL::ALValue::array(3, -0.306667, -0.00000),
                                     AL::ALValue::array(3, 1.00000, 0.00000));
    times[15][2] = 4.00000;
    keys[15][2] = AL::ALValue::array(0.130000,
                                     AL::ALValue::array(3, -1.00000, -0.00000),
                                     AL::ALValue::array(3, 0.00000, 0.00000));
    
    names.push_back("RElbowRoll");
    times[16].arraySetSize(3);
    keys[16].arraySetSize(3);
    
    times[16][0] = 0.0800000;
    keys[16][0] = AL::ALValue::array(0.574213,
                                 AL::ALValue::array(3, -0.0266667, -0.00000),
                                     AL::ALValue::array(3, 0.306667, 0.00000));
    times[16][1] = 1.00000;
    keys[16][1] = AL::ALValue::array(0.574213,
                                     AL::ALValue::array(3, -0.306667, -0.00000),
                                     AL::ALValue::array(3, 1.00000, 0.00000));
    times[16][2] = 4.00000;
    keys[16][2] = AL::ALValue::array(0.404262,
                                     AL::ALValue::array(3, -1.00000, -0.00000),
                                     AL::ALValue::array(3, 0.00000, 0.00000));
    
    names.push_back("RElbowYaw");
    times[17].arraySetSize(3);
    keys[17].arraySetSize(3);
    
    times[17][0] = 0.0800000;
    keys[17][0] = AL::ALValue::array(0.332836,
                                 AL::ALValue::array(3, -0.0266667, -0.00000),
                                     AL::ALValue::array(3, 0.306667, 0.00000));
    times[17][1] = 1.00000;
    keys[17][1] = AL::ALValue::array(0.332836,
                                     AL::ALValue::array(3, -0.306667, -0.00000),
                                     AL::ALValue::array(3, 1.00000, 0.00000));
    times[17][2] = 4.00000;
    keys[17][2] = AL::ALValue::array(1.18636,
                                     AL::ALValue::array(3, -1.00000, -0.00000),
                                     AL::ALValue::array(3, 0.00000, 0.00000));
    
    names.push_back("RHand");
    times[18].arraySetSize(3);
    keys[18].arraySetSize(3);
    
    times[18][0] = 0.0800000;
    keys[18][0] = AL::ALValue::array(0.0144862,
                                 AL::ALValue::array(3, -0.0266667, -0.00000),
                                     AL::ALValue::array(3, 0.306667, 0.00000));
    times[18][1] = 1.00000;
    keys[18][1] = AL::ALValue::array(0.0144862,
                                     AL::ALValue::array(3, -0.306667, -0.00000),
                                     AL::ALValue::array(3, 1.00000, 0.00000));
    times[18][2] = 4.00000;
    keys[18][2] = AL::ALValue::array(0.00523599,
                                     AL::ALValue::array(3, -1.00000, -0.00000),
                                     AL::ALValue::array(3, 0.00000, 0.00000));
    
    names.push_back("RHipPitch");
    times[19].arraySetSize(3);
    keys[19].arraySetSize(3);
    
    times[19][0] = 0.0800000;
    keys[19][0] = AL::ALValue::array(-1.23798,
                                 AL::ALValue::array(3, -0.0266667, -0.00000),
                                     AL::ALValue::array(3, 0.306667, 0.00000));
    times[19][1] = 1.00000;
    keys[19][1] = AL::ALValue::array(-1.23798,
                                     AL::ALValue::array(3, -0.306667, -0.00000),
                                     AL::ALValue::array(3, 1.00000, 0.00000));
    times[19][2] = 4.00000;
    keys[19][2] = AL::ALValue::array(0.130000,
                                     AL::ALValue::array(3, -1.00000, -0.00000),
                                     AL::ALValue::array(3, 0.00000, 0.00000));
    
    names.push_back("RHipRoll");
    times[20].arraySetSize(3);
    keys[20].arraySetSize(3);
    
    times[20][0] = 0.0800000;
    keys[20][0] = AL::ALValue::array(0.357464,
                                 AL::ALValue::array(3, -0.0266667, -0.00000),
                                     AL::ALValue::array(3, 0.306667, 0.00000));
    times[20][1] = 1.00000;
    keys[20][1] = AL::ALValue::array(0.357464,
                                     AL::ALValue::array(3, -0.306667, -0.00000),
                                     AL::ALValue::array(3, 1.00000, 0.00000));
    times[20][2] = 4.00000;
    keys[20][2] = AL::ALValue::array(-0.100000,
                                     AL::ALValue::array(3, -1.00000, -0.00000),
                                     AL::ALValue::array(3, 0.00000, 0.00000));
    
    names.push_back("RHipYawPitch");
    times[21].arraySetSize(3);
    keys[21].arraySetSize(3);
    
    times[21][0] = 0.0800000;
    keys[21][0] = AL::ALValue::array(-1.03234,
                                 AL::ALValue::array(3, -0.0266667, -0.00000),
                                     AL::ALValue::array(3, 0.306667, 0.00000));
    times[21][1] = 1.00000;
    keys[21][1] = AL::ALValue::array(-1.03234,
                                     AL::ALValue::array(3, -0.306667, -0.00000),
                                     AL::ALValue::array(3, 1.00000, 0.00000));
    times[21][2] = 4.00000;
    keys[21][2] = AL::ALValue::array(-0.170000,
                                     AL::ALValue::array(3, -1.00000, -0.00000),
                                     AL::ALValue::array(3, 0.00000, 0.00000));
    
    names.push_back("RKneePitch");
    times[22].arraySetSize(3);
    keys[22].arraySetSize(3);
    
    times[22][0] = 0.0800000;
    keys[22][0] = AL::ALValue::array(0.724090,
                                 AL::ALValue::array(3, -0.0266667, -0.00000),
                                     AL::ALValue::array(3, 0.306667, 0.00000));
    times[22][1] = 1.00000;
    keys[22][1] = AL::ALValue::array(0.724090,
                                     AL::ALValue::array(3, -0.306667, -0.00000),
                                     AL::ALValue::array(3, 1.00000, 0.00000));
    times[22][2] = 4.00000;
    keys[22][2] = AL::ALValue::array(-0.0900000,
                                     AL::ALValue::array(3, -1.00000, -0.00000),
                                     AL::ALValue::array(3, 0.00000, 0.00000));
    
    names.push_back("RShoulderPitch");
    times[23].arraySetSize(3);
    keys[23].arraySetSize(3);
    
    times[23][0] = 0.0800000;
    keys[23][0] = AL::ALValue::array(2.06996,
                                 AL::ALValue::array(3, -0.0266667, -0.00000),
                                     AL::ALValue::array(3, 0.306667, 0.00000));
    times[23][1] = 1.00000;
    keys[23][1] = AL::ALValue::array(2.06996,
                                     AL::ALValue::array(3, -0.306667, -0.00000),
                                     AL::ALValue::array(3, 1.00000, 0.00000));
    times[23][2] = 4.00000;
    keys[23][2] = AL::ALValue::array(1.49930,
                                     AL::ALValue::array(3, -1.00000, -0.00000),
                                     AL::ALValue::array(3, 0.00000, 0.00000));
    
    names.push_back("RShoulderRoll");
    times[24].arraySetSize(3);
    keys[24].arraySetSize(3);
    
    times[24][0] = 0.0800000;
    keys[24][0] = AL::ALValue::array(-0.366519,
                                 AL::ALValue::array(3, -0.0266667, -0.00000),
                                     AL::ALValue::array(3, 0.306667, 0.00000));
    times[24][1] = 1.00000;
    keys[24][1] = AL::ALValue::array(-0.366519,
                                     AL::ALValue::array(3, -0.306667, -0.00000),
                                     AL::ALValue::array(3, 1.00000, 0.00000));
    times[24][2] = 4.00000;
    keys[24][2] = AL::ALValue::array(-0.151592,
                                     AL::ALValue::array(3, -1.00000, -0.00000),
                                     AL::ALValue::array(3, 0.00000, 0.00000));
    
    names.push_back("RWristYaw");
    times[25].arraySetSize(3);
    keys[25].arraySetSize(3);
    
    times[25][0] = 0.0800000;
    keys[25][0] = AL::ALValue::array(-0.378736,
                                 AL::ALValue::array(3, -0.0266667, -0.00000),
                                     AL::ALValue::array(3, 0.306667, 0.00000));
    times[25][1] = 1.00000;
    keys[25][1] = AL::ALValue::array(-0.378736,
                                     AL::ALValue::array(3, -0.306667, -0.00000),
                                     AL::ALValue::array(3, 1.00000, 0.00000));
    times[25][2] = 4.00000;
    keys[25][2] = AL::ALValue::array(0.0993071,
                                     AL::ALValue::array(3, -1.00000, -0.00000),
                                     AL::ALValue::array(3, 0.00000, 0.00000));
    
    
    try
    {
        AL::ALMotionProxy motion(robotIp);
        //        const AL::ALValue jointNames = names;
        ////        std:: cout << jointNames << std::endl;
        
        //        /** Make sure the head is stiff to be able to move it.
        //        * To do so, make the stiffness go to the maximum in one
//        second.
        //        */
        //        /** Target stiffness. */
        ////        AL::ALValue stiffness = 1.0f;
        //        /** Time (in seconds) to reach the target. */
        ////        AL::ALValue time = 1.0f;
        //        /** Call the stiffness interpolation method. */
        ////        motion.stiffnessInterpolation(jointNames, stiffness, time);
        
        motion.closeHand("LHand");
        motion.waitUntilMoveIsFinished();
        //        motion.closeHand("RHand");
        motion.angleInterpolationBezier(names, times, keys);
        motion.waitUntilMoveIsFinished();
        
        /** Target stiffness. */
        //        AL::ALValue stiffness = 0.0f;
        /** Time (in seconds) to reach the target. */
        //        AL::ALValue time = 1.0f;
        /** Call the stiffness interpolation method. */
        //        motion.stiffnessInterpolation(jointNames, stiffness, time);
        
        AL::ALRobotPostureProxy robotPosture(robotIp);
        float maxSpeedFraction = 0.5f; //[0;1]
        bool postureReached = robotPosture.goToPosture("Stand",
                                                       maxSpeedFraction);
        if (! postureReached) speech->say("Could not reach the posture Stand");
    }
    catch(const std::exception& e)
    {
        std::cerr << "Caught exception: " << e.what() << std::endl;
        exit(EXIT_FAILURE);
    }
    
    
#else
    std::cout << "goUp not on linux." << std::endl;
#endif
    
}

void CustomMoves:: riseHandUp()
{
#ifdef __linux__
    
    // Choregraphe bezier export in c++.
    // Add #include <alproxies/almotionproxy.h> at the beginning of this file.
    std::vector<std::string> names;
    AL::ALValue times, keys;
    names.reserve(2);
    times.arraySetSize(2);
    keys.arraySetSize(2);
    
    names.push_back("LShoulderPitch");
    times[0].arraySetSize(2);
    keys[0].arraySetSize(2);
    
    times[0][0] = 0.0400000;
    keys[0][0] = AL::ALValue::array(1.46379,
                                    AL::ALValue::array(3, -0.0133333, -0.00000),
                                    AL::ALValue::array(3, 0.320000, 0.00000));
    times[0][1] = 1.00000;
    keys[0][1] = AL::ALValue::array(0.260054,
                                    AL::ALValue::array(3, -0.320000, -0.00000),
                                    AL::ALValue::array(3, 0.00000, 0.00000));
    
    names.push_back("LShoulderRoll");
    times[1].arraySetSize(2);
    keys[1].arraySetSize(2);
    
    times[1][0] = 0.0400000;
    keys[1][0] = AL::ALValue::array(0.154262,
                                    AL::ALValue::array(3, -0.0133333, -0.00000),
                                    AL::ALValue::array(3, 0.320000, 0.00000));
    times[1][1] = 1.00000;
    keys[1][1] = AL::ALValue::array(0.153589,
                                    AL::ALValue::array(3, -0.320000, -0.00000),
                                    AL::ALValue::array(3, 0.00000, 0.00000));
    
    try
    {
        AL::ALMotionProxy motion(robotIp);
        motion.angleInterpolationBezier(names, times, keys);
        motion.waitUntilMoveIsFinished();
        
        
    }
    catch(const std::exception& e)
    {
        std::cerr << "Caught exception: " << e.what() << std::endl;
        exit(EXIT_FAILURE);
        
    }
#else
    std::cout << "riseHand not on Linux."  << std::endl;
#endif
}

void CustomMoves:: openHandAndMoveItDown()
{
#ifdef __linux__
    
    // Choregraphe bezier export in c++.
    // Add #include <alproxies/almotionproxy.h> at the beginning of this file.
    std::vector<std::string> names;
    AL::ALValue times, keys;
    names.reserve(2);
    times.arraySetSize(2);
    keys.arraySetSize(2);
    
    names.push_back("LShoulderPitch");
    times[0].arraySetSize(2);
    keys[0].arraySetSize(2);
    
    times[0][0] = 0.0400000;
    keys[0][0] = AL::ALValue::array(0.260054,
                                    AL::ALValue::array(3, -0.320000, -0.00000),
                                    AL::ALValue::array(3, 0.00000, 0.00000));
    times[0][1] = 1.00000;
    keys[0][1] = AL::ALValue::array(1.46379,
                                    AL::ALValue::array(3, -0.0133333, -0.00000),
                                    AL::ALValue::array(3, 0.320000, 0.00000));
    
    names.push_back("LShoulderRoll");
    times[1].arraySetSize(2);
    keys[1].arraySetSize(2);
    
    times[1][0] = 0.0400000;
    keys[1][0] = AL::ALValue::array(0.153589,
                                    AL::ALValue::array(3, -0.320000, -0.00000),
                                    AL::ALValue::array(3, 0.00000, 0.00000));
    times[1][1] = 1.00000;
    keys[1][1] = AL::ALValue::array(0.154262,
                                    AL::ALValue::array(3, -0.0133333, -0.00000),
                                    AL::ALValue::array(3, 0.320000, 0.00000));
    
    try
    {
        
        AL::ALMotionProxy motion(robotIp);
        
        motion.openHand("LHand");
        motion.waitUntilMoveIsFinished();
        motion.closeHand("LHand");
        motion.waitUntilMoveIsFinished();
        motion.angleInterpolationBezier(names, times, keys);
        motion.waitUntilMoveIsFinished();
        
        
    }
    catch(const std::exception& e)
    {
        std::cerr << "Caught exception: " << e.what() << std::endl;
        exit(EXIT_FAILURE);
        
    }
#else
    std::cout << "riseHand not on Linux."  << std::endl;
#endif
}



