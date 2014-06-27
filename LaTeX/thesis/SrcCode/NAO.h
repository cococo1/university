//
//  NAO.h
//  naoClustering
//
//  Created by Maxim Chetrusca on 2/18/14.
//  Copyright (c) 2014 Maxim Chetrusca. All rights reserved.
//

#ifndef __naoClustering__NAO__
#define __naoClustering__NAO__

#include <iostream>
#include "Head.h"
#include "Locomotion.h"

//#ifdef __linux__
//    #include <alproxies/alrobotpostureproxy.h>
//    #include <alproxies/alnavigationproxy.h>
//    #include <alproxies/almotionproxy.h>
//#endif

//This class unifies all of the others, and provides a unique point of
//access of all functionality with which this project deals.
class NAO
{
public:
//    Public methods:
    void startInteraction();
    void executeCommand(std::string command);
    
//Getters:
    std::string getRobotIp();
    Head& getHead();
    Locomotion& getLocomotion();

//Setters:
    

//Constructors:
    NAO(const std::string& robotIp, AbstractFactory* factory);
    NAO(const NAO& nao);
    
//Destructor:
    virtual ~NAO();
    
//    Overloaded operators:
    NAO& operator=(const NAO& nao);
    friend std::ostream& operator<<(std::ostream& stream, const NAO& nao);
    
//    Private members:
private:
    std::string receiveCommands();

    Head* head;
    Locomotion locomotion;
    std::string robotIp;
};


#endif /* defined(__naoClustering__NAO__) */
