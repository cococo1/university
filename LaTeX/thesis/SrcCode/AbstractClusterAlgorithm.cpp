//
//  AbstractClusterAlgorithm.cpp
//  naoClusteringMac
//
//  Created by Maxim Chetrusca on 5/15/14.
//  Copyright (c) 2014 Maxim Chetrusca. All rights reserved.
//

#include "AbstractClusterAlgorithm.h"
//Getters:
//an algorithm is identified by its name:
std::string AbstractClusterAlgorithm:: getName()
{
    return name;
}

//Setters:
void AbstractClusterAlgorithm:: setName(std::string name)
{
    this->name = name;
}

//Constructors:
AbstractClusterAlgorithm:: AbstractClusterAlgorithm():
name("unknown")
{
    
}

AbstractClusterAlgorithm:: AbstractClusterAlgorithm
(const AbstractClusterAlgorithm& algorithm):
name(algorithm.name)
{
    
}

//Destructor:
AbstractClusterAlgorithm:: ~AbstractClusterAlgorithm()
{
    
}

//Overloaded operators:
AbstractClusterAlgorithm& AbstractClusterAlgorithm::
operator=(const AbstractClusterAlgorithm& algorithm)
{
    if (this != &algorithm)
    {
        name = algorithm.name;
    }
    
    return *this;
}

std::ostream& operator<<(std::ostream& stream,
                         const AbstractClusterAlgorithm& algorithm)
{
    stream << algorithm.name << std::endl;
    return stream;
}