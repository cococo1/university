// Copyright Max Chetrusca, modified Nov 11, 2014
// car_adt2_test.c
// Data Structures & Algorightms, 2011

// A program for performing some operations upon a car database.
// Uses singly link-lists.
// Max Chetrusca, Feb 19, 2011

#include <stdio.h>
#include <stdlib.h>

#include "car_adt2.h"

int main(void)
{
        CAR* list_of_cars = NULL;
        CAR  *p1 = NULL;
        CAR  *p2 = NULL;
	char name[20] = {'\0'};
        char answer = '\0';
        char name2[20] = {'\0'};
        int n  = 0;
        int operation = 0;
	while (1) {
		show_menu();
		fflush(stdin);
		scanf("%s", name);
		operation = strtol(name, NULL, 10);
		switch (operation) {
		        case 1 : {
		                if (list_of_cars) {
label_1:
                                       puts("List already exist. Do you want "
                                            "to destroy it and create new one"
                                            "? y/n");
	                               fflush(stdin);
	                               scanf("%c", &answer);
	                               if ((answer != 'y') && (answer != 'n')) {
                                               puts("Invalid answer. Please, "
                                                    "try again:");
                                                goto label_1;
                                        }
		        		if (answer == 'y') {
                                                free_list(&list_of_cars);
                                        } else {
                                                goto label_2;
                                        }
		        	}
		        	puts("Give the number of cars:");
		        	scanf("%i", &n);
		                list_of_cars = allocate_memory(n);
label_2:	                puts("Press any key to continue;");
		        	break;
		        }
		        case 2: {
		        	input(list_of_cars);
		        	break;
		        }
		        case 3: {
		        	output(list_of_cars);
		        	break;
		        }
		        case 4: {
		        	if (!list_of_cars) {
                                        puts("List is empty."); 
                                        break;
                                }
		        	puts("Give the name of model of car you want "
                                     "to search:");
		        	scanf("%s", name);
		        	p1 = search(list_of_cars, name);
		        	puts("Model found! Here is the info about it:");
		        	printf("Model: %s \n", p1->model);
		        	printf("Country: %s \n", p1->country);
		        	printf("Capacity of engine: %i \n",
                                       p1->capacity);
		        	printf("Year of manufacturing: %i \n",
                                       p1->date);
		        	printf("Price: %i \n", p1->cost);
		        	p1 = NULL;
		        	break;
		        }
		        case 5: {
		        	if (!list_of_cars) {
                                        puts("List is empty.");
                                        break;
                                }
		        	puts("Introduce the name of model you want "
                                     "to edit:");
		        	scanf("%s", name);
		        	p1 = search(list_of_cars, name);
		        	if (!p1) {
                                        puts("Such a car does not exist.");
                                        break;
                                }
		        	puts("Model found!");
		        	edit(p1);
		        	puts("Modifying complete.");
		        	break;
		        }
		        case 6: {
		        	if (!list_of_cars) {
                                        puts("List is empty.");
                                        break;
                                }
		        	puts("So, you want to swap two cars;");
		        	puts("Introduce the name of the first model "
                                     "to swap:");
		        	scanf("%s", name);
		        	p1 = search(list_of_cars, name);
		        	if (!p1) {
                                        puts("Such a car does not exist.");
                                        puts("Press any key to continue:");
                                        break;
                                }
		        	puts("Introduce the name of the second model "
                                     "to swap:");
		        	scanf("%s", name2);
		        	p2 = search(list_of_cars, name2);
		        	if (!p2) {
                                        puts("Such a car does not exist.");
                                        puts("Press any key to continue:");
                                        break;
                                }
		        	swap(p1, p2);
		        	puts("Cars swapped.");
		        	break;
		        }
		        case 7: {
		                sort(list_of_cars);
		        	break;
		        }
		        case 8: {
		        	puts("Are you sure you want to destroy the "
                                     "existing list ? y/n");
		        	fflush(stdin);
		        	scanf("%c", &answer);
		        	if ((answer != 'y') && (answer != 'n')) {
                                        puts("Invalid answer.");
                                }
		                if (answer == 'y') {
                                        free_list(&list_of_cars);
                                }
		        	break;
		        }
		        case 9 : {
		        	return 0;
		        }
		        default : {
		        	puts("Unknown command, please try again:");
		        }
	        }

        }
	return 0;
}

