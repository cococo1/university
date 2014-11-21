// Copyright Max Chetrusca, modified style on Nov 10 2014
// lab_work4.c
// Programming I, 2010

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ANY_AND_NEWLINE "%*[^\n]%*c"

// Allocates a n x m matrix of floats.
// the caller has the responsibility to free the memory.
// n and m should be greater than zero.
static float** allocate(const int n, const int m);
// test function for previous one:
static void test_allocate(void);
// Inputs from stdin the matrix a,
// which has n rows and m columns.
// a should be allocated, n and m > 0.
static void input(const int n, const int m, float **a);
static void test_input(void);
// Outputs the matrix a on the screen:
// a should be allocated; n, m > 0.
static void output(const int n, const int m, const float **a);
static void test_output(void);
// Fill matrix with rand elements:
// n,m > 0; *a != NULL.
static void fill_rand(const int n, const int m, float **a);
static void test_fill_rand(void);
// Deallocate the memory of this matrix, set a to NULL:
// n - nr. of rows
// *a != NULL; n > 0.
static void clear(const int n, float ***a);
static void test_clear(void);
// helper function for sorting - used only in the sort() function.
static void internal_for(const int i, const int k, const int n, float **a);
// Sort matrix' columns in decreasing order:
// n, m > 0; *a != NULL.
static void sort(const int n, const int m, float **a);
static void test_sort(void);
static void test_all(void);
// helper function for main();
static int switch_operation(const int operation, int *n, int *m, float ***a);
static void test_switch_operation(void);

int main(void)
{
        // test_input();
        // return 0;
        // test_all();

        float **a = NULL;
        int n = 0, m = 0, operation = 0;
        while (1) {
                puts("\t Menu: \n 1.Memory allocation \n 2.Input the array "
                     "elements \n 3.Filling the array with random elements \n "
                      "4.Sorting the   elements from columns in decreasing "
                      "order ");
	        puts(" 5.Output the array elements \n 6.Clearing the "
               "allocated memory \n 0.Exit the program \n \n Enter the "
               "number of operation you want to be performed:");
	        int fills = scanf("%d"ANY_AND_NEWLINE, &operation);
                assert(fills == 1);
                if (!switch_operation(operation, &n, &m, &a)) break;
        }
        return 0;
}

static float** allocate(const int n, const int m)
{
        puts("***alocation.");
        assert(n > 0);
        assert(m > 0);
        float **a = NULL;
        a = (float**)malloc(n * sizeof(float*));
        assert(a);
        for (int i = 0; i < n; ++i) {
                a[i] = (float*)calloc(m, sizeof(float));
                assert(a[i]);
                for (int j = 0; j < m; j++) {
                        a[i][j] = 0;
                }
        }
        puts("Press any key");
        return a;
}

static void test_allocate(void)
{
        float **a = allocate(2, 2);
        assert(a[1][1] == 0);
        clear(2, &a);
}

static void input(const int n, const int m, float **a)
{
        puts("***Inputing the elements:");
        assert(a);
        assert(*a);
        assert(n > 0);
        assert(m > 0);
        for (int i = 0; i < n; ++i) {
                assert(a[i]);
                for (int j = 0; j < m; ++j) {
                        printf("a[%d,%d]=", i, j);
                        fflush(stdout);
                        int fills = scanf("%f"ANY_AND_NEWLINE, &a[i][j]);
                        assert(fills == 1);
                        puts("");
                }
        }
        puts("Press any key");
}

static void test_input(void)
{
        float **a = allocate(2, 2);
        input(2, 2, a);
        output(2, 2, (const float**)a);
        clear(2, &a);
}

static void output(const int n, const int m, const float **a)
{
        puts("\n ***Output:");
        assert(a);
        assert(*a);
        assert(n > 0);
        assert(m > 0);
        for (int i = 0; i < n; ++i) {
                assert(a[i]);
                for (int j = 0; j < m; ++j) {
                        printf(" %.0f ", a[i][j]);
                        fflush(stdout);
                }
                puts("");
       }
        puts("Press any key \n");
}

static void test_output(void)
{
}

static void fill_rand(const int n, const int m, float **a)
{
        puts("***Filling the array with random elements.");
        assert(a);
        assert(n > 0);
        assert(m > 0);
        srand(time(NULL));
        for (int i = 0; i < n; ++i) {
                assert(a[i]);
                for (int j = 0; j < m; ++j) {
                        a[i][j] = rand() % 100;
                }
        }
        puts("Press any key");
}

static void test_fill_rand(void)
{
}

static void clear(const int n, float ***a)
{
        assert(*a);
        assert(**a);
        assert(n > 0);
        for (int i = 0; i < n; ++i) {
                free((*a)[i]);
        }
        free(*a);
        *a = NULL;
        puts("***Memory deallocated. \n Press any key ");
}

static void test_clear(void)
{
        float **a = allocate(2, 3);
        clear(2, &a);
        assert(a == NULL);
}

static void internal_for(const int i, const int k, const int n, float **a)
{
        assert(a);
        assert(*a);
        assert(i >= 0);
        assert(i < n);
        assert(k >= 0);
        assert(n > 0);
        float aux = 0.0;
        for (int j = i + 1; j < n; ++j) {
                if (a[j][k] > a[i][k]) {
                        aux = a[j][k];
		        a[j][k] = a[i][k];
		        a[i][k] = aux;
                }
        }
}

static void sort(const int n, const int m, float **a)
{
        puts("***Sorting the array's column in decreasing order.");
        assert(a);
        assert(*a);
        assert(n > 0);
        assert(m > 0);
        for (int k = 0; k < m; ++k) {
                for (int i = 0; i < n - 1; ++i) {
                        internal_for(i, k, n, a);
                }
        }
        puts("Press any key");
}

static void test_sort(void)
{
}

static void test_all(void)
{
        puts("Starting tests:");
        test_allocate();
        test_input();
        test_output();
        test_fill_rand();
        test_clear();
        test_sort();
        test_switch_operation();
        puts("All tests passed.");
}

static int switch_operation(const int operation, int *n, int *m, float ***a)
{
        switch (operation) {
                case 0 :  {
                        return 0;
                }
	        case 1 : {
                        puts("Give n and m:");
                        int fills = scanf("%d%d"ANY_AND_NEWLINE, n, m);
                        assert(fills == 2);
                        *a = allocate(*n, *m);
	        	break;
                }
	        case 2 : {
                        input(*n, *m, *a);
                        break;
                }
	        case 3 : {
                        fill_rand(*n, *m, *a);
                        break;
                }
	        case 4 : {
                        sort(*n, *m, *a);
                        break;
                }
	        case 5 : {
                        output(*n, *m, (const float**)*a);
                        break;
                }
	        case 6 : {
                        clear(*n, a);
                        break;
                }
	        default : {
                        puts("Unknown command.");
                        puts("Press any key");
                }
	 }
        return 1;
}

static void test_switch_operation(void)
{
        float** a = NULL;
        int n = 0;
        int m = 0;
        assert(switch_operation(1, &n, &m, &a));
        assert(switch_operation(2, &n, &m, &a));
        assert(switch_operation(3, &n, &m, &a));
        assert(switch_operation(4, &n, &m, &a));
        assert(switch_operation(5, &n, &m, &a));
        assert(switch_operation(6, &n, &m, &a));
        assert(!switch_operation(0, &n, &m, &a));
}
