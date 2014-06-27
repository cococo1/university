//
//  NAO.cpp
//  naoClustering
//
//  Created by Maxim Chetrusca on 2/18/14.
//  Copyright (c) 2014 Maxim Chetrusca. All rights reserved.
//

#include "NAO.h"
#include "Image.h"
#include <unistd.h> //for sleep on MacOS
#include "opencv2/opencv.hpp"

//    Public methods:
void NAO:: startInteraction()
{
    std::string command;
    // 1. Localize speaker;

//    std::vector<float> position =
//    head->getSpeech().localizeSoundSource();
    // move head to the position;

    // 2. Receive commands;

    //turn back the head;
    // 3. Perform the job.
    while (1)
    {
        command = receiveCommands();
        if (! command.compare("stop")) break;
        else
        {
            executeCommand(command);
        }
    }
}

void NAO::  executeCommand(std::string command)
{
    if (! command.compare("hi"))
    {
        head->getSpeech().say("Hello!");
    }
    else if (! command.compare("bye"))
    {
        head->getSpeech().say("Bye-bye!");
    }
    else if (! command.compare("cluster objects"))
    {
        //!!! Very important to call this method:
        locomotion.setStiffnessOnAndStand();
        locomotion.lookDown();
//        head->getSpaceOrientation().getBottomCameraPosition();
        std::vector<Object> objects = this->head->detectObjects();

        ///Start of change:
        int n = this->head->clusterObjects(objects  );
        
        
        cv::Mat image = this->head->image.getMatrix();
        for (int i = 0; i < n; i++)
        {
            cv::Scalar color =
            cvScalar(rand() % 255,
                     rand() % 255,
                     rand() % 255 );
            for( int j = 0; j< objects.size(); j++ )
            {
                if (objects[j].getGroup() == i)
                {
                    rectangle( image,
                              objects[j].getImage().getBoundingRect().tl(),
                              objects[j].getImage().getBoundingRect().br(),
                              color,
                              5,
                              8,
                              0 );
                }
            }
            
            
  
        }
        
        
        
        
        

        if (SHOW_IMAGES)
        {
        cv::imshow( "Image", image);
            cv::waitKey();
            cv::destroyWindow("Image");
        //End of change.
        }

        head->getSpaceOrientation().initializePosition();
//        head->getSpaceOrientation().getBottomCameraPosition();
//            AL::ALMotionProxy motion(robotIp);
//            motion.moveTo(0, 0, M_PI/6);



        this->locomotion.moveObjects(objects, head->getSpaceOrientation());
    }
    else
    {
        head->getSpeech().say("I did not understand this word");
    }
}

//Getters:
std::string NAO:: getRobotIp()
{
    return robotIp;
}

Head& NAO:: getHead()
{
    return *head;
}

Locomotion& NAO:: getLocomotion()
{
    return locomotion;
}

//Setters:


//Constructors:
NAO:: NAO(const std::string& robotIp, AbstractFactory* factory):
head(new Head(robotIp, factory)),
robotIp(robotIp),
locomotion(robotIp, &head->getSpeech())
{
    
}

NAO:: NAO(const NAO& nao):
head(new Head(*nao.head)),
robotIp(nao.robotIp),
locomotion(nao.locomotion)
{
    
}

//Destructor:
NAO:: ~NAO()
{
    delete head;
}

//    Overloaded operators:
NAO& NAO:: operator=(const NAO& nao)
{
    if (this != &nao)
    {
        delete head;
        
        head = new Head(*nao.head);
        robotIp = nao.robotIp;
        locomotion = nao.locomotion;
    }
    return *this;
}

std::ostream& operator<<(std::ostream& stream, const NAO& nao)
{
    stream << *nao.head << " " << nao.locomotion << " " << nao.robotIp
    << std::endl;
    return stream;
}

//    Private members:
std::string NAO:: receiveCommands()
{
    static int k = 0;
    k++;
    if (k == 1) return "cluster objects";
    else return "stop";
    //    return head->recognizeSpeech();
}




