// This is a header file for an ADT
// It is included into Chetrusca.cpp file, where the functions are defined
// The ADT is based on a structure that discribe cars 
// Made by Chetrusca Maxim 3.02.2011

#include <stdio.h>
#include <stdlib.h>
#include <string.h>



/////////////////////////////////////////////////////////////////////////
typedef struct
{
	char model[10];   //Name of the car
	char country[15]; // Where is the car from
	int date;         // Date of manufacturing
	int capacity;     // Capacity of engine
	int cost;         // The price
}CAR;


/////////////////////////////////////////////////////////////////////////
void input(CAR *,int n);   
// Inputs an array of structure CAR from the keyboard
void output(CAR *,int n);  
// Outputs an array of structure CAR on the screen
int search(CAR*,int n, char * );  
// Searches a car by a given name
void sort(CAR*,int n);  
//Sorts the array of cars, by price
void edit(CAR* cars,int n, int k);  
//Performs changes in this list of cars, if it's needed
void add(CAR*, int *n, int pos); 
//Adds a new car to the existing list
CAR* reading(CAR*, int *n, char *);
//Reads from a file info about an array of cars



/////////////////////////////////////////////////////////////////////
//END OF FILE
