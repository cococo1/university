// Copyright Max Chetrusca, modified Nov 11, 2014
// car_adt.c
// Data Structures & Algorithms, 2011

// This file is a part of an ADT
// car_adt.h is the header file
// The ADT is based on a structure that discribe cars 
// Max Chetrusca, Feb 3, 2011

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "car_adt.h" 

void input(const int n, CAR *cars)
{
        assert(cars);
        assert(n > 0);
        // Inputs an array of structure CAR from the keyboard. The number of
        // cars n is given.
	for (int i = 0; i < n; ++i) { 
	        printf("\nGive the information about the %i car:\n", i + 1);
	        puts("Name of the model");
	        scanf("%s", cars[i].model);
	        puts("Write the country");
	        scanf("%s", cars[i].country);
	        puts("What is the year of manufacturing ?");
	        scanf("%i", &cars[i].date);
                assert(cars[i].date > 0);
	        puts("What is the capacity of engine?");
	        scanf("%i", &cars[i].capacity);
                assert(cars[i].capacity > 0);
	        puts("What is the price ?");
	        scanf("%i", &cars[i].cost);
                assert(cars[i].cost > 0);
	}
}

void output(const int n, const CAR *cars)
{
        assert(cars);
        assert(n > 0);
        // Outputs an array of structure CAR on the screen; n - number of cars.
        for (int i = 0; i < n; ++i) {
                printf(" \nInformation about car No: %i \n", i + 1);
                puts("Model:");
                printf("%s \n", cars[i].model);
                puts("Country:");
                printf("%s \n", cars[i].country);
                puts("Date of manufacturing:");
                printf("%i \n", cars[i].date);
                puts("The capacity of engine:");
                printf("%i \n", cars[i].capacity);
                puts("Cost:");
                printf("%i \n", cars[i].cost);
                puts("Press any key for next model");
        }
}

int search(const int n, const char *wanted, const CAR *cars)
{
        assert(cars);
        assert(wanted);
        assert(n > 0);
        // Searches a car by a given name. n- number of cars; wanted - the name
        // of the car to search.
	for (int i = 0; i < n; ++i) {
		if (strcmp(cars[i].model, wanted) == 0) { 
		        puts("Model found!"); 
		        return i;
		}
	}
	puts("Model not found.");
	return -1;
}

void sort(const int n, CAR *cars)
{
        assert(cars);
        assert(n > 0);
        // Sorts the array of cars, by price. Bubble sort used. n - numb. of
        // cars;
	CAR car = { .date = 0 };
	for (int i = 0; i < n - 1; ++i) {
                for (int j = 0; j < n -  i - 1; ++j) {
                        if (cars[j].cost > cars[j + 1].cost) {
			        car = cars[j]; 
				cars[j] = cars[j + 1];
				cars[j + 1] = car;
			}
		}
	}
}

void edit(const int n, const int k, CAR *cars)
{
        assert(cars);
        assert(n > 0);
        assert(k >= 0);
        assert(k < n);
        // Performs changes in this list of cars, if it's needed. After
        // question, press 'y' or 'n'
	char ans = '\0';
	puts("Do you want to change the name of model? y/n");
	fflush(stdin);
	scanf("%c", &ans);
	if (ans == 'y') {
	        puts("Introduce the new name of model:");
		scanf("%s", cars[k].model);
	}
	puts("Do you want to change the country of model? y/n");
	fflush(stdin);
	scanf("%c", &ans);
	if (ans == 'y') {
		puts("Introduce the new name of country:");
		scanf("%s", cars[k].country);
	}
	puts("Do you want to change the date of manufacturing of model? y/n");
	fflush(stdin);
	scanf("%c", &ans);
	if (ans == 'y') {
		puts("Introduce the new date of manufacturing:");
	    scanf("%i", &cars[k].date);
            assert(cars[k].date > 0);
	}
	puts("Do you want to change the capacity of model? y/n");
	fflush(stdin);
	scanf("%c", &ans);
	if (ans == 'y') {
		puts("Introduce the new capacity of the car:");
		scanf("%i", &cars[k].capacity);
                assert(cars[k].capacity > 0);
	}
	puts("Do you want to change the cost of model? y/n");
	fflush(stdin);
	scanf("%c", &ans);
	if (ans == 'y') {
		puts("Introduce the new cost of car:");
	        scanf("%i", &cars[k].cost);
                assert(cars[k].cost > 0);
	}
}

void add(const int pos, CAR *cars, int *n)
{
        assert(cars);
        assert(n > 0);
        assert(pos > 0);
        //Adds a new car to the existing list of n cars, to the possition pos .
	(*n)++;
	cars = (CAR*)realloc(cars, (*n) * sizeof(CAR));
        assert(cars);
	for (int i = (*n); i >= pos; --i) {
		cars[i] = cars[i - 1];
	}
	puts("Give the information about new car:");
	puts("Type the model");
        scanf("%s", cars[pos].model);
	puts("Write the country");
        scanf("%s", cars[pos].country);
        puts("Type the year of manufacturing with numbers ");
        scanf("%i", &cars[pos].date);
        assert(cars[pos].date > 0);
	puts("What is the capacity of engine?");
        scanf("%i", &cars[pos].capacity);
        assert(cars[pos].capacity > 0);
	puts("What is the price?");
        scanf("%i", &cars[pos].cost);
        assert(cars[pos].cost > 0);
}

CAR* read(const char *filename, CAR* cars, int *n)
{
        assert(filename);
        //Reads from a file info about an array of cars
	FILE *f = NULL;
	f = fopen(filename, "r");
        assert(f);
	cars = (CAR*)realloc(cars, sizeof(CAR));
        assert(cars);
	fscanf(f,
               "%s %s %d %d %d",
               cars[0].model,
               cars[0].country,
               &cars[0].date,
               &cars[0].capacity,
               &cars[0].cost);
        assert(cars[0].date > 0);
        assert(cars[0].capacity > 0);
        assert(cars[0].cost > 0);
        int i = 0;
	while (getc(f) != EOF) {
                i++;
		cars = (CAR*)realloc(cars, (i + 1) * sizeof(CAR));
	        assert(cars);		
		fscanf(f,
                       "%s %s %d %d %d",
                       cars[i].model, 
                       cars[i].country,
                       &cars[i].date,
                       &cars[i].capacity,
                       &cars[i].cost);
                assert(cars[i].date > 0);
                assert(cars[i].capacity > 0);
                assert(cars[i].cost > 0);
	}
	puts("File successfully scaned.");
	(*n) = i;
	fclose(f);
	return cars;
}

