//
//  TaskScheduller.h
//  TaskScheduller1.0
//
//  Created by Maxim Chetrusca on 10/8/13.
//  Copyright (c) 2013 Maxim Chetrusca. All rights reserved.
//

#ifndef __TaskScheduller1_0__TaskScheduller__
#define __TaskScheduller1_0__TaskScheduller__

#include <iostream>
#include "Task.h"
#include "Job.h"
#include <queue>
#include <stack>

#define K 1

#define MAX_RUN_TIME 10
#define MAX_ALLOWED_TIME 20
#define MAX_PENALIZATION 10




#pragma mark TaskScheduller no default constructor!

class TaskScheduller
{
public:
    TaskScheduller(int rank, int p);
    TaskScheduller(const TaskScheduller& taskScheduller);
    virtual ~TaskScheduller();
    Task* resultTasks;
    Task* initialTasks;
    unsigned* resultIDtasks;
    
    unsigned getUpperBound();
    unsigned getLowerBound();

    
    TaskScheduller operator=(const TaskScheduller& taskScheduller);
    
    //Takes an array of tasks, schedules them and returns the total penalization
    unsigned minimalPenalizationForSchedulingTasks(Task* tasks, unsigned numberOfTasks); // use this for sequential algorithm.
    void startScheduller(Task* tasks, unsigned numberOfTasks); // use for parallel algorithm only!

private:
//    Node* head;
    unsigned numberOfTasks;
    unsigned lowerBound;
    unsigned upperBound;
    queue<Job> queueOfJobs;
    unsigned short wantedSizeOfTheList;
    bool slavesStopped;
    
    int rank; //processor #
//    short k; //how many jobs ...
    int p; // # of processors
    
    unsigned computeLowerBound();
    unsigned computeUpperBound();
    void populateTheTree();

    
    void startSlaveRoutine();
    Job* askForAJob();
    void doTheJob(Task* parentTask, list<Task*> tasks, unsigned short currentTime, unsigned short currentPenalization, stack<unsigned> stackOfTasks);
//    void sendTheResults();
    
    void computeCurrentState(Task* tasks, unsigned numberOfTasks);
    void createTheQueueOfJobs();
    void startMasterRoutine();
   short computeTheWantedSizeOfAJob();
    Task* populateTheQueue(Task* parentTask, list<Task*> tasks,  unsigned currentTime,  unsigned currentPenalization, stack<unsigned> stackOfTasks);
    unsigned* arrayFromQueue(queue<unsigned> currentQueueOfTasks);
    unsigned* arrayFromStack(stack<unsigned> currentStackOfTasks,  bool forJob);
    unsigned* reversedArrayFromStack(stack<unsigned> currentStackOfTasks);


    void sendThisArray(unsigned* array);
    void sendStopToAll();
    void generateResults();
};

#endif /* defined(__TaskScheduller1_0__TaskScheduller__) */
