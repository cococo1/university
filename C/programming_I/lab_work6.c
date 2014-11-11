// Copyright Max Chetrusca, modified Nov 11 2014
// lab_work6.c

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

// input from keyboard an array of n cars:
// car should not be NULL, n != 0
void input(CAR *cars, int n);
// output the array o cars to the stdout:
void output(CAR *cars, int n);
// search for the wanted car:
int search(CAR* cars, int n, char *wanted);
// sort cars by cost:
void sort(CAR* cars, int n);
// edit the data about the car k:
void edit(CAR* cars, int n, int k);
// add a car at given pos:
void add(CAR* cars, int *n, int pos);
// read cars from file, setting n as well:
CAR* read_file(CAR* cars, int *n, char *filename);

int main(void)
{
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
        	scanf("%d", &operation);
	        switch (operation) { 
		        case 1 : {
                                puts("For how many cars do you need "
                                     "memory ?");
			        scanf("%d", &n);
                                assert(n > 0);
			        cars = (CAR*)calloc(n, sizeof(CAR));
                                assert(cars);
			        break;
			}
		        case 2 : {
                                assert(cars);
			        input(cars, n);
			        break;
			}
		        case 3 : {
                                assert(cars);
			        model = malloc(15 * sizeof(char));
                                assert(model);
			        puts("What model are you interested "
                                     "in ?");
			        scanf("%s", model);
			        k = search(cars, n, model);
			        free(model);
			        if (k >= 0) {
                                        printf("\nIt costs %d $.\n",
                                               cars[k].cost);
			        }
			        break;
			}
		        case 4 : {
                                assert(cars);                 
				puts("Sorted the cars by price.");
				sort(cars, n);
				break;
			}
		        case 5 : {
                                assert(cars);
				model = (char*)malloc(15 * sizeof(char));
                                assert(model);
				puts("Introduce the model you want to edit:");
				scanf("%s", model);
				 k = search(cars, n, model);
				 free(model);
				 if (k >= 0) {
				        edit(cars, n, k);
				 }
				 break; 
			}
		        case 6 : {
                                assert(cars);
				add(cars, &n, n);
				break;
			}
		        case 7 : {
                                assert(cars);
				puts("Write what element you want to delete:");
				scanf("%d", &k);
				k--;
				for (int i = k; i < n - 1; ++i) {
				        cars[i] = cars[i + 1];
				}
				n--;
				cars = (CAR*)realloc(cars, n * sizeof(CAR));
                                assert(cars);
				break;
			}
		        case 8: {
                                assert(cars);
				puts("Give the possition of new element:");
				scanf("%d", &k);
				add(cars, &n, k - 1);
				break;
			}
		        case 9 : {
                                assert(cars);
				puts("What is the name of file ? ");
				scanf("%s", filename);
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
				break;
			}
		        case 10 : {
				puts("Introduce the name of the file:");
				scanf("%s", filename);
				cars = read_file(cars, &n, filename);
				break;
			}
		        case 11 : {
                                assert(cars);
				output(cars, n);
				break;
			}
		        case 12: {
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

void input(CAR *cars, int n)
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
	        puts("What is the capacity of engine?");
	        scanf("%d", &cars[i].capacity);
	        puts("What is the cost ?");
	        scanf("%d", &cars[i].cost);
	}
}

void output(CAR *cars, int n)
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

int search(CAR* cars, int n, char *wanted)
{
        assert(cars);
        assert(n > 0);
        assert(wanted);
        for (int i = 0; i < n; ++i) {
	        if (strcmp(cars[i].model, wanted)==0) { 
		        puts("Model found!"); 
		        return i;
	        }
        }
        puts("Model not found.");
        return -1;
}

void sort(CAR* cars, int n)
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

void edit(CAR* cars, int n, int k) {
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
	}
	puts("Do you want to change the capacity of manufacturing of model?"
             " y/n");
	fflush(stdin);
	scanf("%c", &ans);
	if (ans == 'y') {
		puts("Introduce the new capacity of the car:");
		scanf("%d", &cars[k].capacity);
	}
	puts("Do you want to change the cost of manufacturing of model? y/n");
	fflush(stdin);
	scanf("%c", &ans);
	if (ans == 'y') {
		puts("Introduce the new cost of car:");
	        scanf("%d", &cars[k].cost);
	}
}

void add(CAR* cars, int *n, int pos)
{
        assert(cars);
        assert(*n > 0);
        assert(pos >= 0);
        assert(pos < (*n) + 1);
	(*n)++;
	cars = (CAR*)realloc(cars, (*n) * sizeof(CAR));
        assert(cars);
	for (int i = (*n); i >= pos; --i) {
		cars[i] =cars[i - 1];
	}
	puts("Give the information about new car:");
	puts("Type the model");
	scanf("%s", cars[pos].model);
	puts("Write the country");
	scanf("%s", cars[pos].country);
	puts("Type the year of manufacturing with numbers ");
	scanf("%d", &cars[pos].date);
	puts("What is the capacity of engine?");
	scanf("%d", &cars[pos].capacity);
	puts("What is the price?");
	scanf("%d", &cars[pos].cost);
}

CAR* read_file(CAR* cars, int *n, char *filename)
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
        int i = 0;
	while (getc(f) != EOF) {
                i++;
		cars = (CAR*)realloc(cars, (i + 1)*sizeof(CAR));
	        assert(cars);	
		fscanf(f,
                       "%s %s %d %d %d",
                       cars[i].model,
                       cars[i].country,
                       &cars[i].date,
                       &cars[i].capacity,
                       &cars[i].cost);
	}
	puts("File successfully scaned.");
	(*n) = i;
	fclose(f);
	return cars;
}

