// Copyright Max Chetrusca, modified Nov 11, 2014
// car_adt_test.c
// Data Structures & Algorithms, 2011

// An ADT, contains CAR structure, and some functions. 

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "car_adt.h" 

void test_input(void);
void test_output(void);
void test_search(void);
void test_sort(void);
void test_edit(void);
void test_add(void);
void test_read(void);

int main(void)
{
        puts("Starting tests:");
        test_input();
        test_output();
        test_search();
        test_sort();
        test_edit();
        test_add();
        test_read();
        puts("All tests passed.");

        CAR *cars = NULL;
	char *model = NULL;
	int n = 0, k = 0, operation = 0;
        char filename[30] = {'\0'};
	FILE *f = NULL;
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
	        scanf("%i", &operation);
	        switch (operation) { 
	                case 1 : {
	        	        puts("For how many cars do you need memory ?");
	        		scanf("%i", &n);
	        		cars = (CAR*)calloc(n, sizeof(CAR));
                                assert(cars);
	        		break;
	        	}
	        	case 2 : {
	        	        input(n, cars);
	        		 break;
	        	}
	        	case 3 : {
	        		model = (char*)malloc(15 * sizeof(char));
                                assert(model); 
	        		puts("What model are you interested in ?");
	        	        scanf("%s", model);
	        	        k = search(n, model, cars);
	        		free(model);
	        		if (k >= 0) {
	        			 printf("\nIt costs %i $.\n",
                                                cars[k].cost);
	        		}
	        	        break;
	        	}
	        	case 4 : {
	        	        puts("Sorted the cars by price.");
	        		sort(n, cars);
	        		break;
	        	}
	        	case 5 : {
	        		model = (char*)malloc(15 * sizeof(char));
                                assert(model);
	        		puts("Introduce the model you want to edit:");
	        		scanf("%s", model);
	        	        k = search(n, model, cars);
	        		free(model);
	        		if (k >= 0) {
	        		        edit(n, k, cars);
	        		}
	        		break; 
	        	}
	        	case 6 : {
	        		add(n, cars, &n);
	        		break;
	        	}
	        	case 7 : {
	        		puts("Write what element you want to delete:");
	        		scanf("%i", &k);
	        		k--;
	        		for (int i = k; i < n - 1; ++i) {
	        		        cars[i] = cars[i +1];
	        	        }
	        		n--;
	        		cars = (CAR*)realloc(cars, n * sizeof(CAR));
                                assert(cars);
	        		break;
	        	}
	        	case 8: {
	        	        puts("Give the possition of new element:");
	        		scanf("%i", &k);
	        		add(k - 1, cars, &n);
	        		break;
	        	}
	        	case 9 : {
	        		puts("What is the name of file ? ");
	        		scanf("%s", filename);
	        		f = fopen(filename, "w");
                                assert(f);
	        		for (int i = 0; i < n; ++i) {
	        		        fprintf(f,
                                                "%s %s %i %i %i\n",
                                                cars[i].model,
                                                cars[i].country,
                                                cars[i].date,
                                                cars[i].capacity,
                                                cars[i].cost);
	        		}
	        		fclose(f);
	        		puts("Done writting in file.");
	        		break;
	        	}
	        	case 10 : {
	        		puts("Introduce the name of the file:");
	        		scanf("%s", filename);
	        		cars = read(filename, cars, &n);
	        		break;
	        	}
	        	case 11 : {
	        		output(n, cars);
	        		break;
	        	}
	        	case 12 : {
	        		cars = (CAR*)realloc(cars, 0);
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
        }
	return 0;
}

void test_input(void)
{
}

void test_output(void)
{
}

void test_search(void)
{
}

void test_sort(void)
{
}

void test_edit(void)
{
}

void test_add(void)
{
}

void test_read(void)
{
}

