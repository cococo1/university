// Copyright Max Chetrusca, modified Nov 11, 2014
// car_adt.h
// Data Structures & Algorithms, 2011

// This is a header file for an ADT
// It is included into car_adt.c file, where the functions are defined
// The ADT is based on a structure that discribe cars 
// Max Chetrusca, Feb 3, 2011

#ifndef DSA_CAR_ADT_H_
#define DSA_CAR_ADT_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	char model[10];   //Name of the car
	char country[15]; // Where is the car from
	int date;         // Date of manufacturing
	int capacity;     // Capacity of engine
	int cost;         // The price
}CAR;

// Inputs an array of structure CAR from the keyboard
void input(CAR *,int n);   
// Outputs an array of structure CAR on the screen
void output(CAR *,int n);  
// Searches a car by a given name
int search(CAR*,int n, char * );  
//Sorts the array of cars, by price
void sort(CAR*,int n);  
//Performs changes in this list of cars, if it's needed
void edit(CAR* cars,int n, int k);  
//Adds a new car to the existing list
void add(CAR*, int *n, int pos); 
//Reads from a file info about an array of cars
CAR* reading(CAR*, int *n, char *);

#endif  // DSA_CAR_ADT_H_

