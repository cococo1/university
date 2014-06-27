//
//  Head.h
//  naoClustering
//
//  Created by Maxim Chetrusca on 2/14/14.
//  Copyright (c) 2014 Maxim Chetrusca. All rights reserved.
//

#ifndef __naoClustering__Head__
#define __naoClustering__Head__

#include "AbstractFactory.h"
#include "ObjectDetector.h"
#include "SpaceOrientation.h"
#include "Speech.h"

//This class defines all calculations that NAO does:
//position determination,
//distance calculation,
//angle of turn, etc...
// and also incorporates the speech mechanism and camera.
class Head
{
public:
    Image image;
//    Public methods:
    std::vector<Object>& detectObjects();
    unsigned clusterObjects(std::vector<Object>& objects);
    
//Getters:
    SpaceOrientation& getSpaceOrientation();
    AbstractImageFetcher& getEyes();
    Speech& getSpeech();

//    Setters:
    
//Constructors:
    Head(const std::string& robotIp, AbstractFactory* factory);
    Head(const Head& head);
    
//Destructor:
    virtual ~Head();
    
//    Overloaded operators:
    Head& operator=(const Head& head);
    friend std::ostream& operator<<(std::ostream& stream, const Head& head);

//    Private members:
private:

    AbstractImageFetcher* eyes;
    AbstractFactory* factory;
    std::string robotIp;
    AbstractClusterAlgorithm* clusterAlgorithm;
    ObjectDetector* detector;
    SpaceOrientation spaceOrientation;
    Speech speech;
    
};

#endif /* defined(__naoClustering__Head__) */
