//This is a header file to Chetrusca3.c
//It is created for some operations on a car-database
//Last time modified: 10/03/2011
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
int memory_allocation(int n); // Creation of the link-list, allocated dynamic. n - number of cars;
void input (void); // Inputing from keyboard ;
void output (void);  // Outputting on the screen ;
int search (char* asked_model,CAR **result); // Searches asked_model and stores the adress of it in variable result.
// asked_model - pointer to char, stores the adress of the string;
// returns 0 if model not found or list is empty, 1 if found;
int edit (CAR* model_to_modify); // Asks user about all fields of the model_to_modify and modifies them if needed.
// returns 0 if pointer model_to_modify is empty , 1 otherwise;
int list_length(void); //Returns the length of the list.
int swap(CAR *a, CAR* b); // Interchanges two elements of structure CAR type, by given adresses.
// returns 0 if elements do not exist;
int sort (); // Sorts the list of cars by price . returns 0 if list is empty . Uses bubble sort.
int insert(CAR *after_this_adress,CAR new_element); //Inserts the new_element after_this_adress; returns 0 if something is wrong;
int deleting(CAR *adress); // Deletes the element with indicated adress.
int write_in_file( char* file_name); // Records the list into a file : each row contain fields of an element separated by a space.
int read_from_file(char* file_name); // Creates  link-list and store there the data from file.
void free_list(); // Deallocates the memory , frees it.
CAR* adress_of_last(void); // returns the adress of the last element of link-list.
void divide_list(CAR* head2); // Divides the list into two; the second one will start with the adress head2;
// head2- the adress of the head of the second link list ;
void concat_lists(CAR* head2); // Concatenates list that has the adress of the first element stored in head2 to list that has the adress
// of the first element stored in global pointer head;

//---------------------------------------------------
//END OF FILE .//////////////////////////////////////
