//
//  Job.h
//  TaskScheduller1.0
//
//  Created by Maxim Chetrusca on 11/8/13.
//  Copyright (c) 2013 Maxim Chetrusca. All rights reserved.
//

#ifndef __TaskScheduller1_0__Job__
#define __TaskScheduller1_0__Job__

//#include <iostream>
#include "Task.h"
#include <list>
#include "mpi.h"
#include <limits>


#define USE_MPI 0

#define INFINITY numeric_limits<int>::max()

#define DESTINATION_MASTER 0
#define TAG_SEND_INITIAL_TASKS 0
//#define TAG_IS_JOB 1
#define TAG_JOB 2
#define TAG_POSSIBLE_SOLUTION 3
#define TAG_STOP 4



using namespace std;

class Job
{
public:
    static unsigned lowerBound;
    static unsigned upperBound;
    static unsigned size;
    static unsigned totalNumberOfTasks; 
    
public:
    
    Job();
    Job(list<Task*> tasks,short unsigned time, short unsigned penalization, unsigned short ID);
    Job(const Job& job);
    Job(char* buffer);
    virtual ~Job();
//    void printJob();
    void setArrayOfTasks(unsigned* newArrayOfTasks);
    unsigned* getArrayOfTasks() { return arrayOfTasks; }
    
    
    
    Job operator=(const Job &job);
    
    char* toBuffer();
    
    void setCurrentTime(short unsigned time) { currentTime = time; }
    void setCurrentPenalization(short unsigned penalization) { currentPenalization = penalization; }
    short unsigned getCurrentTime() { return currentTime; }
    short unsigned getCurrentPenalization() { return currentPenalization; }
    list<Task*> getListOfTasks();
    
    
private:
    list<Task*> listOfTasks;
    short unsigned currentTime;
    short unsigned currentPenalization;
    short unsigned parentID;
    unsigned *arrayOfTasks;

    
    
};

#endif /* defined(__TaskScheduller1_0__Job__) */
