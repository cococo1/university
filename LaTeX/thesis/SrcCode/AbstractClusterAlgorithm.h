//
//  AbstractClusterAlgorithm.h
//  naoClusteringMac
//
//  Created by Maxim Chetrusca on 5/15/14.
//  Copyright (c) 2014 Maxim Chetrusca. All rights reserved.
//

#ifndef __naoClusteringMac__ClusterAlgorithm__
#define __naoClusteringMac__ClusterAlgorithm__

#include "Object.h"

//This is an abstract class which defines a common behaviour for any
//clustering algorithm
class AbstractClusterAlgorithm
{
public:
//    Public methods:
//    any clustering algorithm should be able to label a vector of objects:
    virtual unsigned assignGroupsToObjects(std::vector<Object>& objects) = 0;
    
//Getters:
    //an algorithm is identified by its name:
    std::string getName();
    
//Setters:
    void setName(std::string name);
    
    //Constructors:
    AbstractClusterAlgorithm();
    AbstractClusterAlgorithm(const AbstractClusterAlgorithm& algorithm);
    
    //Destructor:
    virtual ~AbstractClusterAlgorithm();
    
    //Overloaded operators:
    AbstractClusterAlgorithm& operator=(const AbstractClusterAlgorithm& algorithm);
    friend std::ostream& operator<<(std::ostream& stream,
                                    const AbstractClusterAlgorithm& algorithm);

//    Private members:
private:
    std::string name;
    
};

#endif /* defined(__naoClusteringMac__ClusterAlgorithm__) */
