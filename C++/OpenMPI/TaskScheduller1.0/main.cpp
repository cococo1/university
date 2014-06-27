//
//  main.cpp
//  TaskScheduller1.0
//
//  Created by Maxim Chetrusca on 10/8/13.
//  Copyright (c) 2013 Maxim Chetrusca. All rights reserved.
//

#pragma mark TODO: How to maximize the lower bound???

#include <iostream>
#include <iomanip> // for setw()
#include <stdlib.h>

#include <time.h>

#include "TaskScheduller.h"
#include "Task.h"

#include "mpi.h"

#include <ctime>

#define LENGTH 100

#define NUMBER_OF_TASKS 4



using namespace std;


Task* generateNTasks(unsigned n);
void printTasks(Task *tasks, int numberOfTasks);

void useMPI(int argc, char *argv[]);
void useSequentialAlgorithm(int argc, char *argv[]);

void executeSlaveWork(unsigned short processorRank, unsigned short numberOfProcessors, int argc, char** argv);
void executeMasterWork(unsigned short processorRank, unsigned short numberOfProcessors, int argc, char** argv);
void sendTasksToSlaves(Task* tasks, unsigned short numberOfTasks, unsigned short numberOfProcessors);
Task* getTasksFromMaster(unsigned short numberOfTasks, unsigned short numberOfProcessors);



int main(int argc, char *argv[])
{
    clock_t begin = clock();
    if (USE_MPI) useMPI(argc, argv);
    else useSequentialAlgorithm(argc, argv);
    clock_t end = clock();
    double elapsedSeconds = double(end - begin)/CLOCKS_PER_SEC;
    cout << "Time: " << elapsedSeconds << endl;
    return 0;
}




Task* generateNTasks(unsigned n)
{
    Task *tasks = new Task[n];
    
    srand(unsigned(time(0)));
    //    cout << "Size of a task: " << sizeof(Task) << endl;
    for (int i = 0; i < n; i++)
    {
        tasks[i].setT(rand() % MAX_RUN_TIME);
        tasks[i].setD(rand() % MAX_ALLOWED_TIME);
        tasks[i].setZ(rand() % MAX_PENALIZATION);
        tasks[i].setID(i+1);
    }
    
    return tasks;
    
}

void printTasks(Task *tasks, int numberOfTasks)
{
    for (int i = 0; i < numberOfTasks; i++)
    {
        cout << tasks[i].ID() <<" " << tasks[i].t() << " " << tasks[i].d() << " " << tasks[i].z() << endl;
    }
}


void useSequentialAlgorithm(int argc, char *argv[])
{
    int numberOfTasks = NUMBER_OF_TASKS;
    if (argc > 1) numberOfTasks = atoi(argv[1]);
    Task* tasks = generateNTasks(numberOfTasks);
    
    //    cout << sizeof(tasks) / sizeof(Task) << endl;
    
    cout  << "Initial set of tasks:" << endl;
    printTasks(tasks, numberOfTasks);
    
    TaskScheduller scheduller(0, 1);
    unsigned penalty = scheduller.minimalPenalizationForSchedulingTasks(tasks, numberOfTasks);
    cout << "Scheduled set of tasks:" << endl;
    printTasks(scheduller.resultTasks, numberOfTasks);
    cout << "Penalty: "<< penalty << endl;
    delete []tasks;

}


void useMPI(int argc, char *argv[])
{
  if (USE_MPI)
  {
    int myRank;
    int p; // # of processes
    
    MPI_Init(&argc, &argv);
    
    MPI_Comm_rank(MPI_COMM_WORLD, &myRank);
    MPI_Comm_size(MPI_COMM_WORLD, &p);
    
    if (myRank != 0) //I'm a slave
    {
        executeSlaveWork(myRank, p, argc, argv);
    }
    else //I'm the master
    {
        executeMasterWork(myRank, p, argc, argv);
    }
      
    cout << "We're done. Calling MPI_Finalize()" << endl;
    MPI_Finalize();
  }// if(USE_MPI)
}

void executeSlaveWork(unsigned short processorRank, unsigned short numberOfProcessors, int argc, char** argv)
{
    if (USE_MPI)
    {
        //            int dest = 0;
        //            int tag  = 1;
        
        int numberOfTasks = NUMBER_OF_TASKS;
        if (argc > 1) numberOfTasks = atoi(argv[1]);

        Task* tasks = getTasksFromMaster(numberOfTasks, numberOfProcessors);
        cout << "Hey I am slave " << processorRank << "; initial set of tasks received." <<endl;

        
        TaskScheduller scheduller(processorRank, numberOfProcessors);
        scheduller.startScheduller(tasks, numberOfTasks);//minimalPenalizationForSchedulingTasks(tasks, numberOfTasks);

        delete []tasks;

    }//if (USE_MPI)
}

void executeMasterWork(unsigned short processorRank, unsigned short numberOfProcessors, int argc, char** argv)
{
    if (USE_MPI)
    {
        cout << "# of processes: " << numberOfProcessors << endl;
        
        
        int numberOfTasks = NUMBER_OF_TASKS;
        if (argc > 1) numberOfTasks = atoi(argv[1]);
        Task* tasks = generateNTasks(numberOfTasks);
        
        sendTasksToSlaves(tasks, numberOfTasks, numberOfProcessors);
        
        cout  << "Initiale set of tasks:" << endl;
        printTasks(tasks, numberOfTasks);
        
        TaskScheduller scheduller(processorRank, numberOfProcessors);
        scheduller.startScheduller(tasks, numberOfTasks);
        unsigned penalty = scheduller.getUpperBound();
        unsigned lowerBound = scheduller.getLowerBound();
        cout << "Lower bound: "<< lowerBound << " penalty: " << penalty << endl;
        cout << "Schedulede set of tasks:" << endl;
        printTasks(scheduller.resultTasks, numberOfTasks);

        delete []tasks;
    }//if (USE_MPI)
}

void sendTasksToSlaves(Task* tasks, unsigned short numberOfTasks, unsigned short numberOfProcessors)
{
    //    cout << sizeof(tasks) / sizeof(Task) << endl;
    short length = numberOfTasks*sizeof(int)*4;
    char message[length];
    int position = 0;
//    short tag = 0;
    unsigned short tasksData[numberOfTasks*4];
    short j = 0;
    for (short i = 0; i < numberOfTasks; i++)
    {
        tasksData[j] = tasks[i].ID();
        tasksData[j+1] = tasks[i].t();
        tasksData[j+2] = tasks[i].d();
        tasksData[j+3] = tasks[i].z();
        j += 4;
    }
    if (USE_MPI)
    {
        MPI_Pack(tasksData, numberOfTasks*4, MPI_INT, message, length, &position, MPI_COMM_WORLD);
        
        
        for (short i = 1; i < numberOfProcessors; i++)
        {
            MPI_Send(message, length, MPI_PACKED, i, TAG_SEND_INITIAL_TASKS, MPI_COMM_WORLD);
        }
    }

}

Task* getTasksFromMaster(unsigned short numberOfTasks, unsigned short numberOfProcessors)
{
    int length = numberOfTasks*sizeof(int)*4;
    char message[length];
    int position = 0;
    unsigned short tasksData[numberOfTasks*4];
    
    if (USE_MPI)
    {
        MPI_Status status;
        
        MPI_Recv(message, length, MPI_PACKED, DESTINATION_MASTER, TAG_SEND_INITIAL_TASKS, MPI_COMM_WORLD, &status);
        MPI_Unpack(message, length, &position, tasksData, numberOfTasks*4, MPI_INT, MPI_COMM_WORLD);
    }
    
    Task* tasks = new Task[numberOfTasks];
    
    short j  = 0;
    for (short i = 0; i < numberOfTasks; i++)
    {
        tasks[i].setID(tasksData[j]);
        tasks[i].setT(tasksData[j+1]);
        tasks[i].setD(tasksData[j+2]);
        tasks[i].setZ(tasksData[j+3]);
        j += 4;
    }
//    printTasks(tasks, numberOfTasks);
    
    return tasks;
}

