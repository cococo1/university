//
//  Task.cpp
//  TaskScheduller1.0
//
//  Created by Maxim Chetrusca on 10/8/13.
//  Copyright (c) 2013 Maxim Chetrusca. All rights reserved.
//

#include "Task.h"


//using namespace std;


Task:: Task():
_t(0),
_d(0),
_z(0),
_ID(-1)
{
//    cout <<"Task()" << endl;
//    _t = _z = _d = ID = 0;
}

Task:: Task(unsigned short t, unsigned short d, unsigned short z, unsigned short ID):
_t(t),
_d(d),
_z(z),
_ID(ID)
{
//    cout << "Task(unsigned short t, unsigned short d, unsigned short z)" << endl;
}

Task:: Task(const Task& task):
_ID(task._ID),
_t(task._t),
_d(task._d),
_z(task._z)
{
//    cout <<"Task(const Task& task)" << endl;
}

Task:: ~Task()
{
//    cout << "~Task()" << ID << endl;
}

Task& Task:: operator= (const Task& task)
{
    if (this != &task)
    {
//        cout <<"operator= (const Task& task)" << endl;
        _t = task._t;
        _d = task._d;
        _z = task._z;
        _ID = task._ID;
    }

    return *this;
}

unsigned short Task:: t() const
{
//    cout << "t()" << endl;
    return _t;
}

unsigned short Task:: d() const
{
//    cout << "d()" << endl;
    return _d;
}

unsigned short Task:: z() const
{
//    cout << "z()" << endl;
    return _z;
}

void Task:: setT(unsigned short t)
{
//    cout << "setT()" << endl;
    _t = t;
}

void Task:: setD(unsigned short d)
{
//    cout << "setD()" << endl;
    _d = d;
}

void Task:: setZ(unsigned short z)
{
//    cout << "setZ()" << endl;
    _z = z;
}

unsigned short Task:: ID() const
{
    return _ID;
}

void Task:: setID(unsigned short ID)
{
    _ID = ID;
}






