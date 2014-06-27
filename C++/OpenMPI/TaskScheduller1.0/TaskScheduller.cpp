//
//  TaskScheduller.cpp
//  TaskScheduller1.0
//
//  Created by Maxim Chetrusca on 10/8/13.
//  Copyright (c) 2013 Maxim Chetrusca. All rights reserved.
//

#include "TaskScheduller.h"
#include "mpi.h"
#include <stdio.h>

using namespace std;

TaskScheduller:: TaskScheduller(int rank, int p):
lowerBound(0),
upperBound(INFINITY), //"infinity"
initialTasks(NULL),
resultTasks(NULL),
numberOfTasks(0),
rank(rank),
p(p),
resultIDtasks(NULL),
slavesStopped(false)
{
//    cout << "TaskScheduller(int rank, int p) with rank: " <<  rank << endl;

}

TaskScheduller:: TaskScheduller(const TaskScheduller& taskScheduller):
lowerBound(taskScheduller.lowerBound),
upperBound(taskScheduller.upperBound),
initialTasks(new Task[taskScheduller.numberOfTasks]),
resultTasks(new Task[taskScheduller.numberOfTasks]),
numberOfTasks(taskScheduller.numberOfTasks),
rank(taskScheduller.rank),
p(taskScheduller.p),
queueOfJobs(taskScheduller.queueOfJobs),
resultIDtasks(new unsigned[numberOfTasks]),//taskScheduller.resultIDtasks),
slavesStopped(taskScheduller.slavesStopped)
{
    cout << "TaskScheduller(const TaskScheduller& taskScheduller)" << endl;

    
    for (int i = 0; i < numberOfTasks; i++)
    {
        initialTasks[i] = taskScheduller.initialTasks[i];
        resultTasks[i] = taskScheduller.resultTasks[i];
        resultIDtasks[i] = taskScheduller.resultIDtasks[i];
    }
    
}

TaskScheduller:: ~TaskScheduller()
{
    cout << "~TaskScheduller() rank: " << rank << endl;
    delete []initialTasks;
    delete []resultTasks;
    delete []resultIDtasks;
}

TaskScheduller TaskScheduller:: operator=(const TaskScheduller& taskScheduller)
{
    cout << " TaskScheduller:: operator=(const TaskScheduller& taskScheduller)" << endl;
    if (this != &taskScheduller)
    {
        delete []initialTasks;
        delete []resultTasks;
        delete []resultIDtasks;
        
        lowerBound = taskScheduller.lowerBound;
        upperBound = taskScheduller.upperBound;
        initialTasks = new Task[taskScheduller.numberOfTasks];
        resultTasks = new Task[taskScheduller.numberOfTasks];
        resultIDtasks = new unsigned[taskScheduller.numberOfTasks];
        
        numberOfTasks = taskScheduller.numberOfTasks;
        rank = taskScheduller.rank;
        p = taskScheduller.p;
        queueOfJobs = taskScheduller.queueOfJobs;
        slavesStopped = taskScheduller.slavesStopped;
        
        for (int i = 0; i < numberOfTasks; i++)
        {
            initialTasks[i] = taskScheduller.initialTasks[i];
            resultTasks[i] = taskScheduller.resultTasks[i];
            resultIDtasks[i] = taskScheduller.resultIDtasks[i];
        }
    }
    return *this;
}

unsigned TaskScheduller:: minimalPenalizationForSchedulingTasks(Task* tasks, unsigned numberOfTasks)
{
    if (rank == 0)
    {
        cout << "minimalPenalizationForSchedulingTasks(Task* tasks)" << endl;
        Job::totalNumberOfTasks = numberOfTasks;
        this->numberOfTasks = numberOfTasks;
        delete []this->initialTasks;
        this->initialTasks = new Task[numberOfTasks];
        resultTasks = new Task[numberOfTasks];
        resultIDtasks = new unsigned(numberOfTasks);
        for (int i = 0; i < numberOfTasks; i++)
        {
            this->initialTasks[i] = tasks[i];
            resultTasks[i] = tasks[i];
//            cout << "id " << tasks[i].ID() << " t " << tasks[i].t() << " d " << tasks[i].d() << " z " << tasks[i].z() << endl;
        }
        
        computeLowerBound();
        computeUpperBound();
        
        if (lowerBound == upperBound)
        {
            //The planets aligned in such a way that the solution is already here:
            cout << "The planets aligned! " << endl;
            return upperBound;
        }
        
        populateTheTree();
    }
    return upperBound;
}

unsigned TaskScheduller:: computeLowerBound()
{
//    cout << "TaskScheduller:: computeLowerBound() rank "<< rank << endl;
    unsigned maxLowerBound = 0;
    for (int i = 0; i < numberOfTasks; i++)
    {
        if (initialTasks[i].t() > initialTasks[i].d())
        {
             maxLowerBound += initialTasks[i].z();
        }
    }
    lowerBound = maxLowerBound;
    cout << "The lower bound is: " << lowerBound << endl;
    return maxLowerBound;
}

unsigned TaskScheduller:: computeUpperBound()
{
//    cout << "TaskScheduller:: computeUpperBound() rank "<< rank << endl;
    unsigned minUpperBound = 0;
    unsigned time = 0;
    
    for (int i = 0; i < numberOfTasks; i++)
    {
        time += initialTasks[i].t();
        if (time > initialTasks[i].d()) minUpperBound += initialTasks[i].z();
        resultIDtasks[i] = initialTasks[i].ID();
    }
    
    upperBound = minUpperBound;
    cout << "The upper bound is: " << upperBound << endl;
    return minUpperBound;
}

void TaskScheduller:: populateTheTree()
{
    if (rank == 0)
    {
        cout << "TaskScheduller:: populateTheTree()" << endl;
        list<Task*> listOfNodes;
        cout << sizeof(initialTasks) << endl;
        for (int i = 0; i < numberOfTasks; i++)
        {
            listOfNodes.push_back(&initialTasks[i]);
        }
        stack<unsigned> stackOfTasks;

        Task* startTask = new Task();

        doTheJob    (startTask, listOfNodes, 0, 0, stackOfTasks);
    }
}

void TaskScheduller:: startScheduller(Task* tasks, unsigned numberOfTasks)
{
//    cout << "startScheduller rank "<< rank << endl;
    if (p > 1) //we have a parallel algorithm
    {
        Job::totalNumberOfTasks = numberOfTasks;
        
        if (rank == 0)
        {
            //we have a master;
            computeCurrentState(tasks, numberOfTasks);
            if (lowerBound != upperBound)
            {
                createTheQueueOfJobs();
                startMasterRoutine();
                sendStopToAll();
            }
            
            //we're done. Let's return the result:
            generateResults();
        }
        else if (rank > 0)
        {
            //we have a slave.
            this->numberOfTasks = numberOfTasks;
            startSlaveRoutine();
        }
    }
    else cout << "You asked to solve a parallel algorithm on one processor." << endl;
}

void TaskScheduller:: startSlaveRoutine()
{
//    cout << "startSlaveRoutine rank" << rank << endl;
    Job *job;
    while ((job = askForAJob()))
    {
        stack <unsigned> stackOfTasks;
        int i = 0;
        unsigned* arraya = job->getArrayOfTasks();

        i = Job::totalNumberOfTasks - 1 ;

        while (arraya[i]) //it is assumed that in the end there will be zeros
        {
            stackOfTasks.push(arraya[i]);
            i--;
        }
        upperBound = job->upperBound;
        lowerBound = job->lowerBound;
        
        Task *someTask = new Task(0,0,0,0);
        
        doTheJob(someTask, job->getListOfTasks(), job->getCurrentTime(), job->getCurrentPenalization(), stackOfTasks);
    }
    cout << "No more jobs." << endl;
}

Job* TaskScheduller:: askForAJob() //while there are jobs.
{
    bool someMessage = false;
    bool workAvailable = true;
//    cout << "ask for a job rank" << rank << endl;
    if (USE_MPI)
    {
        bool askedAlready =false;
        while (!someMessage)
        {
//            cout << "no message rank " << rank << endl;
            int flag;
            MPI_Status status;
            MPI_Iprobe(DESTINATION_MASTER, TAG_STOP, MPI_COMM_WORLD, &flag, &status);
            
            if (flag)
            {
                someMessage = true;
                char message[5];
                MPI_Recv(message, 5, MPI_CHAR, DESTINATION_MASTER, TAG_STOP, MPI_COMM_WORLD, &status);
                //THIS is the end:
                cout << "Stop received." << endl;
                MPI_Send(message, 5, MPI_CHAR, DESTINATION_MASTER, TAG_STOP, MPI_COMM_WORLD);
                return NULL;
            }
            
            if (!askedAlready)
            {
                askedAlready = true;
                char message[4] = "job";
                MPI_Send(message, 4, MPI_CHAR, DESTINATION_MASTER, TAG_JOB, MPI_COMM_WORLD);
            }
            flag = 0;
            MPI_Iprobe(DESTINATION_MASTER, TAG_JOB, MPI_COMM_WORLD, &flag, &status);
            if (flag && workAvailable)
            {
                someMessage = true;

                Job::size = computeTheWantedSizeOfAJob();
//                        cout << "job size: "<< Job::size << endl;
                unsigned length = Job::size*4*sizeof(unsigned) + 2*sizeof(unsigned) +2*sizeof(unsigned) + sizeof(unsigned) + Job::totalNumberOfTasks*sizeof(unsigned);
                char *buffer = new char[length];
//                        cout << "buffer length "<< length << endl;

                MPI_Recv(buffer, length, MPI_PACKED, DESTINATION_MASTER, TAG_JOB, MPI_COMM_WORLD, &status);
//                        cout << "1" << endl;
                Job *job = new Job(buffer);
//                        cout << "2" << endl;
                delete []buffer;
        
                list<Task*> ll = job->getListOfTasks();
        
                list<Task*>::iterator listIterator = ll.begin(), end = ll.end();
                
                for (; listIterator != end; listIterator++)
                {
                    
                    Task *task = *listIterator;
                    if ((task->ID() > 100) || (task->t() > MAX_RUN_TIME) || (task->d() > MAX_ALLOWED_TIME) || (task->z() > MAX_PENALIZATION))
                    {
                        cout << "This task from this list of jobs is corrupted. Aborting the execution. Rank: " << rank << endl;
                        workAvailable = false;
                    }
                }
                
                if (workAvailable) return job;
                else someMessage = false;
                    continue;
            }
        }

    }
            return NULL;
}

void TaskScheduller:: doTheJob(Task* parentTask,list<Task*> tasks, unsigned short currentTime, unsigned short currentPenalization, stack<unsigned> stackOfTasks)
{
    static bool solution = 0;
    
    currentTime += parentTask->t();
    if (currentTime > parentTask->d())
    {
        currentPenalization += parentTask->z();
        if (currentPenalization >= upperBound) // not optimal
        {
//                                cout << "Not optimal. Inserting ID " << task->ID << endl;
            return ;
        }
    }

    list<Task*>::iterator listIterator = tasks.begin(), end = tasks.end();

    for (; listIterator != end; listIterator++)
    {
        
        Task *task = *listIterator;

        stackOfTasks.push(task->ID());
        listIterator = tasks.erase(listIterator);
        if (tasks.empty()) //we've reached a leaf
        {

            currentTime += task->t();
            if (currentTime > task->d())
            {
                currentPenalization += task->z();
                if (currentPenalization > upperBound) // not optimal
                {
                    //                    cout << "Not optimal. Inserting ID " << task->ID << endl;
                    tasks.insert(listIterator, task);
                    return ;
                }
            }
            ////////////////////////////////////////////////////////////////////////////////
            ////////////////////////////////////////////////////////////////////////////////
            if (currentPenalization < upperBound)
            {
//                cout << "Update upperBound." << endl;
                upperBound = currentPenalization;
                unsigned *array = arrayFromStack(stackOfTasks,false);
                
                if (USE_MPI) sendThisArray(array);
//                cout << "send this array. rank: " << rank << endl;
                else
                {
                    for (int i = 0; i < numberOfTasks; i++)
                    {
                        resultTasks[i] = initialTasks[array[i]-1];
//                        cout << " " << array[i] << " ";
                    }
                }

                
            }
            
            if (upperBound <= lowerBound) //Yeah, magic
            {
//                                cout << "Solution found" << endl;
                solution = 1;
            }
            ////////////////////////////////////////////////////////////////////////////////
            //            cout << "Tasks empty. Inserting ID " << task->ID  << endl;
            
            tasks.insert(listIterator, task);
            
            return ;
        }
        
        if (! solution)  doTheJob(task, tasks, currentTime, currentPenalization, stackOfTasks);
        
        stackOfTasks.pop();

        tasks.insert(listIterator, task);
        
        listIterator--;
    }

}


void TaskScheduller:: computeCurrentState(Task* tasks, unsigned numberOfTasks)
{
//    cout << "computeCurrentState rank " << rank << endl;
    this->numberOfTasks = numberOfTasks;
    delete []this->initialTasks;
    this->initialTasks = new Task[numberOfTasks];
    resultTasks = new Task[numberOfTasks];
    delete []resultIDtasks;
    resultIDtasks  = new unsigned[numberOfTasks];
    for (int i = 0; i < numberOfTasks; i++)
    {
        this->initialTasks[i] = tasks[i];
        resultTasks[i] = tasks[i];
    }
    
    computeLowerBound();
    computeUpperBound();
    Job::lowerBound = lowerBound;
    Job::upperBound = upperBound;
    
    
    if (lowerBound == upperBound)
    {
        //The planets aligned in such a way that the solution is already here:
        cout << "The planets aligned! " << endl;
        sendStopToAll();
    }
}

void TaskScheduller:: createTheQueueOfJobs()
{
//    cout << "createTheQueueOfJobs rank " << rank << endl;
    wantedSizeOfTheList = computeTheWantedSizeOfAJob();
    Job::size = wantedSizeOfTheList;
    cout << "The job size is: " << Job::size << endl;
    
    list<Task*> listOfTasks;
//    cout << "Intial list of tasks " << endl;
    for (int i = 0; i < numberOfTasks; i++)
    {
        listOfTasks.push_back(&initialTasks[i]);
    }
    stack<unsigned> tasks;
    Task *task = new Task();
    populateTheQueue(task, listOfTasks, 0, 0, tasks);
    cout << "# of jobs: "<< queueOfJobs.size() << endl;
}

//send no
void TaskScheduller:: startMasterRoutine()
{
//    cout << "startMasterRoutine rank " <<rank << endl;
    if (USE_MPI)
    {
        cout << "# of pro " << p << endl;
        int flag;
        MPI_Status status;
        Job lastJob; //this is the last job. Send it to everyone when no more jobs... in order to synchronize.
        while (!queueOfJobs.empty())
        {
            for (int source = 1; source < p; source++)
            {
                flag = 0;
                MPI_Iprobe(MPI_ANY_SOURCE, TAG_POSSIBLE_SOLUTION, MPI_COMM_WORLD, &flag, &status);
                if (flag)
                {
                    int length = numberOfTasks*sizeof(unsigned) + sizeof(unsigned);
                    char message[length];
                    MPI_Recv(message, length, MPI_PACKED, MPI_ANY_SOURCE, TAG_POSSIBLE_SOLUTION, MPI_COMM_WORLD, &status);
                    
                    int position = 0;
                    unsigned *array = new unsigned[numberOfTasks];
                    unsigned possibleUpperBound = INFINITY;
                    MPI_Unpack(message, length, &position, array, numberOfTasks, MPI_UNSIGNED, MPI_COMM_WORLD);
                    MPI_Unpack(message, length, &position, &possibleUpperBound, 1, MPI_UNSIGNED, MPI_COMM_WORLD);
                    cout << "One possible solution received. " << endl;

                    if (possibleUpperBound < upperBound)
                    {
                        //new solution found!
                        upperBound = possibleUpperBound;
                        delete []resultIDtasks;
                        resultIDtasks = array;
                        Job::upperBound = upperBound;
                        
                        if (upperBound <= lowerBound) // yeah, magic
                        {
                            //We're done!
                            cout << "Ideal solution recieved!!! master." << endl;
                            sendStopToAll();
                            return;
                        }
                        
                    }
                    else delete []array;
                    
                    
                }
                flag = 0;
                
    #pragma mark What if one gets the last job, and the other one just waits for it?
//                cout << "master: anyone asks for a job?" << endl;
                MPI_Iprobe(source, TAG_JOB, MPI_COMM_WORLD, &flag, &status);
                if (flag)
                {
                    char message[4];
                    MPI_Recv(message, 4, MPI_CHAR, source, TAG_JOB, MPI_COMM_WORLD, &status);
//                    cout << source << " asks for job.(master)" << endl;
                    
                    Job job;
                    if (!queueOfJobs.empty())
                    {
                        job = queueOfJobs.front();
                        queueOfJobs.pop();
                    }
                    else
                    {
                        cout << "The queue is empty rank 0" << endl;
                        return;
                    }
                    unsigned length = Job::size*4*sizeof(unsigned) + 2*sizeof(unsigned) +2*sizeof(unsigned) + sizeof(unsigned) + Job::totalNumberOfTasks*sizeof(unsigned);
                    char *buffer = job.toBuffer();
                    MPI_Send(buffer, length, MPI_PACKED, source, TAG_JOB, MPI_COMM_WORLD);
                }
                flag = 0;
            }
        }
    }
}

short TaskScheduller:: computeTheWantedSizeOfAJob()
{
//    cout << "computeTheWantedSizeOfAJob rank " << rank << endl;
    int size = numberOfTasks;
    int n = 1;
    int pp = p-1;
    if (!pp) pp = 1;
    while (n < K*pp)
    {
        n *= size;
        size--;
        if (!size) { size = 1; break;}
    }
    return size;
}

Task* TaskScheduller:: populateTheQueue(Task* parentTask, list<Task*> tasks,  unsigned currentTime,  unsigned currentPenalization, stack<unsigned> stackOfTasks)
{
    bool ereased = false;
    currentTime += parentTask->t();
    if (currentTime > parentTask->d())
    {
        currentPenalization += parentTask->z();
        if (currentPenalization >= upperBound) // not optimal
        {
            return NULL;
        }
    }
    
    list<Task*>::iterator listIterator = tasks.begin(), end = tasks.end();
    
    
    for (; listIterator != end; listIterator++)
    {
        Task *task = *listIterator;

        if (tasks.size() > wantedSizeOfTheList)
        {
            listIterator = tasks.erase(listIterator);
            ereased = true;
            stackOfTasks.push(task->ID());
         }
        
        if (tasks.size() <= wantedSizeOfTheList)
        {
            if (ereased)
            {
                currentTime += task->t();
                if (currentTime > task->d())
                {
                    currentPenalization += task->z();
                    if (currentPenalization >= upperBound) // not optimal
                    {
                        return task;
                    }
                }
            }
            //we want to stop here, and add this "sublist" into the queue. It's good for a job.
            Job job(tasks,currentTime,currentPenalization,parentTask->ID());
            job.setArrayOfTasks(arrayFromStack(stackOfTasks,true));
            
            queueOfJobs.push(job);
            
            //And, after that:
            if (ereased)
            {
                if (currentTime > task->d()) currentPenalization -= task->z();
                currentTime -= task->t();
//                return task;
                tasks.insert(listIterator, task);
                listIterator--;
                stackOfTasks.pop();
                continue;
            }
            return parentTask;
        }
        
        Task *task1 = populateTheQueue(task, tasks, currentTime, currentPenalization, stackOfTasks);
        if (task1)
        {
//            cout << " returned :" << task1->ID() << " " << task1->t() << " " << task1->d() << " " << task1->z() << endl;
            tasks.insert(listIterator,task1);
            listIterator--;
        }
        if (ereased)
        {
            stackOfTasks.pop();
            tasks.insert(listIterator, task);
            listIterator--;
        }
    }
    return NULL;
}

unsigned* TaskScheduller:: arrayFromQueue(queue<unsigned> currentQueueOfTasks)
{
//    cout << "arrayFromQueue rank " << rank << endl;
    unsigned* array = new unsigned[Job::totalNumberOfTasks];
    for (int i = 0; i < Job::totalNumberOfTasks; i++)
    {
        array[i] = 0;
    }
    int i = 0;
    while(!currentQueueOfTasks.empty())
    {
        array[i] = currentQueueOfTasks.front();
        currentQueueOfTasks.pop();
        i++;
        
    }
    
    return array;
}

void TaskScheduller:: sendThisArray(unsigned* array)
{
//    cout << "sendThisArray rank " << rank << endl;
    if (USE_MPI)
    {
        short length = numberOfTasks*sizeof(unsigned) + sizeof(unsigned);
        char message[length];
        int position = 0;
        
        
        MPI_Pack(array, numberOfTasks, MPI_UNSIGNED, message, length, &position, MPI_COMM_WORLD);
        MPI_Pack(&upperBound, 1, MPI_UNSIGNED, message, length, &position, MPI_COMM_WORLD);
        MPI_Send(message, length, MPI_PACKED, DESTINATION_MASTER, TAG_POSSIBLE_SOLUTION, MPI_COMM_WORLD);
    }
}

void TaskScheduller:: sendStopToAll()
{
    if (!slavesStopped)
    {
        cout << "sendStopToAll rank " << rank << endl;
        if (USE_MPI)
        {
            char message[5] = "stop";

            for (int dest = 1; dest < p ; dest++)
            {
//                cout << "send stop 0" << endl;
                MPI_Send(message, 5, MPI_CHAR, dest, TAG_STOP, MPI_COMM_WORLD);
            }
            int stopsReceived = 0;
            int flag;
            MPI_Status status;
            
            while (stopsReceived < p-1)
            {
//                cout << "waiting for stop 0" << endl;
                flag = 0;
                MPI_Iprobe(MPI_ANY_SOURCE, TAG_POSSIBLE_SOLUTION, MPI_COMM_WORLD, &flag, &status);
                if (flag)
                {
                    cout << "One possible solution received. " << endl;
                    int length = numberOfTasks*sizeof(unsigned) + sizeof(unsigned);
                    char message[length];
                    MPI_Recv(message, length, MPI_PACKED, MPI_ANY_SOURCE, TAG_POSSIBLE_SOLUTION, MPI_COMM_WORLD, &status);
                    
                    int position = 0;
                    unsigned *array = new unsigned[numberOfTasks];
                    unsigned possibleUpperBound = INFINITY;
                    MPI_Unpack(message, length, &position, array, numberOfTasks, MPI_UNSIGNED, MPI_COMM_WORLD);
                    MPI_Unpack(message, length, &position, &possibleUpperBound, 1, MPI_UNSIGNED, MPI_COMM_WORLD);
                    
                    if (possibleUpperBound < upperBound)
                    {
                        //new solution found!
                        cout << "New solution found! master." << endl;
                        upperBound = possibleUpperBound;
                        delete []resultIDtasks;
                        resultIDtasks = array;
                        Job::upperBound = upperBound;
                        
                    }
                    else delete []array;
                }
                for (int source = 1; source < p; source++)
                {
                    flag = 0;
                    MPI_Iprobe(source, TAG_STOP, MPI_COMM_WORLD, &flag, &status);
                    if (flag)
                    {
                        cout << "one more slave stopped. " << endl;
                        MPI_Recv(message, 5, MPI_CHAR, source, TAG_STOP, MPI_COMM_WORLD, &status);
                        stopsReceived++;
                    }
                }

            }

        }
    }
    slavesStopped = true;
    
}


void TaskScheduller:: generateResults()
{
    cout << "generateResults rank " << rank << endl;
//    cout << "resultIDtasks size :" << sizeof(resultIDtasks) << "result tasks: " << sizeof(resultTasks) << endl;
    for (int i = 0; i < numberOfTasks; i++)
    {
        unsigned id = resultIDtasks[i];
        cout << id << " " << endl;
        resultTasks[i] = initialTasks[id-1]; // that is how the things stand.
    }
}

unsigned TaskScheduller::getUpperBound()
{
    return upperBound;
}

unsigned TaskScheduller:: getLowerBound()
{
    return lowerBound;
}

unsigned* TaskScheduller:: arrayFromStack(stack<unsigned> currentStackOfTasks, bool forJob)
{
//    cout << "arrayFromStack rank " << rank << endl;
    int length = Job:: totalNumberOfTasks;

    unsigned* array = new unsigned[length];
    for (int i = 0; i < length; i++)
    {
        array[i] = 0;
    }
    int i = length - 1;//Job::totalNumberOfTasks -1;

    while(!currentStackOfTasks.empty())
    {
//        cout << i << endl;
        array[i] = currentStackOfTasks.top();
        currentStackOfTasks.pop();
        i--;
        
        
    }
    
    return array;
}

unsigned* TaskScheduller:: reversedArrayFromStack(stack<unsigned> currentStackOfTasks)
{
    cout << "reversedArrayFromStack rank " << rank << endl;
    unsigned* array = new unsigned[Job::totalNumberOfTasks];
    for (int i = 0; i < Job::totalNumberOfTasks; i++)
    {
        array[i] = 0;
    }
    int i = 0;//Job::totalNumberOfTasks -1;
    //    cout << "total "<< Job::totalNumberOfTasks << endl;
    
    while(!currentStackOfTasks.empty())
    {
        //        cout << i << endl;
        array[i] = currentStackOfTasks.top();
        currentStackOfTasks.pop();
        i++;
    }
    return array;
}















