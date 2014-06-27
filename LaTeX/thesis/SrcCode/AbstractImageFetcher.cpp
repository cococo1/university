//
//  AbstractImageFetcher.cpp
//  naoClustering
//
//  Created by Maxim Chetrusca on 2/14/14.
//  Copyright (c) 2014 Maxim Chetrusca. All rights reserved.
//

#include "AbstractImageFetcher.h"


//Constructors:
AbstractImageFetcher:: AbstractImageFetcher()
{
    
}

AbstractImageFetcher:: AbstractImageFetcher
(const AbstractImageFetcher& imageFetcher)
{
    
}

//Destructor:
AbstractImageFetcher:: ~AbstractImageFetcher()
{
    
}

//Overloaded operators:
AbstractImageFetcher& AbstractImageFetcher::
operator=(const AbstractImageFetcher& imageFetcher)
{
    if (this != &imageFetcher)
    {
        
    }
    
    return *this;
}

std::ostream& operator<<(std::ostream& stream,
                         const AbstractImageFetcher& imageFetcher)
{
    return stream;
}