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

// helper function, for clearing the input buffer:
static void fflush_stdin(void)
{
        int ch = 0;
        while((ch = getchar()) != '\n' && ch != EOF) /* clear buffer */;
}

void input(const int n, CAR *cars)
{
        assert(cars);
        assert(n > 0);
        // Inputs an array of structure CAR from the keyboard. The number of
        // cars n is given.
	for (int i = 0; i < n; ++i) {
	        printf("\nGive the information about the %d car:\n", i + 1);
                fflush(stdout);
	        puts("Name of the model");
	        scanf("%9s", cars[i].model);
                fflush_stdin();
	        puts("Write the country");
	        scanf("%14s", cars[i].country);
                fflush_stdin();
	        puts("What is the year of manufacturing ?");
	        int filled = scanf("%d", &cars[i].date);
                assert(filled == 1);
                fflush_stdin();
                assert(cars[i].date > 0);
	        puts("What is the capacity of engine?");
	        filled = scanf("%d", &cars[i].capacity);
                assert(filled == 1);
                fflush_stdin();
                assert(cars[i].capacity > 0);
	        puts("What is the price ?");
	        filled = scanf("%d", &cars[i].cost);
                assert(filled == 1);
                fflush_stdin();
                assert(cars[i].cost > 0);
	}
}

void output(const int n, const CAR *cars)
{
        assert(cars);
        assert(n > 0);
        // Outputs an array of structure CAR on the screen; n - number of cars.
        for (int i = 0; i < n; ++i) {
                printf(" \nInformation about car No: %d \n", i + 1);
                puts("Model:");
                printf("%s \n", cars[i].model);
                puts("Country:");
                printf("%s \n", cars[i].country);
                puts("Date of manufacturing:");
                printf("%d \n", cars[i].date);
                puts("The capacity of engine:");
                printf("%d \n", cars[i].capacity);
                puts("Cost:");
                printf("%d \n", cars[i].cost);
                fflush(stdout);
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

static void internal_for(const int n, const int i, CAR* cars)
{
        assert(n > 0);
        assert(i >= 0);
        assert(i < n);
        assert(cars);
	CAR car = { .date = 0 };
        for (int j = 0; j < n -  i - 1; ++j) {
                if (cars[j].cost > cars[j + 1].cost) {
                        car = cars[j];
		        cars[j] = cars[j + 1];
			cars[j + 1] = car;
	        }
	}
}

void sort(const int n, CAR *cars)
{
        assert(cars);
        assert(n > 0);
        // Sorts the array of cars, by price. Bubble sort used. n - numb. of
        // cars;
	for (int i = 0; i < n - 1; ++i) {
                internal_for(n, i, cars);
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
	scanf("%c", &ans);
        fflush_stdin();
	if (ans == 'y') {
	        puts("Introduce the new name of model:");
		scanf("%9s", cars[k].model);
                fflush_stdin();
	}
	puts("Do you want to change the country of model? y/n");
	scanf("%c", &ans);
        fflush_stdin();
	if (ans == 'y') {
		puts("Introduce the new name of country:");
		scanf("%14s", cars[k].country);
                fflush_stdin();
	}
	puts("Do you want to change the date of manufacturing of model? y/n");
	scanf("%c", &ans);
        fflush_stdin();
	if (ans == 'y') {
		puts("Introduce the new date of manufacturing:");
	        int filled = scanf("%d", &cars[k].date);
                fflush_stdin();
                assert(filled == 1);
                assert(cars[k].date > 0);
	}
	puts("Do you want to change the capacity of model? y/n");
	scanf("%c", &ans);
        fflush_stdin();
	if (ans == 'y') {
		puts("Introduce the new capacity of the car:");
		int filled = scanf("%d", &cars[k].capacity);
                assert(filled = 1);
                fflush_stdin();
                assert(cars[k].capacity > 0);
	}
	puts("Do you want to change the cost of model? y/n");
	scanf("%c", &ans);
        fflush_stdin();
	if (ans == 'y') {
		puts("Introduce the new cost of car:");
	        int filled = scanf("%d", &cars[k].cost);
                assert(filled == 1);
                fflush_stdin();
                assert(cars[k].cost > 0);
	}
}

void add(const int pos, CAR **cars, int *n)
{
        assert(cars);
        assert(n > 0);
        assert(pos >= 0);
        assert(pos <= *n);
        //Adds a new car to the existing list of n cars, to the possition pos .
	(*n)++;
	(*cars) = (CAR*)realloc((*cars), (*n) * sizeof(CAR));
        assert((*cars));
	for (int i = (*n); i >= pos; --i) {
		(*cars)[i] = (*cars)[i - 1];
	}
	puts("Give the information about new car:");
	puts("Type the model");
        scanf("%9s", (*cars)[pos].model);
        fflush_stdin();
	puts("Write the country");
        scanf("%14s", (*cars)[pos].country);
        fflush_stdin();
        puts("Type the year of manufacturing with numbers ");
        int filled = scanf("%d", &(*cars)[pos].date);
        assert(filled == 1);
        fflush_stdin();
        assert((*cars)[pos].date > 0);
	puts("What is the capacity of engine?");
        filled = scanf("%d", &(*cars)[pos].capacity);
        assert(filled == 1);
        fflush_stdin();
        assert((*cars)[pos].capacity > 0);
	puts("What is the price?");
        filled = scanf("%d", &(*cars)[pos].cost);
        assert(filled == 1);
        fflush_stdin();
        assert((*cars)[pos].capacity > 0);
        assert((*cars)[pos].cost > 0);
}

CAR* read(const char *filename, CAR** cars, int *n)
{
        assert(cars);
        assert(filename);
        //Reads from a file info about an array of cars
	FILE *f = NULL;
	f = fopen(filename, "r");
        assert(f);
	(*cars) = (CAR*)realloc((*cars), sizeof(CAR));
        assert(*cars);
	int filled = fscanf(f,
                            "%9s %14s %d %d %d",
                            (*cars)[0].model,
                            (*cars)[0].country,
                            &(*cars)[0].date,
                            &(*cars)[0].capacity,
                            &(*cars)[0].cost);
        assert(filled == 5);
        assert((*cars)[0].date > 0);
        assert((*cars)[0].capacity > 0);
        assert((*cars)[0].cost > 0);
        int i = 0;
	while (1) {
                i++;
		(*cars) = (CAR*)realloc((*cars), (i + 1) * sizeof(CAR));
	        assert((*cars));
		int filled = fscanf(f,
                                    "%9s %14s %d %d %d",
                                    (*cars)[i].model, 
                                    (*cars)[i].country,
                                    &(*cars)[i].date,
                                    &(*cars)[i].capacity,
                                    &(*cars)[i].cost);
                assert(filled == 5);
                assert((*cars)[i].date > 0);
                assert((*cars)[i].capacity > 0);
                assert((*cars)[i].cost > 0);
	}
	puts("File successfully scaned.");
	(*n) = i;
	fclose(f);
	return (*cars);
}
