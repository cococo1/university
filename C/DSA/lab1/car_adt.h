// Copyright Max Chetrusca, modified Nov 11, 2014
// car_adt.h
// Data Structures & Algorithms, 2011

// This is a header file for an ADT
// It is included into car_adt.c file, where the functions are defined
// The ADT is based on a structure that discribe cars 
// Max Chetrusca, Feb 3, 2011

#ifndef DSA_CAR_ADT_H_
#define DSA_CAR_ADT_H_

typedef struct {
	char model[10];   //Name of the car
	char country[15]; // Where is the car from
	int date;         // Date of manufacturing
	int capacity;     // Capacity of engine
	int cost;         // The price
}CAR;

// Inputs an array of structure CAR from the keyboard
void input(const int n, CAR *cars);   
// Outputs an array of structure CAR on the screen
void output(const int n, const CAR *cars);  
// Searches a car by a given name
int search(const int n, const char *wanted, const CAR *cars);  
// Sorts the array of cars, by price
void sort(const int n, CAR *cars);  
// Performs changes in this list of cars, if it's needed
void edit(const int n, const int k, CAR *cars);  
// Adds a new car to the existing list
void add(const int pos, CAR **cars, int *n); 
// Reads from a file info about an array of cars
CAR* read(const char *filename, CAR **cars, int *n);

#endif  // DSA_CAR_ADT_H_

