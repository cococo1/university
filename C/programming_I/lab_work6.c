// Copyright Max Chetrusca, modified Nov 11 2014
// lab_work6.c
// Programming I, 2010


#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
        char model[10];  // what model is the car
        char country[15];  // where is it produced
        int date;  // year of manufacturing
        int capacity;  // of the engine
        int cost;
}CAR;
// a small test function for our structure.
static void test_CAR(void);

// input from keyboard an array of n cars:
// car should not be NULL, n > 0
static void input(const int n, CAR *cars);
static void test_input(void);
// output the array of cars to the stdout:
// cars != NULL; n > 0;
static void output(const int n, const CAR *cars);
static void test_output(void);
// search for the wanted car:
// n >= 0; wanted != NULL; strlen(wanted) > 0; cars != NULL;
static int search(const int n, const char *wanted, const CAR *cars);
static void test_search(void);
// helper function for sort(). used only there.
static void internal_for(const int n, const int i, CAR *cars);
// sort cars by cost:
// n > 0; cars != NULL;
static void sort(const int n, CAR *cars);
static void test_sort(void);
// edit the data about the car k:
// k within range; n > 0; cars != NULL;
static void edit(const int n, const int k, CAR *cars);
static void test_edit(void);
// add a car at given pos:
// 0 <= pos <= n; n >0; cars != NULL;
static void add(const int pos, CAR **cars, int *n);
static void test_add(void);
// read cars from file, setting n as well:
// filename should be the name of an existing file,
// which can be opened.
static CAR* read_file(const char *filename, CAR *cars, int *n);
static void test_read_file(void);
static void test_all(void);
// helper function to get info about a car:
// n > 0; cars != NULL;
static void get_info(const int n, const CAR *cars);
static void test_get_info(void);
// find a car and edit its info:
// n > 0; cars != NULL;
static void edit_some_car(const int n, CAR *cars);
static void test_edit_some_car(void);
// find a car and delete it:
// n > 0; *cars != NULL;
static void delete_a_car(int *n, CAR **cars);
static void test_delete_a_car(void);
// write the contents to a file:
// n > 0; cars != NULL;
static void write_to_file(const int n, const CAR *cars);
static void test_write_to_file(void);
// helper function for main():
// cars != NULL;
static int switch_operation(const int operation, int *n, CAR **cars);
static void test_switch_operation(void);
// a helper function to discard all values which are currently stored in the
// input buffer:
static void fflush_stdin(void);
static void test_fflush_stdin(void);

int main(void)
{
        // test_all();
        // test_input();
        // test_edit();
        // test_fflush_stdin();
        // return 0;

        CAR *cars = NULL;
        int n = 0, operation = 0;
        while (1) {
                puts("Press any key to continue");
                puts("      Menu :");
                puts("1. Dynamic memory allocation");
                puts("2. Input array from keyboard");
                puts("3. Searching for a specific element");
                puts("4. Sorting");
                puts("5. Editing a specified element");
                puts("6. Adding a new element in the end ");
                puts("7. Deleting the specified element from array ");
                puts("8. Inserting a new element. ");
                puts("9. Writing the array to a file. ");
                puts("10.Reading the array from a file. ");
                puts("11.Output on the screen. ");
                puts("12.Clearing the allocated memory for array. ");
                puts("0. Exit from the program.");
                printf("\n \n ");
                fflush(stdout);
                puts("Enter the operation to be performed:");
                int fills = scanf("%d", &operation);
                assert(fills == 1);
                fflush_stdin();
                if (!switch_operation(operation, &n, &cars)) break;
        }
        return 0;
}

static void test_CAR(void)
{
        CAR c = { .date = 0};
        assert(c.capacity == 0);
        assert(strlen(c.model) == 0);
        assert(strlen(c.country) == 0);
        assert(c.cost == 0);
}

static void input(const int n, CAR *cars)
{
        assert(cars);
        assert(n > 0);
        for (int i = 0; i < n; ++i) {
                printf("\nGive the information about the %d car:\n", i+1);
                fflush(stdout);
                puts("Name of the model");
                scanf("%9s", cars[i].model);
                fflush_stdin();
                puts("Write the country");
                scanf("%14s", cars[i].country);
                fflush_stdin();
                puts("What is the year of manufacturing ?");
                int fills = scanf("%d", &cars[i].date);
                assert(fills = 1);
                fflush_stdin();
                assert(cars[i].date > 0);
                puts("What is the capacity of engine?");
                int fills1 = scanf("%d", &cars[i].capacity);
                assert(fills1 == 1);
                fflush_stdin();
                assert(cars[i].capacity > 0);
                puts("What is the cost ?");
                int fills2 = scanf("%d", &cars[i].cost);
                assert(fills2 == 1);
                fflush_stdin();
                assert(cars[i].cost > 0);
        }
}

static void test_input(void)
{
        int n = 0;
        puts("How many cars do you want?");
        scanf("%d", &n);
        fflush_stdin();
        assert(n > 0);
        CAR *cars = (CAR*)calloc(n, sizeof(CAR));
        assert(cars);
        input(n, cars);
        output(n, cars);
        input(n, cars);
        output(n, cars);
        free(cars);
        cars = NULL;


        assert(strcmp("", "asd"));
}

static void output(const int n, const CAR *cars)
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
                fflush(stdout);
        }
}

static void test_output(void)
{
}

static int search(const int n, const char *wanted, const CAR *cars)
{
        assert(cars);
        assert(n > 0);
        assert(wanted);
        assert(strlen(wanted) > 0);
        for (int i = 0; i < n; ++i) {
                if (strcmp(cars[i].model, wanted) == 0) {
                        puts("Model found!");
                        return i;
                }
        }
        puts("Model not found.");
        return -1;
}

static void test_search(void)
{
}

static void internal_for(const int n, const int i, CAR *cars)
{
        assert(n > 0);
        assert(cars);
        assert(i >= 0);
        assert(i < n);
        CAR car = {.date = 0};
        for (int j = 0; j < n - i - 1; ++j) {
                if (cars[j].cost > cars[j + 1].cost) {
                        car = cars[j];
                        cars[j] = cars[j + 1];
                        cars[j + 1] = car;
                }
        }
}

static void sort(const int n, CAR *cars)
{
        assert(cars);
        assert(n > 0);
        for (int i = 0; i < n - 1; ++i) {
                internal_for(n, i, cars);
        }
}

static void test_sort(void)
{
}

static void edit(const int n, const int k, CAR *cars) {
        assert(cars);
        assert(n > 0);
        assert(k >= 0);
        assert(k < n);
        char ans = '\0';

        puts("Do you want to change the name of model? y/n");
        scanf("%c", &ans);
        fflush_stdin();
        if (ans == 'y') {
                puts("Introduce the new name of model:");
                scanf("%9s", cars[k].model);
                fflush_stdin();
        }
        puts("Do you want to change the country of model? y/n");
        scanf("%c", &ans);
        fflush_stdin();
        if (ans == 'y') {
                puts("Introduce the new name of country:");
                scanf("%14s", cars[k].country);
                fflush_stdin();
        }
        puts("Do you want to change the date of manufacturing of model? y/n");
        scanf("%c", &ans);
        fflush_stdin();
        if (ans == 'y') {
                puts("Introduce the new date of manufacturing:");
                int fills = scanf("%d", &cars[k].date);
                assert(fills == 1);
                fflush_stdin();
                assert(cars[k].date > 0);
        }
        puts("Do you want to change the capacity of manufacturing of model?"
             " y/n");
        scanf("%c", &ans);
        fflush_stdin();
        if (ans == 'y') {
                puts("Introduce the new capacity of the car:");
                int fills = scanf("%d", &cars[k].capacity);
                assert(fills == 1);
                fflush_stdin();
                assert(cars[k].capacity > 0);
        }
        puts("Do you want to change the cost of manufacturing of model? y/n");
        scanf("%c", &ans);
        fflush_stdin();
        if (ans == 'y') {
                puts("Introduce the new cost of car:");
                int fills = scanf("%d", &cars[k].cost);
                assert(fills == 1);
                fflush_stdin();
                assert(cars[k].cost > 0);
        }
}

static void test_edit(void)
{
        int n = 0;
        puts("How many cars do you need?");
        scanf("%d", &n);
        fflush_stdin();
        assert(n > 0);

        CAR *cars = (CAR*)calloc(n, sizeof(CAR));
        assert(cars);
        input(n, cars);
        edit_some_car(n, cars);
        output(n, cars);
        free(cars);
        cars = NULL;
}

static void add(const int pos, CAR **cars, int *n)
{
        assert(cars);
        assert(*cars);
        assert(*n > 0);
        assert(pos >= 0);
        assert(pos < (*n) + 1);
        (*n)++;
        *cars = (CAR*)realloc(*cars, (*n) * sizeof(CAR));
        assert(*cars);
        for (int i = (*n); i >= pos; --i) {
                (*cars)[i] = (*cars)[i - 1];
        }
        puts("Give the information about new car:");
        puts("Type the model");
        scanf("%9s", (*cars)[pos].model);
        fflush_stdin();
        puts("Write the country");
        scanf("%14s", (*cars)[pos].country);
        fflush_stdin();
        puts("Type the year of manufacturing with numbers ");
        int fills = scanf("%d", &(*cars)[pos].date);
        assert(fills == 1);
        fflush_stdin();
        assert((*cars)[pos].date > 0);
        puts("What is the capacity of engine?");
        int fills1 = scanf("%d", &(*cars)[pos].capacity);
        assert(fills1 == 1);
        fflush_stdin();
        assert((*cars)[pos].capacity > 0);
        puts("What is the price?");
        int fills2 = scanf("%d", &(*cars)[pos].cost);
        assert(fills2 == 1);

        fflush_stdin();
        assert((*cars)[pos].cost > 0);
}

static void test_add(void)
{
}

static CAR* read_file(const char *filename, CAR *cars, int *n)
{
        assert(filename);
        FILE *f = NULL;
        f = fopen(filename, "r");
        assert(f);
        char model[10] = {'\0'};
        char country[10] = {'\0'};
        int date = 0;
        int capacity = 0;
        int cost = 0;
        int i = 0;
        while(5 == fscanf(f,
                          "%9s %14s %d %d %d",
                          model,
                          country,
                          &date,
                          &capacity,
                          &cost)) {
                assert(date > 0);
                assert(capacity > 0);
                assert(cost > 0);
                cars = (CAR*)realloc(cars, (i + 1) * sizeof(CAR));
                assert(cars);
                cars[i].model[0] = '\0';
                strncat(cars[i].model, model, strlen(model));
                cars[i].country[0] = '\0';
                strncat(cars[i].country, country, strlen(country));
                cars[i].date = date;
                cars[i].capacity = capacity;
                cars[i].cost = cost;
                i++;
        }
        puts("File successfully scaned.");
        (*n) = i;
        fclose(f);
        return cars;
}

static void test_read_file(void)
{
}

static void test_all(void)
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
        test_fflush_stdin();
        puts("All tests passed.");
}

static void get_info(const int n, const CAR *cars)
{
        assert(cars);
        assert(n > 0);
        char model[15] = {'\0'};
        puts("What model are you interested in ?");
        scanf("%9s", model);
        fflush_stdin();
        int k = search(n, model, (const CAR*)cars);
        if (k >= 0) {
                 printf("\nIt costs %d $.\n", cars[k].cost);
                 fflush(stdout);
        }
}

static void test_get_info(void)
{
}

static void edit_some_car(const int n, CAR *cars)
{
        assert(cars);
        assert(n > 0);
        char model[15] = {'\0'};
        puts("Introduce the model you want to edit:");
        scanf("%9s", model);
        fflush_stdin();
        int k = search(n, model, (const CAR*)cars);
        if (k >= 0) {
                edit(n, k, cars);
        }
}

static void test_edit_some_car(void)
{
}

static void delete_a_car(int *n, CAR **cars)
{
        assert(cars);
        assert(*cars);
        assert(n);
        assert(*n > 0);
        puts("Write what element you want to delete:");
        int k = 0;
        int fills = scanf("%d", &k);
        assert(fills == 1);
        fflush_stdin();
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

static void test_delete_a_car(void)
{
}

static void write_to_file(const int n, const CAR *cars)
{
        assert(cars);
        assert(n > 0);
        puts("What is the name of file ? ");
        char filename[15];
        scanf("%14s", filename);
        fflush_stdin();
        FILE *f = NULL;
        f = fopen(filename, "r");
        assert(!f);
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
                fflush(f);
        }
        fclose(f);
        puts("Done writting in file.");
}

static void test_write_to_file(void)
{
}

static int switch_operation(const int operation, int *n, CAR **cars)
{
        assert(cars);
        switch (operation) {
                case 1 : {
                        puts("For how many cars do you need memory ?");
                        int fills = scanf("%d", n);
                        assert(fills == 1);
                        fflush_stdin();
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
                        add(*n, cars, n);
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
                         int fills = scanf("%d", &k);
                        assert(fills == 1);
                        fflush_stdin();
                        add(k - 1, cars, n);
                        break;
                }
                case 9 : {
                        write_to_file(*n, *cars);
                        break;
                }
                case 10 : {
                        puts("Introduce the name of the file:");
                        char filename[10] = {'\0'};
                        scanf("%9s", filename);
                        fflush_stdin();
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

static void test_switch_operation(void)
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

static void fflush_stdin(void)
{
        int ch = 0;
        while((ch = getchar()) != '\n' && ch != EOF) /* clear buffer. */;
}

static void test_fflush_stdin(void)
{
        char c = '\0';
        puts("Type a char:");
        scanf("%c", &c);
        fflush_stdin();
        printf("the char: \"%c\"", c);
}
