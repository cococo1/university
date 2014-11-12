// Copyright Max Chetrusca, modified Nov 11, 2014
// car_adt2.c
// Data Structures & Algorithms, 2011

// This file should be attached to car_adt2.h header file.
// Here is the defenition of functions declared there.
// Max Chetrusca, Feb 19, 2011

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "car_adt2.h"

CAR* allocate_memory(int n)
{
        assert(n > 0);
	CAR *head = NULL;
        CAR *current = NULL;
        CAR *pointer = NULL;
	head = (CAR*)malloc(sizeof(CAR));
        assert(head);
        head->model[0] = '\0';
        head->country[0] = '\0';
        head->date = 1;
        head->cost = 1;
        head->capacity = 1;
	// The variable head is defined anyway,
	// either there is one or more elements; 
        // n-- to avoid allocating memory for one more element
        n--;
	head->next = NULL;
	for (int i = 0; i < n; i++) {
                current = (CAR*)malloc(sizeof(CAR));
                assert(current);
                current->model[0] = '\0';
                current->country[0] = '\0';
                current->date = 1;
                current->capacity = 1;
		current->next = NULL;
		if (i == 0) {
		        head->next = current;
		} else {
			pointer->next = current;
		}
                pointer = current;
	}
	puts("Memory allocated.");
	return head;
}

void input (CAR *head)
{
        assert(head);
	CAR *current = head;
	int i = 0;
	puts("Enter info about the cars:");
        while(current) {
                printf("\nCar %d: ", i + 1);
		puts("\nModel:");
		scanf("%s", current->model);
		puts("\nCountry:");
                scanf("%s", current->country);
		puts("\nYear of manufacturing:");
		scanf("%d", &current->date);
                assert(current->date > 0);
		puts("\nPrice of the model:");
		scanf("%d", &current->cost);
                assert(current->cost > 0);
		puts("\nCapacity of engine:");
		scanf("%d", &current->capacity);
                assert(current->capacity > 0);
                current = current->next;
                i++;
        }
	puts("Input finished.");
}

void output(const CAR *head)
{
        assert(head);
	int i = 0;
	while (head) {
	        puts("");
		printf("Info about car No %d", i + 1);
		printf("\nAdress of the current element: %p", head);
		printf("\nModel: %s", head->model);
                printf("\nCountry: %s", head->country);
                printf("\nYear of manufacturing: %d", head->date);
                printf("\nPrice of model: %d", head->cost);
                printf("\nCapacity of engine: %d", head->capacity);
		puts("");
                head = head->next;
                i++;
	}
}

CAR* search(const CAR *head, const char *asked_model)
{
        assert(head);
        assert(asked_model);
	int i = 0;
	while (head) {
		i = strcmp(head->model, asked_model);
		if (i == 0) {
		        return (CAR*)head;
		}
		head = head->next;
	}
	return NULL;
}

void edit (CAR* model_to_modify)
{
        assert(model_to_modify);
	// User should answer questions using 'y' and 'n' keys .
	if (!model_to_modify) {
		puts("Error: You want to modify a model that does not exist.");
		return;
	}
	char answer = '\0';
one:
        puts("Do you want to modify the name of the model? y/n");
	fflush(stdin);
	scanf("%c", &answer);
	if ((answer != 'y') && (answer != 'n')) {
                puts("Unknown answer, please try again:");
                goto one;
        }
	if (answer == 'y') {
		puts("Introduce the new name of this model:");
		fflush(stdin);
		scanf("%s", model_to_modify->model);
	}
two:
        puts("Do you want to modify the country of the model? y/n");
	fflush(stdin);
	scanf("%c", &answer);
	if ((answer != 'y') && (answer != 'n')) {
                puts("Unknown answer, please try again:");
                goto two;
        }
	if (answer == 'y') {
		puts("Introduce the new country of this model:");
		fflush(stdin);
		scanf("%s", model_to_modify->country);
	}
three:
        puts("Do you want to modify the capacity of engine of the model? y/n");
	fflush(stdin);
	scanf("%c", &answer);
	if ((answer != 'y') && (answer != 'n')) {
                puts("Unknown answer, please try again:");
                goto three;
        }
	if (answer == 'y') {
		puts("Introduce the new capacity of this model:");
		fflush(stdin);
		scanf("%d", &model_to_modify->capacity);
                assert(model_to_modify->capacity > 0);
	}
four:
        puts("Do you want to modify the price of this model? y/n");
	fflush(stdin);
	scanf("%c", &answer);
	if ((answer != 'y') && (answer != 'n')) {
                puts("Unknown answer, please try again:");
                goto four;
        }
	if (answer == 'y') {
		puts("Introduce the new price of this model:");
		fflush(stdin);
		scanf("%d", &model_to_modify->cost);
                assert(model_to_modify->cost > 0);
	}
five:
        puts("Do you want to modify the year of manufacturing of this model?"
             " y/n");
	fflush(stdin);
	scanf("%c", &answer);
	if ((answer != 'y') && (answer != 'n')) {
                puts("Unknown answer, please try again:");
                goto five;
        }
	if (answer == 'y') {
		puts("Introduce the new year of manufacturing of this model:");
		fflush(stdin);
		scanf("%d", &model_to_modify->date);
                assert(model_to_modify->date > 0);
	}
}

void swap(CAR *a, CAR *b)
{
        assert(a);
        assert(b);
	CAR *next_a = a->next;
        CAR *next_b = b->next;
        CAR t = { .date = 0};
	t = *a;
	*a = *b;
	*b = t;
	a->next = next_a;
	b->next = next_b;
}

void sort(CAR *head)
{
        assert(head);
	int n = list_length(head);
	CAR *one = NULL;
        CAR *two = NULL;
	for (int i = 0; i < n - 1; ++i) {
		one = head;
		two = head->next;
		for (int j = 0; j < n - i - 1; ++j) {
			if (one->cost > two->cost) {
				swap(one, two);
			}
			one = one->next;
			two = two->next;
		}
	}
	puts("List of cars sorted by price.");
}

void free_list(CAR **head)
{
        assert(head);
        assert(*head);
	CAR *c = NULL;
	while (*head) {
		c = *head;
		*head = (*head)->next;
		free(c);
		c = NULL;
	}
	*head = NULL;
	puts("Memory is free.");
}

void show_menu(void)
{
	puts("\t\t ___MENU___ ");
	puts("1. Create a new list of cars;");
	puts("2. Input the list of cars from the keyboard;");
	puts("3. Output the list of cars on the screen;");
	puts("4. Search a car by the name of the model;");
	puts("5. Edit some data about a car;");
	puts("6. Swap two cars;");
	puts("7. Sort the list of cars in ascending order by price;");
	puts("8. Destroy the existing list of cars;");
	puts("9. Exit the program.");
	puts("");
	puts("Select an operation to be performed ( type a number):");
}

int list_length(CAR *head)
{
        assert(head);
	int n = 0;
	while (head) {
		++n;
		head = head->next;
	}
	return n;
}

