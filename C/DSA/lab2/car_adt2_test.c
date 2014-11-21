// TODO: Check this file for errors;
// TODO: Test everything;
// Copyright Max Chetrusca, modified Nov 11, 2014
// car_adt2_test.c
// Data Structures & Algorightms, 2011

// A program for performing some operations upon a car database.
// Uses singly link-lists.
// Max Chetrusca, Feb 19, 2011

#include <assert.h>
#include <stdio.h>

#include "car_adt2.h"

static void test_allocate_memory(void);
static void test_input(void);
static void test_output(void);
static void test_search(void);
static void test_edit(void);
static void test_swap(void);
static void test_sort(void);
static void test_free_list(void);
static void test_show_menu(void);
static void test_list_length(void);
static void test_all(void);
static void case_allocate(int *n, CAR **list_of_cars);
static void test_case_allocate(void);
static void case_search(const CAR *list_of_cars);
static void test_case_search(void);
static int switch_operation(const int operation, int *n, CAR **list_of_cars);
static void test_switch_operation(void);
static void show_menu(void);
static void fflush_stdin(void);
static void test_fflush_stdin(void);
static void case_edit(CAR *list_of_cars);
static void test_case_edit(void);
static void case_swap(CAR *list_of_cars);
static void test_case_swap(void);
static void case_destroy(CAR **list_of_cars);
static void test_case_destroy(void);

int main(void)
{
        test_all();

        CAR* list_of_cars = NULL;
        int n  = 0;
        int operation = 0;
	while (1) {
		show_menu();
		int filled = scanf("%d", &operation);
                assert(filled == 1);
                fflush_stdin();
                switch_operation(operation, &n, &list_of_cars);
        }
	return 0;
}

static void test_allocate_memory(void)
{
        CAR *head = allocate_memory(1);
        assert(head);
        free_list(&head);
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

static void test_edit(void)
{
}

static void test_swap(void)
{
        CAR a = { .date = 1};
        CAR b = { .date = 2};
        CAR a1 = a;
        CAR b1 = b;
        swap(&a, &b);
        assert(a.date == b1.date);
        assert(b.date == a1.date);
}

static void test_sort(void)
{
}

static void test_free_list(void)
{
        CAR *c = allocate_memory(3);
        free_list(&c);
        assert(c == NULL);
}

static void test_show_menu(void)
{
}

static void test_list_length(void)
{
        CAR *h = allocate_memory(4);
        assert(list_length(h) == 4);
        free_list(&h);
}

static void test_all(void)
{
        puts("Starting tests:");
        test_allocate_memory();
        test_input();
        test_output();
        test_search();
        test_edit();
        test_swap();
        test_sort();
        test_free_list();
        test_show_menu();
        test_list_length();
        test_case_allocate();
        test_case_search();
        test_switch_operation();
        test_fflush_stdin();
        test_case_edit();
        test_case_swap();
        test_case_destroy();

        puts("All tests passed.");
}

static void case_allocate(int *n, CAR **list_of_cars)
{
        assert(n);
        assert(list_of_cars);
        if (*list_of_cars) {
label_1:
                puts("List already exist. Do you want to destroy it and create"
                     "new one? y/n");
                char answer = '\0';
	        scanf("%c", &answer);
                fflush_stdin();
                if ((answer != 'y') && (answer != 'n')) {
                        puts("Invalid answer. Please, try again:");
                        goto label_1;
                }
                if (answer == 'y') {
                        free_list(list_of_cars);
                } else {
                        goto label_2;
                }
        }
        puts("Give the number of cars:");
        int filled = scanf("%i", n);
        assert(filled == 1);
        fflush_stdin();
        assert(*n > 0);
        *list_of_cars = allocate_memory(*n);
label_2:
        puts("Press any key to continue;");
}

static void test_case_allocate(void)
{
}

static void case_search(const CAR *list_of_cars)
{
        assert(list_of_cars);
        puts("Give the name of model of car you want to search:");
        char name[15] = {'\0'};
        scanf("%s", name);
        fflush_stdin();
        CAR *p1 = search(list_of_cars, name);
        puts("Model found! Here is the info about it:");
        printf("Model: %s \n", p1->model);
        printf("Country: %s \n", p1->country);
        printf("Capacity of engine: %i \n", p1->capacity);
        printf("Year of manufacturing: %i \n", p1->date);
        printf("Price: %i \n", p1->cost);
        fflush(stdout);
        p1 = NULL;
}

static void test_case_search(void)
{
}

static int switch_operation(const int operation, int *n, CAR **list_of_cars)
{
        assert(n);
        assert(*n > 0);
        assert(list_of_cars);
        switch (operation) {
                case 1 : {
	                case_allocate(n, list_of_cars);
		        break;
		}
		case 2: {
		        input(*list_of_cars);
		        break;
		}
		case 3: {
		        output(*list_of_cars);
		        break;
		}
		case 4: {
                        case_search(*list_of_cars);
		        break;
		}
		case 5: {
                        case_edit(*list_of_cars);
		        break;
	        }
		case 6: {
                        case_swap(*list_of_cars);
                        break;
		}
		case 7: {
		        sort(*list_of_cars);
		        break;
		}
		case 8: {
                        case_destroy(list_of_cars);
                        break;
                }
                case 9 : {
                        return 0;
                }
                default : {
                        puts("Unknown command, please try again:");
                }
        }
        return 1;
}

static void test_switch_operation(void)
{
}

static void show_menu(void)
{
	puts("\t\t ___MENU___ ");
	puts("1. Create a new list of cars;");
	puts("2. Input the list of cars from the keyboard;");
	puts("3. Output the list of cars on the screen;");
	puts("4. Search a car by the name of the model;");
	puts("5. Edit some data about a car;");
	puts("6. Swap two cars;");
	puts("7. Sort the list of cars in ascending order by price;");
	puts("8. Destroy the existing list of cars;");
	puts("9. Exit the program.");
	puts("");
	puts("Select an operation to be performed ( type a number):");
}

static void fflush_stdin(void)
{
        int ch = 0;
        while((ch = getchar()) != '\n' && ch != EOF) /* empty buffer */;
}

static void test_fflush_stdin(void)
{
}

static void case_edit(CAR *list_of_cars)
{
        assert(list_of_cars);
        puts("Introduce the name of model you want to edit:");
        char name[15] = {'\0'};
        scanf("%s", name);
        fflush_stdin();
        CAR *p1 = NULL;
	p1 = search(list_of_cars, name);
	if (!p1) {
                puts("Such a car does not exist.");
                return;
        }
        puts("Model found!");
        edit(p1);
	puts("Modifying complete.");
}

static void test_case_edit(void)
{
}

static void case_swap(CAR *list_of_cars)
{
        assert(list_of_cars);
        puts("So, you want to swap two cars;");
        puts("Introduce the name of the first model to swap:");
        char name[15] = {'\0'};
        scanf("%s", name);
        fflush_stdin();
        CAR *p1 = search(list_of_cars, name);
        if (!p1) {
                puts("Such a car does not exist.");
                puts("Press any key to continue:");
                return;
        }
        puts("Introduce the name of the second model to swap:");
        scanf("%s", name);
        fflush_stdin();
        CAR *p2 = search(list_of_cars, name);
	if (!p2) {
                puts("Such a car does not exist.");
                puts("Press any key to continue:");
                return;
        }
        swap(p1, p2);
        puts("Cars swapped.");
}

static void test_case_swap(void)
{
}

static void case_destroy(CAR **list_of_cars)
{
        assert(list_of_cars);
        assert(*list_of_cars);
        puts("Are you sure you want to destroy the existing list ? y/n");
        char answer = '\0';
        scanf("%c", &answer);
        fflush_stdin();
        if ((answer != 'y') && (answer != 'n')) {
                puts("Invalid answer.");
        }
        if (answer == 'y') {
                free_list(list_of_cars);
        }
}

static void test_case_destroy(void)
{
}
