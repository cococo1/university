//
//  Head.cpp
//  naoClustering
//
//  Created by Maxim Chetrusca on 2/14/14.
//  Copyright (c) 2014 Maxim Chetrusca. All rights reserved.
//

#include "Head.h"
#include "opencv2/opencv.hpp"

//    Public methods:
std::vector<Object>& Head:: detectObjects()
{
    //NAO takes first shot
    //    say("Let me see the background");
    //    std::cout << "Let me see the background" << std::endl;
//    lookDown(robotIp);//head->getCamera().getRobotIp());
    Image& background = eyes->getImage();
    speech.say("Ok, I saw the background. Now let me see the objects.");
    //    std::cout << "Now, the objects" << std::endl;
    
    //Do some things ...
//    sleep(10);
    cv::imshow( "Image", background.getMatrix() );
    cv::waitKey();
    cv::destroyWindow("Image");

    Image& image =  eyes->getImage();
    this->image = image;
    speech.say("Done");
    
    //    std::cout << "Done" << std::endl;
    return detector->detectObjectsFromImage(image, background);
}

unsigned Head:: clusterObjects(std::vector<Object>& objects)
{
    
    return clusterAlgorithm->assignGroupsToObjects(objects);
}

//Getters:
SpaceOrientation& Head:: getSpaceOrientation()
{
    return spaceOrientation;
}

AbstractImageFetcher& Head:: getEyes()
{
    return *eyes;
}

Speech& Head:: getSpeech()
{
    return speech;
}

//    Setters:


//Constructors:
Head:: Head(const std::string& robotIp, AbstractFactory* factory):
factory(factory),
robotIp(robotIp),
eyes(factory->createImageFetcher(robotIp)),
detector(new ObjectDetector()),
spaceOrientation(robotIp),
speech(robotIp),
image(cv::Mat())
{
    clusterAlgorithm =
    factory->createClusteringAlgorithm(KMEANS_CLUSTERING_ALGORITHM);

}

Head:: Head(const Head& head):
factory(head.factory),
robotIp(head.robotIp),
eyes(head.factory->createImageFetcher(head.robotIp)),
detector(new ObjectDetector(*head.detector)),
spaceOrientation(head.spaceOrientation),
speech(head.robotIp),
image(head.image)
{
        clusterAlgorithm =
    factory->createClusteringAlgorithm(head.clusterAlgorithm->getName());
}

//Destructor:
Head:: ~Head()
{
    delete eyes;
    delete clusterAlgorithm;
    delete detector;

}

//    Overloaded operators:
Head& Head:: operator=(const Head& head)
{
    if (this != &head)
    {
        delete eyes;
        delete clusterAlgorithm;
        delete detector;

        factory = head.factory;
        eyes = factory->createImageFetcher(head.robotIp);
        robotIp = head.robotIp;
        clusterAlgorithm =
        factory->createClusteringAlgorithm(head.clusterAlgorithm->getName());
        detector = new ObjectDetector(*head.detector);
        spaceOrientation = head.spaceOrientation;
        speech = head.speech;
        
    }
    
    return *this;
}

std::ostream& operator<<(std::ostream& stream, const Head& head)
{
    stream << *head.eyes << " " << head.factory << " " << head.robotIp <<
    " " << *head.clusterAlgorithm << " " << *head.detector << " " <<
    head.speech << std::endl;
    
    return stream;
}

//    Private members:


