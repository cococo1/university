// Copyright Max Chetrusca, modified style on Nov 10 2014
// lab_work3.c
// Programming I, 2010

#include <assert.h>
#include <float.h>
#include <stdio.h>

#define ANY_AND_NEWLINE "%*[^\n]%*c"

int main(void)
{
        float A[50][50] = {{0}}, max = -FLT_MAX;
        int n = 0, m = 0, k = 0;
        puts("Give the number of rows and columns:");
        scanf("%d%d"ANY_AND_NEWLINE, &n, &m);
        assert(n > 0);
        assert(m > 0);
        assert(n <= 48);
        assert(m <= 48);
        n = n + 2;
        m = m + 2;
        for (int i = 1; i < n - 1; ++i) {
                for (int j = 1; j < m - 1; ++j) {
                        printf("Give the element A[%d, %d]=", i, j);
                        fflush(stdout);
                        scanf("%f", &A[i][j]);
                        int ch = 0;
                        while((ch = getchar()) != '\n' && ch != EOF);
                        if (A[i][j] > max) {
                                max = A[i][j];
                        }
                }
        }

        for (int i = 0; i < n; ++i) {
                for (int j = 0; j < m; ++j) {
                        if ((i == 0) ||
                            (i == n - 1) ||
                            (j == 0) ||
                            (j == m - 1)) {
                                A[i][j] = max + 1;
                        }
                }
        }
        k = 0;
        for (int i = 0; i < n; ++i) {
                for (int j = 0; j < m; ++j) {
                        if ((A[i][j] < A[i - 1][j]) &&
                            (A[i][j] < A[i - 1][j + 1]) &&
                            (A[i][j] < A[i][j + 1]) &&
                            (A[i][j] < A[i + 1][j + 1]) &&
                            (A[i][j] < A[i + 1][j]) &&
                            (A[i][j] < A[i + 1][j - 1]) &&
                            (A[i][j] < A[i][j - 1]) &&
                            (A[i][j] < A[i - 1][j - 1])) {
                                ++k;
                        }
                }
        }
        printf("\n There are %d minima element(s).", k);
        fflush(stdout);
        return 0;
}

