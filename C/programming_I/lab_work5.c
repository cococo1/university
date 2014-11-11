// Copyright Max Chetrusca, modified Nov 11 2014
// lab_work5.c

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
        char *aux = NULL;
        const int kSize = 500;
        char **a = (char**)malloc(kSize * sizeof(char*));
        assert(a);
        for (int i = 0; i < kSize; ++i) {
                a[i] = NULL;
        }
        puts("Give the string");
        char s[1000] = {'\0'};
        fgets(s, kSize, stdin);
        a[0] = strtok(s, " ");
        int n = 0;
        while (a[n] != NULL) {
	        ++n;
                a[n] = strtok(NULL, " ");
        }
        for (int i = 0; i < n - 1; ++i) {
	        for (int j = 0; j < n - 1; ++j) {
		        if (strlen(a[j]) < strlen(a[j + 1])) {
                                aux = a[j];
		                a[j] = a[j + 1];
		                a[j + 1] = aux;
                        }
	        }
        }
        for (int i = 0; i < n; ++i) {
                puts(a[i]);
        }
        free(a);
        a = NULL;
        return 0;
}

