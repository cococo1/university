//
//  Task.h
//  TaskScheduller1.0
//
//  Created by Maxim Chetrusca on 10/8/13.
//  Copyright (c) 2013 Maxim Chetrusca. All rights reserved.
//

#ifndef __TaskScheduller1_0__Task__
#define __TaskScheduller1_0__Task__

//#include <iostream>

class Task
{
public:
    Task();
    Task(unsigned short t, unsigned short d, unsigned short z, unsigned short ID);
    Task(const Task& task);
    virtual ~Task();
    
    Task& operator= (const Task& task);

    
#pragma mark setters & getters:
    unsigned short t() const;
    unsigned short d() const;
    unsigned short z() const;
    unsigned short ID() const;

    void setT(unsigned short t);
    void setD(unsigned short d);
    void setZ(unsigned short z);
    void setID(unsigned short ID);

private:
    unsigned short _t; //running time
    unsigned short _d; //maximum allowed time
    unsigned short _z; //penalization
    unsigned short _ID;

};


#endif /* defined(__TaskScheduller1_0__Task__) */
