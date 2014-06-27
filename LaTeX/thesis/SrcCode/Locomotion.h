//
//  Locomotion.h
//  naoClusteringMac
//
//  Created by Maxim Chetrusca on 5/16/14.
//  Copyright (c) 2014 Maxim Chetrusca. All rights reserved.
//

#ifndef __naoClusteringMac__Locomotion__
#define __naoClusteringMac__Locomotion__

//#include <iostream>
//#include "Object.h"
#include "SpaceOrientation.h"
#include "CustomMoves.h"

//Robot does some mistakes during movement:
#define USE_CORRECTION 1

const float FORWARD_CORRECTION = (1 - 0.082);
const float LATERAL_CORRECTION_FOR_FORWARD_MOVEMENT = -0.08;
const float LATERAL_CORRECTION = (1 + 0.2);







//This class has the purpose to perform all the movements
//of the body, including looking down, or opening the hand.
class Locomotion
{
public:
    //    Public methods:
    //    Movement involved:
    void setStiffnessOnAndStand();
    void lookDown();
    void move(float x, float y, float theta);
    bool moveObjects(std::vector<Object>& objects,
                     SpaceOrientation& spaceOrientation);
    void walkToObject(Object& object, SpaceOrientation& spaceOrientation);
    float turnToObject(Object& object,  SpaceOrientation& spaceOrientation);
    
    void pickObject(Object& object);
    void giveObjectAndSayResult(Object& object );






    //Constructors:
    Locomotion(const std::string& robotIp, Speech* speech);
    Locomotion(const Locomotion& locomotion);
    
    //Destructor:
    virtual ~Locomotion();
    
    //    Overloaded operators:
    Locomotion& operator=(const Locomotion& locomotion);
    friend std::ostream& operator<<(std::ostream& stream,
                                    const Locomotion& locomotion);
private:
//    Private members:
    std::string robotIp;
    Speech* speech;
    CustomMoves customMoves;
};

#endif /* defined(__naoClusteringMac__Locomotion__) */
