//
//  Object.cpp
//  naoClustering
//
//  Created by Maxim Chetrusca on 2/13/14.
//  Copyright (c) 2014 Maxim Chetrusca. All rights reserved.
//

#include "Object.h"

//Getters:
int Object:: getGroup()
{
    return group;
}

bool Object:: isGrouped()
{
    return grouped;
}

Image Object:: getImage()
{
    return *image;
}

//Setters:
void Object:: setGroup(int group)
{
    this->group = group;
    //an object becomes grouped as soon as it receives a group
    this->grouped = true;
}

void Object:: setPositionInRobotFrame(cv::Point2d point)
{
    positionInRobotFrame = point;
}
cv::Point2d Object:: getPositionInRobotFrame()
{
    return positionInRobotFrame;
}

//Constructors:
Object:: Object(const Image image):
image(new Image(image)),
grouped(false),
group(-1),
positionInRobotFrame(cv::Point2d(-1, -1))
{
    
}

Object:: Object(const Object& object):
image(new Image(*object.image)),
grouped(object.grouped),
group(object.group),
positionInRobotFrame(object.positionInRobotFrame)
{
    
}

//Destructors:
Object:: ~Object()
{
    delete image;
}

//Overloaded operators:
Object& Object:: operator=(const Object& object)
{
    if (this != &object)
    {
        delete image;
        
        image = new Image(*object.image);
        grouped = object.grouped;
        group = object.group;
        positionInRobotFrame = object.positionInRobotFrame;
    }
    return *this;
}

std::ostream& operator<<(std::ostream& stream, const Object& object)
{
    stream << *object.image << object.grouped << object.group << std::endl;
    return stream;
}

