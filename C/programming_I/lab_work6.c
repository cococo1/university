// Copyright Max Chetrusca, modified Nov 11 2014
// lab_work6.c
// Programming I, 2010

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
        char model[10];
	char country[15];
	int date;
	int capacity;
	int cost;
}CAR;
void test_CAR(void);

// input from keyboard an array of n cars:
// car should not be NULL, n != 0
void input(const int n, CAR *cars);
void test_input(void);
// output the array o cars to the stdout:
void output(const int n, const CAR *cars);
void test_output(void);
// search for the wanted car:
int search(const int n, const char *wanted, const CAR *cars);
void test_search(void);
// sort cars by cost:
void sort(const int n, CAR* cars);
void test_sort(void);
// edit the data about the car k:
void edit(const int n, const int k, CAR *cars);
void test_edit(void);
// add a car at given pos:
void add(const int pos, CAR* cars, int *n);
void test_add(void);
// read cars from file, setting n as well:
CAR* read_file(const char* filename, CAR* cars, int *n);
void test_read_file(void);
void test_all(void);
// helper function for main():
int switch_operation(const int operation, int *n, CAR **cars);
void test_switch_operation(void);
// helper function to get info about a car:
void get_info(const int n, const CAR *cars);
void test_get_info(void);
// find a car and edit its info:
void edit_some_car(const int n, CAR *cars);
void test_edit_some_car(void);
// find a car and delete it:
void delete_a_car(int *n, CAR **cars);
void test_delete_a_car(void);
// write the contents to a file:
void write_to_file(const int n, const CAR *cars);
void test_write_to_file(void);

int main(void)
{
        test_all();

        CAR *cars = NULL;
	int n = 0, operation = 0;
        while (1) { 
	        puts("Press any key to continue");
	        puts("      Menu :");
	        puts("1. Dynamic memory allocation");
	        puts("2. Input of array elements from keyboard");
	        puts("3. Searching the element in array ");
	        puts("4. Sorting of array");
                puts("5. Editing the element of array ");
	        puts("6. Adding a new element in the end ");
        	puts("7. Deleting the specified element from array ");
        	puts("8. Inserting a new element. ");
        	puts("9. Recording array elements in a file. ");
        	puts("10.Reading array elements from a file. ");
        	puts("11.Output of array elements to the screen. ");
        	puts("12.Clearing the memory allocated for array. ");
        	puts("0. Exit from the program.");
        	printf("\n \n ");
        	puts("Enter the operation to be performed:");
        	scanf("%d", &operation);
                if (!switch_operation(operation, &n, &cars)) break;
	        
        } 
        return 0;
}

void test_CAR(void)
{
        CAR c = { .date = 0};
        assert(c.capacity == 0);
        assert(strlen(c.model) == 0);
        assert(strlen(c.country) == 0);
        assert(c.cost == 0);
}

void input(const int n, CAR *cars)
{
        assert(cars);
        assert(n > 0);
	for (int i = 0; i < n; ++i) { 
                printf("\nGive the information about the %d car:\n", i+1);
	        puts("Name of the model");
	        scanf("%s", cars[i].model);
	        puts("Write the country");
	        scanf("%s", cars[i].country);
	        puts("What is the year of manufacturing ?");
	        scanf("%d", &cars[i].date);
                assert(cars[i].date > 0);
	        puts("What is the capacity of engine?");
	        scanf("%d", &cars[i].capacity);
                assert(cars[i].capacity > 0);
	        puts("What is the cost ?");
	        scanf("%d", &cars[i].cost);
                assert(cars[i].cost > 0);
	}
}

void test_input(void)
{
        assert(strcmp("", "asd"));
}

void output(const int n, const CAR *cars)
{
        assert(cars);
        assert(n > 0);
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
                puts("Press any key for next model");
        }
}

void test_output(void)
{
}

int search(const int n, const char *wanted, const CAR *cars)
{
        assert(cars);
        assert(n > 0);
        assert(wanted);
        for (int i = 0; i < n; ++i) {
	        if (strcmp(cars[i].model, wanted) == 0) { 
		        puts("Model found!"); 
		        return i;
	        }
        }
        puts("Model not found.");
        return -1;
}

void test_search(void)
{
}

void sort(const int n, CAR *cars)
{ 
        assert(cars);
        assert(n > 0);
        CAR car = {.date = 0};
        for (int i = 0; i < n - 1; ++i) {
                for (int j = 0; j < n - i - 1; ++j) {
                        if (cars[j].cost > cars[j + 1].cost) {
				car = cars[j]; 
				cars[j] = cars[j + 1];
				cars[j + 1] = car;
			}
		}
	}
}

void test_sort(void)
{
}

void edit(const int n, const int k, CAR *cars) {
        assert(cars);
        assert(n > 0);
        assert(k >= 0);
        assert(k < n);
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
	        scanf("%d", &cars[k].date);
                assert(cars[k].date > 0);
	}
	puts("Do you want to change the capacity of manufacturing of model?"
             " y/n");
	fflush(stdin);
	scanf("%c", &ans);
	if (ans == 'y') {
		puts("Introduce the new capacity of the car:");
		scanf("%d", &cars[k].capacity);
                assert(cars[k].capacity > 0);
	}
	puts("Do you want to change the cost of manufacturing of model? y/n");
	fflush(stdin);
	scanf("%c", &ans);
	if (ans == 'y') {
		puts("Introduce the new cost of car:");
	        scanf("%d", &cars[k].cost);
                assert(cars[k].cost > 0);
	}
}

void test_edit(void)
{
}

void add(const int pos, CAR *cars, int *n)
{
        assert(cars);
        assert(*n > 0);
        assert(pos >= 0);
        assert(pos < (*n) + 1);
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
	scanf("%d", &cars[pos].date);
        assert(cars[pos].date > 0);
	puts("What is the capacity of engine?");
	scanf("%d", &cars[pos].capacity);
        assert(cars[pos].capacity > 0);
	puts("What is the price?");
	scanf("%d", &cars[pos].cost);
        assert(cars[pos].cost > 0);
}

void test_add(void)
{
}

CAR* read_file(const char *filename, CAR *cars, int *n)
{
        assert(cars);
        assert(*n > 0);
        assert(filename);
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
	while (!feof(f)) {
                i++;
		cars = (CAR*)realloc(cars, (i + 1) * sizeof(CAR));
	        assert(cars);	
		int filled = fscanf(f,
                                    "%s %s %d %d %d",
                                    cars[i].model,
                                    cars[i].country,
                                    &cars[i].date,
                                    &cars[i].capacity,
                                    &cars[i].cost);
                if (filled < 5) {
                        cars = (CAR*)realloc(cars, i * sizeof(CAR));
                        break;
                }
                assert(cars[i].date > 0);
                assert(cars[i].capacity > 0);
                assert(cars[i].cost > 0);
	}
        
	puts("File successfully scaned.");
	(*n) = i;
	fclose(f);
	return cars;
}

void test_read_file(void)
{
}

void test_all(void)
{
        puts("Starting tests:");
        test_CAR();
        test_input();
        test_output();
        test_search();
        test_sort();
        test_edit();
        test_add();
        test_read_file();
        test_switch_operation();
        test_get_info();
        test_edit_some_car();
        test_delete_a_car();
        test_write_to_file();
        puts("All tests passed.");
}

void get_info(const int n, const CAR *cars)
{
        assert(cars);
        assert(n > 0);
        char model[15] = {'\0'};
        puts("What model are you interested in ?");
	scanf("%s", model);
        int k = search(n, model, (const CAR*)cars);
        if (k >= 0) {
                 printf("\nIt costs %d $.\n", cars[k].cost);
        }
}

void test_get_info(void)
{
}

void edit_some_car(const int n, CAR *cars)
{
        assert(cars);
        assert(n > 0);
        char model[15] = {'\0'};
	puts("Introduce the model you want to edit:");
	scanf("%s", model);
        int k = search(n, model, (const CAR*)cars);
	if (k >= 0) {
	        edit(n, k, cars);
	}
}

void test_edit_some_car(void)
{
}

void delete_a_car(int *n, CAR **cars)
{
        assert(cars);
        assert(*cars);
        assert(n > 0);
	puts("Write what element you want to delete:");
        int k = 0;
	scanf("%d", &k);
        assert(k > 0);
        assert(k < *n);
	k--;
	for (int i = k; i < *n - 1; ++i) {
	        (*cars)[i] = (*cars)[i + 1];
	}
	(*n)--;
	*cars = (CAR*)realloc((*cars), (*n) * sizeof(CAR));
        assert(cars);
}

void test_delete_a_car(void)
{
}

void write_to_file(const int n, const CAR *cars)
{
        assert(cars);
        assert(n > 0);
	puts("What is the name of file ? ");
        char filename[15];
	scanf("%s", filename);
        FILE *f = NULL;
	f = fopen(filename, "w");
        assert(f);
	for (int i = 0; i < n; ++i) {
        	fprintf(f,
                        "%s %s %d %d %d\n",
                        cars[i].model,
                        cars[i].country,
                        cars[i].date,
                        cars[i].capacity,
                        cars[i].cost);
        }
	fclose(f);
	puts("Done writting in file.");
}

void test_write_to_file(void)
{
}

int switch_operation(const int operation, int *n, CAR **cars)
{
        assert(cars);
        switch (operation) { 
	        case 1 : {
                        puts("For how many cars do you need memory ?");
                        scanf("%d", n);
                        assert(*n > 0);
                        *cars = (CAR*)calloc(*n, sizeof(CAR));
                        assert(*cars);
                        break;
		}
	        case 2 : {
                        assert(*cars);
	                input(*n, *cars);
                        break;
		}
	        case 3 : {
                        get_info(*n, *cars);
			break;
		}
		case 4 : {
                        assert(*cars);                 
			puts("Sorted the cars by price.");
			sort(*n, *cars);
			break;
		}
		case 5 : {
                        edit_some_car(*n, *cars);
		        break; 
		}
		case 6 : {
                        assert(*cars);
		        add(*n, *cars, n);
			break;
		}
		case 7 : {
                        delete_a_car(n, cars);
                        break;
		}
		case 8 : {
                        assert(*cars);
		        puts("Give the possition of new element:");
                        int k = 0;
	 		scanf("%d", &k);
			add(k - 1, *cars, n);
			break;
		}
		case 9 : {
                        write_to_file(*n, *cars);
                        break;
		}
		case 10 : {
		        puts("Introduce the name of the file:");
                        char filename[10] = {'\0'};
			scanf("%s", filename);
			*cars = read_file(filename, *cars, n);
			break;
		}
		case 11 : {
                         assert(*cars);
		         output(*n, (const CAR*)*cars);
			 break;
		}
	        case 12: {
		        *cars = (CAR*)realloc(*cars, 0);
                        *cars = NULL;
			puts("Memory deallocated.");
			break;
		}
		case 0 : {
			return 0; 
		}
                default : {
		        puts("Unknown command.");
		}
        }
        return 1;
}

void test_switch_operation(void)
{
        int n = 0;
        CAR *cars = NULL;
        assert(switch_operation(1, &n, &cars));
        assert(switch_operation(2, &n, &cars));
        assert(switch_operation(3, &n, &cars));
        assert(switch_operation(4, &n, &cars));
        assert(switch_operation(5, &n, &cars));
        assert(switch_operation(6, &n, &cars));
        assert(switch_operation(7, &n, &cars));
        assert(switch_operation(8, &n, &cars));
        assert(switch_operation(9, &n, &cars));
        assert(switch_operation(10, &n, &cars));
        assert(switch_operation(12, &n, &cars));
        assert(switch_operation(13, &n, &cars));
        assert(!switch_operation(0, &n, &cars));
}

