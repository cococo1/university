// Copyright Max Chetrusca, modified Nov 11, 2014
// car_adt_test.c
// Data Structures & Algorithms, 2011

// An ADT, contains CAR structure, and some functions. 

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "car_adt.h" 

static void test_all(void);
static void test_input(void);
static void test_output(void);
static void test_search(void);
static void test_sort(void);
static void test_edit(void);
static void test_add(void);
static void test_read(void);
static void search_case(const int n, const CAR *cars);
static void test_search_case(void);
static void edit_case(const int n, CAR *cars);
static void test_edit_case(void);
static void delete_case(int *n, CAR **cars);
static void test_delete_case(void);
static void write_to_file(const int n, const CAR *cars);
static void test_write_to_file(void);
static int switch_operation(const int operation, int *n, CAR **cars);
static void test_switch_operation(void);

int main(void)
{
        test_all();

        CAR *cars = NULL;
	int n = 0;
        int operation = 0;
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
                fflush(stdout);
	        puts("Enter the operation to be performed:");
	        scanf("%d", &operation);
                switch_operation(operation, &n, &cars);
	        
        }
	return 0;
}


static void test_all(void)
{
        puts("Starting tests:");
        test_input();
        test_output();
        test_search();
        test_sort();
        test_edit();
        test_add();
        test_read();
        test_search_case();
        test_edit_case();
        test_delete_case();
        test_write_to_file();
        test_switch_operation();
        puts("All tests passed.");
}

static void test_input(void)
{
}

static void test_output(void)
{
}

static void test_search(void)
{
}

static void test_sort(void)
{
}

static void test_edit(void)
{
}

static void test_add(void)
{
}

static void test_read(void)
{
}

static void search_case(const int n, const CAR *cars)
{
        assert(n > 0);
        assert(cars);
        char model[15] = {'\0'};
        puts("What model are you interested in ?");
        scanf("%s", model);
        int k = search(n, model, cars);
        if (k >= 0) {
                printf("\nIt costs %d $.\n", cars[k].cost);
                fflush(stdout);
        }       
}

static void test_search_case(void)
{
}

static void edit_case(const int n, CAR *cars)
{
        assert(n > 0);
        assert(cars);
        char model[15] = {'\0'};
        puts("Introduce the model you want to edit:");
        scanf("%s", model);
        int k = search(n, model, cars);
        if (k >= 0) {
                edit(n, k, cars);
        }
}

static void test_edit_case(void)
{
}

static void delete_case(int *n, CAR **cars)
{
        assert(n);
        assert((*n) > 0);
        assert(cars);
        assert(*cars);
        puts("Write what element you want to delete:");
        int k = 0;
	scanf("%d", &k);
        assert(k > 0);
        assert(k <= (*n));
        k--;
        for (int i = k; i < (*n) - 1; ++i) {
                (*cars)[i] = (*cars)[i + 1];
        }
        (*n)--;
        (*cars) = (CAR*)realloc((*cars), (*n) * sizeof(CAR));
        assert(*cars);
}

static void test_delete_case(void)
{
}

static void write_to_file(const int n, const CAR *cars)
{
        assert(n > 0);
        assert(cars);
        puts("What is the name of file ? ");
        char filename[15] = {'\0'};
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
                fflush(stdout);
	}
	fclose(f);
        puts("Done writting in file.");
}

static void test_write_to_file(void)
{
}


static int switch_operation(const int operation, int *n, CAR **cars)
{
        switch (operation) { 
                case 1 : {
                        puts("For how many cars do you need memory ?");
                        scanf("%d", n);
                        assert(*n > 0);
                        (*cars) = (CAR*)calloc(*n, sizeof(CAR));
                        assert(cars);
                        break;
	        }
	        case 2 : {
                        input(*n, *cars);
	                break;
	        }
	        case 3 : {
                        search_case(*n, *cars);
	        	break;
	        }
	        case 4 : {
	        	puts("Sorted the cars by price.");
	        	sort(*n, *cars);
	        	break;
	        }
	        case 5 : {
                        edit_case(*n, *cars);
	        	break; 
	        }
	        case 6 : {
	        	add(*n, cars, n);
	        	break;
	        }
	        case 7 : {
	                delete_case(n, cars);	
	        	break;
	        }
	        case 8: {
                        puts("Give the possition of new element:");
                        int k = 0;
                        scanf("%d", &k);
                        assert(k >= 0);
                        assert(k < *n);
	        	add(k - 1, cars, n);
	        	break;
	        }
	        case 9 : {
                        write_to_file(*n, *cars);
                        break;
	        }
                case 10 : {
                        puts("Introduce the name of the file:");
                        char filename[15] = {'\0'};
                        scanf("%s", filename);
                        *cars = read(filename, cars, n);
                        break;
                }
                case 11 : {
                        output(*n, *cars);
                        break;
	        }
	        case 12 : {
                        *cars = (CAR*)realloc((*cars), 0);
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
        CAR *cars = NULL;
        int n = 0;
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
        assert(switch_operation(11, &n, &cars));
        assert(switch_operation(12, &n, &cars));
        assert(!switch_operation(0, &n, &cars));
}

