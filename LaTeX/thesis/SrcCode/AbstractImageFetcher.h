//
//  AbstractImageFetcher.h
//  naoClustering
//
//  Created by Maxim Chetrusca on 2/14/14.
//  Copyright (c) 2014 Maxim Chetrusca. All rights reserved.
//

#ifndef __naoClustering__AbstractImageFetcher__
#define __naoClustering__AbstractImageFetcher__

#include "Image.h"

//Abstract class that defines an object which might produce an image:
class AbstractImageFetcher
{
public:
//Getters:
    virtual Image& getImage() = 0;
    
//Constructors:
    AbstractImageFetcher();
    AbstractImageFetcher(const AbstractImageFetcher& imageFetcher);
    
//Destructor:
    virtual ~AbstractImageFetcher();
    
//Overloaded operators:
    AbstractImageFetcher& operator=(const AbstractImageFetcher& imageFetcher);
    friend std::ostream& operator<<(std::ostream& stream,
                                    const AbstractImageFetcher& imageFetcher);
};

#endif /* defined(__naoClustering__AbstractImageFetcher__) */
