// Copyright Max Chetrusca, modified Nov 11, 2014
// car_adt2.h
// Data Structures & Algorithms, 2011

// This is a header file to car_adt2.c
// It is created for some operations on a car-database
// Max Chetrusca, Feb 19, 2011


#ifndef DSA_CAR_ADT2_H_
#define DSA_CAR_ADT2_H_

typedef struct CAR { 
// model of of car (ex: BMW); country - origin of model (Germany); 
// date - year of manufacturing; cost - price in $ of the car; 
// capacity - the capacity of engine ;
	char model[10];
        char country[10];
	int date;
        int cost;
        int capacity;
	struct CAR *next;  // for singly link lists
}CAR;
 
// Creation of the link-list, allocated dynamic. n - number of cars;
CAR* allocate_memory(int n);
// Inputing from keyboard ; head - pointer to the first element of link list;
void input(CAR *head);
// Outputting on the screen ;
void output(const CAR *head);
 // Searches asked_model and returns the adress of it.
CAR* search(const CAR *head, const char *asked_model);
// Asks user about all fields of the model_to_modify and modifies them if
// needed.
void edit(CAR *model_to_modify);
;// Interchanges two elements, by given adresses. 
void swap(CAR *a, CAR *b);
// Sorts the list of cars by price .
void sort(CAR *head);
// Deallocates the memory , frees it. 
void free_list(CAR **head);
// Function that generates the menu on the screen;
void show_menu(void);
//Returns the length of the list.
int list_length(CAR *head);

#endif  // DSA_CAR_ADT2_H_

