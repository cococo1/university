// Copyright Max Chetrusca, Nov 12, 2014
// car_adt3.c
// Data Structures & Algorithms, 2011

// This file should be attached to car_adt3.h header file.
// Here is the definition of functions declared there.
// Max Chetrusca, Mar 10, 2011

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "car_adt3.h"

// A global variable used as pointer to first element of link list.
// defined in the main file.
extern CAR *g_head;

static void fflush_stdin(void)
{
        int ch = 0;
        while((ch = getchar()) != '\n' && ch != EOF) /* clear buffer; */;
}

int allocate_memory(const int n)
{
        assert(!g_head);
        assert(n > 0);
        CAR  *current = NULL;
        CAR *previous = NULL;
        g_head = (CAR*)malloc(sizeof(CAR));
        assert(g_head);
        g_head->model[0] = '\0';
        g_head->country[0] = '\0';
        g_head->date = 1;
        g_head->cost = 1;
        g_head->capacity = 1;
        g_head->next = NULL;
        for (int i = 0; i < n - 1; i++)
        {
                current = (CAR*)malloc(sizeof(CAR));
                assert(current);
                current->next = NULL;
                if (i == 0) {
                        g_head->next = current;
                } else {
                        previous->next = current;
                }
                previous = current;
        }
        return 1;
}

void input(void)
{
        assert(g_head);
        CAR *current = g_head;
        int i = 0;
        puts("Enter info about the cars:");
        while(current) {
                printf("\nCar %d: ", i + 1);
                puts("\nModel:");
                scanf("%9s", current->model);
                fflush_stdin();
                puts("\nCountry:");
                scanf("%9s", current->country);
                fflush_stdin();
                puts("\nYear of manufacturing:");
                int filled = scanf("%d", &current->date);
                assert(filled == 1);
                fflush_stdin();
                assert(current->date > 0);
                puts("\nPrice of the model:");
                filled = scanf("%d", &current->cost);
                assert(filled == 1);
                fflush_stdin();
                assert(current->cost > 0);
                puts("\nCapacity of engine:");
                filled = scanf("%d", &current->capacity);
                assert(filled == 1);
                fflush_stdin();
                assert(current->capacity > 0);
                current = current->next;
                i++;
        }
        puts("Input finished.");
}

void output(void)
{
        assert(g_head);
        int i = 0;
        CAR *current = g_head;
        while (current) {
                puts("");
                printf("Info about car No %d", i + 1);
                printf("\nAdress of the current element: %p", current);
                printf("\nAdress of the next element: %p", current->next);
                printf("\nModel: %s", current->model);
                printf("\nCountry: %s", current->country);
                printf("\nYear of manufacturing: %d", current->date);
                printf("\nPrice of model: %d", current->cost);
                printf("\nCapacity of engine: %d", current->capacity);
                puts("");
                current = current->next;
                i++;
        }
}

int search(const char *asked_model, CAR **result)
{
        assert(g_head);
        assert(asked_model);
        assert(result);
        int i = 0;
        CAR *current = g_head;
        while (current) {
                i = strcmp(current->model, asked_model);
                if (i == 0) {
                        *result = current;
                        return 1;
                }
                current = current->next;
        }
        return 0;
}

int edit(CAR *model_to_modify)
{
        assert(model_to_modify);
        char answer = '\0';
        //User should answer questions using 'y' and 'n' keys .
one:
        puts("Do you want to modify the name of the model? y/n");
        scanf("%c", &answer);
        fflush_stdin();
        if ((answer != 'y') && (answer != 'n')) {
                puts("Unknown answer, please try again:");
                goto one;
        }
        if (answer == 'y') {
                puts("Introduce the new name of this model:");
                scanf("%9s", model_to_modify->model);
                fflush_stdin();
        }
two:
        puts("Do you want to modify the country of the model? y/n");
        scanf("%c", &answer);
        fflush_stdin();
        if ((answer != 'y') && (answer != 'n')) {
                puts("Unknown answer, please try again:");
                goto two;
        }
        if (answer == 'y') {
                puts("Introduce the new country of this model:");
                scanf("%9s", model_to_modify->country);
                fflush_stdin();
        }
three:
        puts("Do you want to modify the capacity of engine of the model? y/n");
        scanf("%c", &answer);
        fflush_stdin();
        if ((answer != 'y') && (answer != 'n')) {
                puts("Unknown answer, please try again:");
                goto three;
        }
        if (answer == 'y') {
                puts("Introduce the new capacity of this model:");
                int filled = scanf("%d", &model_to_modify->capacity);
                assert(filled == 1);
                fflush_stdin();
                assert(model_to_modify->capacity > 0);
        }
four:
        puts("Do you want to modify the price of this model? y/n");
        scanf("%c", &answer);
        fflush_stdin();
        if ((answer != 'y') && (answer != 'n')) {
                puts("Unknown answer, please try again:");
                goto four;
        }
        if (answer == 'y') {
                puts("Introduce the new price of this model:");
                int filled = scanf("%d", &model_to_modify->cost);
                assert(filled == 1);
                fflush_stdin();
                assert(model_to_modify->cost > 0);
        }
five:
        puts("Do you want to modify the year of manufacturing of this model? "
             "y/n");
        scanf("%c", &answer);
        fflush_stdin();
        if ((answer != 'y') && (answer != 'n')) {
                puts("Unknown answer, please try again:");
                goto five;
        }
        if (answer == 'y') {
                puts("Introduce the new year of manufacturing of this model:");
                int filled = scanf("%d", &model_to_modify->date);
                assert(filled == 1);
                fflush_stdin();
                assert(model_to_modify->date > 0);
        }
        return 1;
}

int list_length(void)
{
        int n = 0;
        CAR *current = g_head;
        while (current) {
                ++n;
                current = current->next;
        }
        return n;
}

int swap(CAR *a, CAR* b)
{
        assert(a);
        assert(b);
        CAR *next_a = NULL;
        CAR *next_b = NULL;
        CAR t = { .date = 1};
        next_a = a->next;
        next_b = b->next;
        t = *a;
        *a = *b;
        *b = t;
        a->next = next_a;
        b->next = next_b;
        return 1;
}

static void internal_for(const int n, const int i, CAR *one, CAR *two)
{
        for (int j = 0; j < n - i - 1; ++j) {
                if (one->cost > two->cost) {
                        swap(one, two);
                }
                one = one->next;
                two = two->next;
        }
}

int sort(void)
{
        assert(g_head);
        int n = 0;
        CAR *one = NULL, *two = NULL, *current = g_head;
        n = list_length();
        for (int i = 0; i < n - 1; ++i) {
                one = current;
                two = current->next;
                internal_for(n, i, one, two);
        }
        return 1;
}

int insert(const CAR *new_element, CAR *after_this_address)
{
        assert(after_this_address);
        assert(new_element);
        CAR *current = NULL;
        current = (CAR*)malloc(sizeof(CAR));
        assert(current);
        current->next = after_this_address->next;
        after_this_address->next = current;
        current->capacity = new_element->capacity;
        current->cost = new_element->cost;
        current->model[0] = '\0';
        strncat(current->model, new_element->model, strlen(new_element->model));
        current->country[0] = '\0';
        strncat(current->country,
                new_element->country,
                strlen(new_element->country));
        current->date = new_element->date;
        return 1;
}

int remove_car(CAR *address)
{
        assert(g_head);
        assert(address);
        CAR *p = NULL;
        if (g_head == address) {
                p = g_head;
                g_head = g_head->next;
                free(p);
                p = NULL;
                return 1;
        }
        p = g_head;
        while ((p->next != address) && p) {
                p = p->next;
        }
        assert(p);
        p->next = address->next;
        free(address);
        address = NULL;
        return 1;
}

int write_to_file(const char *filename)
{
        assert(filename);
        assert(g_head);
        FILE *f = NULL;
        CAR *current = NULL;
        current = g_head;
        // first assert that such a file does not exist:
        f = fopen(filename, "r");
        assert(!f);
        f = fopen(filename, "w");
        assert(f);
        while (current) {
                fprintf(f,
                        "%s %s %d %d %d\n",
                        current->model,
                        current->country,
                        current->capacity,
                        current->cost,
                        current->date);
                current = current->next;
        }
        fclose(f);
        return 1;
}

int read_from_file(const char *filename)
{
        assert(filename);
        int i = 0;
        FILE *f = NULL;
        CAR *c = NULL;
        CAR *previous = NULL;
        f = fopen(filename, "r");
        assert(f);
        char model[10] = {'\0'};
        char country[10] = {'\0'};
        int capacity = 0;
        int cost = 0;
        int date = 0;
        while(5 == fscanf(f,
                          "%9s %9s %d %d %d",
                          model,
                          country,
                          &capacity,
                          &cost,
                          &date)) {
                if (i == 0) {
                        g_head = (CAR*)malloc(sizeof(CAR));
                        assert(g_head);
                        c = g_head;
                        previous = g_head;
                } else {
                        c = (CAR*)malloc(sizeof(CAR));
                        assert(c);
                        previous->next = c;
                        previous = c;
                }
                c->next = NULL;
                c->model[0] = '\0';
                strncat(c->model, model, strlen(model));
                c->country[0] = '\0';
                strncat(c->country, country, strlen(country));
                c->capacity = capacity;
                c->cost = cost;
                c->date = date;
                ++i;
        }
        return 1;
}

void free_list(void)
{
        assert(g_head);
        CAR *c = NULL;
        while (g_head) {
                c = g_head;
                g_head = g_head->next;
                free(c);
                c = NULL;
        }
        g_head = NULL;
}

CAR* address_of_last(void)
{
        if (!g_head) return NULL;
        CAR *current = g_head;
        while (current->next) {
                current = current->next;
        }
        return current;
}

void divide_list(const CAR *head2)
{
        assert(g_head);
        assert(head2);
        CAR *current = g_head;
        if (g_head == head2) {
                g_head = NULL;
                return;
        }
        while (current->next != head2 && current) {
                current = current->next;
        }
        assert(current);
        current->next = NULL;
}

void concat_lists(const CAR* head2)
{
        assert(g_head);
        assert(head2);
        CAR *current = g_head;
        while (current->next) {
                current = current->next;
        }
        current->next = (CAR *)head2;
}
