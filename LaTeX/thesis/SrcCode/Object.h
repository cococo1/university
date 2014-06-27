//
//  Object.h
//  naoClustering
//
//  Created by Maxim Chetrusca on 2/13/14.
//  Copyright (c) 2014 Maxim Chetrusca. All rights reserved.
//

#ifndef __naoClustering__MovableObject__
#define __naoClustering__MovableObject__

#include "Image.h"

//Class which identifies an object by its image, position relative to robot
//and group
class Object
{
public:
//Getters:
    //an object might be clustered or not:
    int getGroup();
    bool isGrouped();
    //gets the position of object relative to the initial position of robot
    cv::Point2d getPositionInRobotFrame();
    Image getImage();

//Setters:
    void setGroup(int group);
    void setPositionInRobotFrame(cv::Point2d point);

//Constructors:
    //an object is represented by an image;
    // group and position by default are initialized to negative values,
    //thus they need to be setted manually
    Object(const Image image);
    Object(const Object& object);

//Destructor:
    virtual ~Object();

//Overloaded operators:
    Object& operator=(const Object& object);
    friend std::ostream& operator<<(std::ostream& stream, const Object& object);

//Member variables:
private:
    Image* image;
    bool grouped;
    int group;
    cv::Point2d positionInRobotFrame;
    
};

#endif /* defined(__naoClustering__MovableObject__) */
