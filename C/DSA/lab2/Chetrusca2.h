//This is a header file to Chetrusca2.cpp
//It is created for some operations on a car-database
//Created : 19/02/2011
//Author : Chetrusca Maxim

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct CAR
{ 
// model of of car (ex: BMW); country - origin of model (Germany); 
// date - year of manufacturing; cost - price in $ of the car; 
// capacity - the capacity of engine ;
	char model[10], country[10];
	int date, cost, capacity;
	struct CAR * next; // for singly link lists
}CAR;
       
// HEADER FILES :
CAR* memory_allocation(int n); // Creation of the link-list, allocated dynamic. n - number of cars;
void input (CAR* head); // Inputing from keyboard ; head - pointer to the first element of link list;
void output (CAR* head);  // Outputting on the screen ;
CAR* search (CAR* head, char* asked_model); // Searches asked_model and returns the adress of it.
void edit (CAR* model_to_modify); // Asks user about all fields of the model_to_modify and modifies them if needed.
void swap(CAR *a, CAR* b); // Interchanges two elements, by given adresses. 
void sort (CAR *head); // Sorts the list of cars by price .
void free_list(CAR** head); // Deallocates the memory , frees it. 
void show_menu(void); // Function that generates the menu on the screen;
int list_length(CAR *head); //Returns the length of the list.

////////////////////////////////////////
//END OF FILE .
