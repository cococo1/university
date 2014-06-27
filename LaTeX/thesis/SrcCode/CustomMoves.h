//
//  CustomMoves.h
//  naoClusteringMac
//
//  Created by Maxim Chetrusca on 5/16/14.
//  Copyright (c) 2014 Maxim Chetrusca. All rights reserved.
//

#ifndef __naoClusteringMac__CustomMoves__
#define __naoClusteringMac__CustomMoves__

#include <iostream>
#include "Speech.h"


#ifdef __linux__
#include <alproxies/alrobotpostureproxy.h>
#include <alproxies/alnavigationproxy.h>
#include <alproxies/almotionproxy.h>
#endif

//This class implements some moves exported from Choreographe;
class CustomMoves
{
public:
//    Public methods:
    void goDown();
    void goUp();
    void riseHandUp();
    void openHandAndMoveItDown();

    //Constructors:
    CustomMoves(const std::string& robotIp, Speech* speech);
    CustomMoves(const CustomMoves& customMove);
    
    //Destructor:
    virtual ~CustomMoves();
    
    //    Overloaded operators:
    CustomMoves& operator=(const CustomMoves& customMove);
    friend std::ostream& operator<<(std::ostream& stream,
                                    const CustomMoves& customMove);
    
private:

    //    Private members:
    std::string robotIp;
    Speech* speech;
};

#endif /* defined(__naoClusteringMac__CustomMoves__) */
