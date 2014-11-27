// Copyright Max Chetrusca, modified Nov 12, 2014
// car_adt3.h
// Data Structures & Algorithms, 2011

// This is a header file to car_adt3.c
// It is created for some operations on a car linked list.
// Max Chetrusca, Mar 10, 2011

typedef struct CAR {
// model of of car (ex: BMW); country - origin of model (Germany);
// date - year of manufacturing; cost - price in $ of the car;
// capacity - the capacity of engine ;
        char model[10];
        char country[10];
        int date;
        int cost;
        int capacity;
        struct CAR *next; // for singly link lists
}CAR;

// THIS ADT OPERATES WITH A GLOBAL VARIABLE CAR *g_head, WHICH POINTS TO THE 
// HEAD OF THE LIST.  

// Creation of the link-list, memory allocated dynamically. n - number of cars;
int allocate_memory(const int n);
// Input from keyboard;
void input(void);
// Output on the screen;
void output(void);
// Searches asked_model and stores the adress of it in variable result.
// asked_model - stores the adress of the string of the name of car;
// returns 0 if model not found or list is empty, 1 if found;
int search(const char *asked_model, CAR **result);
// Asks user about all fields of the model_to_modify; modifies them if needed.
// returns 0 if pointer model_to_modify is empty, 1 otherwise;
int edit(CAR *model_to_modify);
// Returns the length of the list.
int list_length(void);
// Interchanges two elements of structure CAR type, by given adresses.
// returns 0 if elements do not exist;
int swap(CAR *a, CAR* b);
int sort(void);
// Inserts the new_element after_this_address and allocates memory for it;
//  returns 0 if something is wrong;
int insert(const CAR *new_element, CAR *after_this_address);
// Deletes the element with indicated adress.
int remove_car(CAR *adress);
// Records the list into a file: each row contain fields of an element
// separated by a space.
int write_to_file(const char *filename);
// Creates  link-list and store there the data from file.
int read_from_file(const char *filename);
// Deallocates the memory.
void free_list(void);
// returns the adress of the last element of link-list.
CAR *address_of_last(void);
// Divides the list into two; the second one will start with the adress head2;
// head2 - the adress of the head of the second link list;
void divide_list(const CAR *head2);
// Concatenates list that has the adress of the first element stored in head2
// to list that has the adress of the first element stored in global pointer
// head;
void concat_lists(const CAR *head2);
