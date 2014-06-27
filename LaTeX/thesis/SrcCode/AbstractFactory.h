//
//  AbstractFactory.h
//  naoClusteringMac
//
//  Created by Maxim Chetrusca on 4/29/14.
//  Copyright (c) 2014 Maxim Chetrusca. All rights reserved.
//

#ifndef __naoClusteringMac__AbstractFactory__
#define __naoClusteringMac__AbstractFactory__

//#include <iostream>
#include "AbstractImageFetcher.h"
#include "AbstractClusterAlgorithm.h"

const std::string KMEANS_CLUSTERING_ALGORITHM = "kmeans";

//This is a factory for products, the well known design pattern.
class AbstractFactory
{
public:
//Create methods:
//    this image fetcher is based on robot, so it has the necessity of its IP:
//    the first method will decide depending of platform which fetcher to
//    create
    AbstractImageFetcher* createImageFetcher(std::string robotIp);
    AbstractImageFetcher* createRobotImageFetcher(std::string robotIp);
    AbstractImageFetcher* createMacOSXImageFetcher();
    //creates the clustering algorithm given name;
    //if the name is unknown, returns NULL;
    AbstractClusterAlgorithm* createClusteringAlgorithm(
                                    const std::string nameOfAlgorithm);
    
//Constructors:
    AbstractFactory();
    AbstractFactory(const AbstractFactory& factory);
    
//Destructor:
    virtual ~AbstractFactory();

//Overloaded operators:
    AbstractFactory& operator=(const AbstractFactory& factory);
    friend std::ostream& operator<<(std::ostream& stream, const AbstractFactory& factory);

    
    
};

#endif /* defined(__naoClusteringMac__AbstractFactory__) */
