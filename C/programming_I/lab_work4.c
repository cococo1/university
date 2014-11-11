// Copyright Max Chetrusca, modified style on Nov 10 2014
// lab_work4.c
// Programming I, 2010

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Allocates a n x m matrix of floats dynamically. 
// the caller has the responsibility to free the memory.
// n and m should not be zero.
float** allocate(const int n, const int m);
// Inputs from stdin the matrix a, 
// which has n rows and m columns.
// a should be allocated, n and m != 0.
void input(const int n, const int m, float **a);
// Outputs the matrix a on the screen:
void output(const int n, const int m, const float **a);
// Fill matrix with rand elements:
void fill_rand(const int n, const int m, float **a);
// Deallocate the memory of this matrix, set a to 0:
void clear(const int n, float **a);
// Sort matrix' columns in decreasing order:
void sort(const int n, const int m, float **a);

int main(void)
{
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
	        scanf("%d", &operation);
	        switch (operation) {
                        case 0 :  return 0; 
		        case 1 : puts("Give n and m:");
                                 scanf("%d%d", &n, &m);
                                 a = allocate(n, m);
				 break;
		        case 2 : input(n, m, a); 
                                 break;
		        case 3 : fill_rand(n, m, a);
                                 break;
		        case 4 : sort(n, m, a);
                                 break;
		        case 5 : output(n, m, (const float**)a);
                                 break;
		        case 6 : clear(n, a);
                                 break;
		        default : puts("Unknown command.");
                                  puts("Press any key"); 
	        }
        }
        return 0;
}

float** allocate(const int n, const int m)
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

void input(const int n, const int m, float **a)
{
        puts("***Inputing the elements:");
        assert(a);
        assert(n > 0);
        assert(m > 0);
        for (int i = 0; i < n; ++i) {
                assert(a[i]);
                for (int j = 0; j < m; ++j) {
                        printf("a[%d,%d]=", i, j);
                        scanf("%f", &a[i][j]);
                        puts("");
                }
        }
        puts("Press any key");
}

void output(const int n, const int m, const float **a)
{
        puts("\n ***Output:");
        assert(a);
        assert(n > 0);
        assert(m > 0);
        for (int i = 0; i < n; ++i) {
                assert(a[i]);
                for (int j = 0; j < m; ++j) {
                        printf(" %.0f ", a[i][j]);
                }
                puts("");
       }
        puts("Press any key \n");
}

void fill_rand(const int n, const int m, float **a)
{
        puts("***Filling the array with random elements.");
        assert(a);
        assert(n > 0);
        assert(m > 0);
        for (int i = 0; i < n; ++i) {
                assert(a[i]);
                for (int j = 0; j < m; ++j) {
                        srand(time(NULL));
                        a[i][j] = rand() % 100;
                }
        }
        puts("Press any key");
}

void clear(const int n, float **a)
{
        assert(a);
        assert(n > 0);
        for (int i = 0; i < n; ++i) {
                free(a[i]);
        }      
        free(a);
        a = NULL;
        puts("***Memory deallocated. \n Press any key ");
}

void sort(const int n, const int m, float **a)
{
        puts("***Sorting the array's column in decreasing order.");
        assert(a);
        assert(n > 0);
        assert(m > 0);
        float aux = 0.0; 
        for (int k = 0; k < m; ++k) {
                for (int i = 0; i < n - 1; ++i) {
                        for (int j = i + 1; j < n; ++j) {
                                if (a[j][k] > a[i][k]) {
                                        aux = a[j][k];
		                        a[j][k] = a[i][k]; 
		                        a[i][k] = aux;
                                }
                        }
                }
        }
        puts("Press any key");
}

