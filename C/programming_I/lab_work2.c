// Copyright Max Chetrusca, modified syle on Nov 10 2014
// lab_work2.c
// Programming I, 2010

#include <assert.h>
#include <stdio.h>

int main(void)
{
        // n1 - number of minimal elements
        int n = 0, n1 = 0, b[50] = {0};
        float a[50] = {0.0};
        float min = 0.0;
        printf("Enter the number of elements:\n");
        scanf("%d", &n);
        assert(n > 0);
        assert(n <= 50);
        for (int i = 0; i < n; ++i) {
                printf("Enter element number %d: ", i+1);
                scanf("%f", &a[i]);
                printf("\n");
        }
        min = a[0];
        for (int i = 1; i < n; ++i) {
                if (a[i] < min) {
                        min = a[i]; 
                }
        }
        for (int i = 0; i < n; ++i) {
                if (a[i] == min) {
                        b[n1] = i + 1;
                        ++n1; 
                }
        }
        printf("Results :\n");
        printf("The value of the minimal elements is %.3f \n", min);
        printf("The quantity of the minimal elements is : %d \n", n1);
        printf("These are the positions of the minimal elements in array :\n");
        for (int i = 0; i < n1; ++i) {
                     printf("%d  ", b[i]); 
        }
 return 0;
}

