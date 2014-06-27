//
//  Job.cpp
//  TaskScheduller1.0
//
//  Created by Maxim Chetrusca on 11/8/13.
//  Copyright (c) 2013 Maxim Chetrusca. All rights reserved.
//

#include "Job.h"

 unsigned Job::lowerBound = 0;
unsigned Job::upperBound = INFINITY;//numeric_limits<int>::max();
unsigned Job::size = 0;
unsigned Job::totalNumberOfTasks = 0;


Job:: Job():
currentPenalization(0),
currentTime(0),
parentID(0),
arrayOfTasks(new unsigned[Job::totalNumberOfTasks])
{
    for (int i = 0; i < Job::totalNumberOfTasks; i++)
    {
        arrayOfTasks[i] = 0;
    }
//    cout << "Job()" << endl;

    
}

Job:: Job(list<Task*> tasks,short unsigned time, short unsigned penalization, unsigned short ID):
listOfTasks(tasks),
currentPenalization(penalization),
currentTime(time),
parentID(ID),
arrayOfTasks(new unsigned[Job::totalNumberOfTasks])
{
    for (int i = 0; i < Job::totalNumberOfTasks; i++)
    {
        arrayOfTasks[i] = 0;
    }
//    cout << "Job:: Job(list<Task*> tasks):" << endl;
}

Job:: Job(const Job& job):
currentPenalization(job.currentPenalization),
currentTime(job.currentTime),
parentID(job.parentID),
arrayOfTasks(new unsigned[Job::totalNumberOfTasks])
{
//    cout << "Job(copy)" << endl;

    
    list<Task*> aList = job.listOfTasks;
    list<Task*>::iterator listIterator = aList.begin(), end = aList.end();
    for (; listIterator != end; listIterator++)
    {
        listOfTasks.push_back(*listIterator);
    }
    
    for (int i = 0; i < Job::totalNumberOfTasks; i++)
    {
        arrayOfTasks[i] = job.arrayOfTasks[i];
    }
}

Job:: Job(char* buffer)
{
//    cout << "Job(buffer)" << endl;

    if (USE_MPI)
    {
        //transform this into a "job"
        int position = 0;
        unsigned length = Job::size*4*sizeof(unsigned) + 2*sizeof(unsigned) +2*sizeof(unsigned) +sizeof(unsigned) + Job::totalNumberOfTasks*sizeof(unsigned);
        unsigned short arrayLength = Job::size*4*sizeof(unsigned); //length - 2*sizeof(unsigned) -2*sizeof(unsigned) - Job::totalNumberOfTasks*si;
        unsigned tasksData[arrayLength/sizeof(unsigned)];
        unsigned short numberOfTasks = Job::size;//arrayLength/sizeof(unsigned)/4;
//        cout << "Decoding: Buffer length: " << length << "Number of tasks: " << numberOfTasks << endl;
        MPI_Unpack(buffer, length, &position, tasksData, numberOfTasks*4, MPI_UNSIGNED, MPI_COMM_WORLD);
        MPI_Unpack(buffer, length, &position, &currentTime, 1, MPI_UNSIGNED, MPI_COMM_WORLD);
        MPI_Unpack(buffer, length, &position, &currentPenalization, 1, MPI_UNSIGNED, MPI_COMM_WORLD);
        MPI_Unpack(buffer, length, &position, &Job::lowerBound, 1, MPI_UNSIGNED, MPI_COMM_WORLD);
        MPI_Unpack(buffer, length, &position, &Job::upperBound, 1, MPI_UNSIGNED, MPI_COMM_WORLD);
        MPI_Unpack(buffer, length, &position, &parentID, 1, MPI_UNSIGNED, MPI_COMM_WORLD);
        arrayOfTasks = new unsigned[Job::totalNumberOfTasks];
        for (int i = 0; i < Job::totalNumberOfTasks; i++)
        {
            arrayOfTasks[i] = 0;
        }
        MPI_Unpack(buffer, length, &position, arrayOfTasks, Job::totalNumberOfTasks, MPI_UNSIGNED, MPI_COMM_WORLD);

        
        short j  = 0;
        for (short i = 0; i < numberOfTasks; i++)
        {
            unsigned short t,d,z,id;
            id = tasksData[j];
            t = tasksData[j+1];
            d = tasksData[j+2];
            z = tasksData[j+3];
            
            Task* task = new Task(t,d,z,id);
            listOfTasks.push_back(task);
            

            j += 4;
        }
        
//        printJob();
        
    }
}

Job:: ~Job()
{
//    cout << "~Job()" << endl;
    delete []arrayOfTasks;
    
}

Job Job:: operator=(const Job &job)
{
    if (this != &job)
    {
        delete []arrayOfTasks;

        
        list<Task*> aList = job.listOfTasks;
        arrayOfTasks = new unsigned[Job::totalNumberOfTasks];
        list<Task*>::iterator listIterator = aList.begin(), end = aList.end();
        for (; listIterator != end; listIterator++)
        {
            listOfTasks.push_back(*listIterator);
        }
        currentTime = job.currentTime;
        currentPenalization = job.currentPenalization;
        parentID = job.parentID;
        
        for (int i = 0; i < Job::totalNumberOfTasks; i++)
        {
            arrayOfTasks[i] = job.arrayOfTasks[i];
        }
    }
    
    return *this;
}

char* Job:: toBuffer()
{
    // transform this into some MPI_PACK
    unsigned tasksData[size*4];
    
    list<Task*>::iterator listIterator = listOfTasks.begin(), end = listOfTasks.end();
    short i = 0;
    for (; listIterator != end; listIterator++)
    {
        tasksData[i] = (*listIterator)->ID();
        tasksData[i+1] = (*listIterator)->t();
        tasksData[i+2] = (*listIterator)->d();
        tasksData[i+3] = (*listIterator)->z();
        i += 4;
    }
    unsigned length = Job::size*4*sizeof(unsigned) + 2*sizeof(unsigned) +2*sizeof(unsigned) + sizeof(unsigned) + Job::totalNumberOfTasks*sizeof(unsigned);
//    cout << "Encoding: Number of tasks: " << Job::size << "buffer length: " << length << endl;
    char *message = new char[length];
    int position = 0;
    if (USE_MPI)
    {
        MPI_Pack(tasksData, size*4, MPI_UNSIGNED, message, length, &position, MPI_COMM_WORLD);
//        cout << "tasksData encoded" << endl;
        MPI_Pack(&currentTime, 1, MPI_UNSIGNED, message, length, &position, MPI_COMM_WORLD);
//        cout << "currentTime" << endl;
        MPI_Pack(&currentPenalization, 1, MPI_UNSIGNED, message, length, &position, MPI_COMM_WORLD);
//        cout << "currentPenalization" << endl;
        unsigned lb = Job::lowerBound;
        unsigned ub = Job::upperBound;
        MPI_Pack(&lb, 1, MPI_UNSIGNED, message, length, &position, MPI_COMM_WORLD);
//        cout << "lowerBound" << endl;
        MPI_Pack(&ub, 1, MPI_UNSIGNED, message, length, &position, MPI_COMM_WORLD);
        MPI_Pack(&parentID, 1, MPI_UNSIGNED, message, length, &position, MPI_COMM_WORLD);
//        cout << "Totoal numbrer of tasks at packing " << Job::totalNumberOfTasks << endl;
        MPI_Pack(arrayOfTasks, Job::totalNumberOfTasks, MPI_UNSIGNED, message, length, &position, MPI_COMM_WORLD);

    

//        printJob();

    }
    
    
    
    
#pragma mark Do we need to return position as well? or may be size?
    return message;
}

//void Job:: printJob()
//{
//    list<Task*>::iterator listIterator = listOfTasks.begin(), end = listOfTasks.end();
//    for (; listIterator != end; listIterator++)
//    {
//        cout << (*listIterator)->ID() <<" " << (*listIterator)->t() << " " << (*listIterator)->d() << " " << (*listIterator)->z() <<" current time: " << currentTime << " current penalization: " << currentPenalization << " lower bound: " << Job::lowerBound << " upper bound: " << Job::upperBound << " parent id: " << parentID << endl;
//    }
//    
//    cout << "ArrayOfTasks " << endl;
//    for (int i = 0; i< Job::totalNumberOfTasks; i++)
//    {
//        cout << arrayOfTasks[i] << " " << endl;
//    }
//    
//}

list<Task*> Job:: getListOfTasks()
{
    return listOfTasks;
}

void Job:: setArrayOfTasks(unsigned* newArrayOfTasks)
{
    delete []arrayOfTasks;
    arrayOfTasks = newArrayOfTasks;
}


