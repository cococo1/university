//
//  AbstractFactory.cpp
//  naoClusteringMac
//
//  Created by Maxim Chetrusca on 4/29/14.
//  Copyright (c) 2014 Maxim Chetrusca. All rights reserved.
//

#include "AbstractFactory.h"
#include "Camera.h"
#include "ImageFetcherOnOSX.h"
#include "KMeansClusteringAlgorithm.h"

//Create methods:
AbstractImageFetcher* AbstractFactory:: createImageFetcher(std::string robotIp)
{
#ifdef __linux__
    return createRobotImageFetcher(robotIp);
#else
    return createMacOSXImageFetcher();
#endif
}

AbstractImageFetcher* AbstractFactory:: createRobotImageFetcher(std::string robotIp)
{
    //On robot, Camera class is the image fetcher:
    return new Camera(robotIp);
}

AbstractImageFetcher* AbstractFactory:: createMacOSXImageFetcher()
{
    return new ImageFetcherOnOSX();
}

AbstractClusterAlgorithm* AbstractFactory:: createClusteringAlgorithm(
                                            const std::string nameOfAlgorithm)
{
    if (! nameOfAlgorithm.compare(KMEANS_CLUSTERING_ALGORITHM))
    {
        KMeansClusteringAlgorithm* alg = new KMeansClusteringAlgorithm();
        alg->setName(nameOfAlgorithm);
        return alg;
    }
    else return NULL;
}

//Constructors:
AbstractFactory:: AbstractFactory()
{
    
}

AbstractFactory:: AbstractFactory(const AbstractFactory& factory)
{
    
}

//Destructor:
AbstractFactory::  ~AbstractFactory()
{
    
}

//Overloaded operators:
AbstractFactory& AbstractFactory:: operator=(const AbstractFactory& factory)
{
    if (this != &factory)
    {
        
    }
    return *this;
}

std::ostream& operator<<(std::ostream& stream, const AbstractFactory& factory)
{
    stream << "This is factory: " << factory << std::endl;
    return  stream;
}