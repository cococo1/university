#include <string.h>
#include <stdlib.h>
#include <stdio.h>



int main ()
{ char s[1000];
 int n,i,j;
 char *aux;
char **a=(char**)malloc(500*sizeof(char*));
if (!s) {puts("Memomory was not allocated. Case 1."); return 1;}
if (!a) {puts("Memomory was not allocated. Case 2."); return 1;}
for (i=0; i<500; ++i) {a[i]=(char*)malloc(sizeof(char*));
 if (!a[i]) {puts("Memomory was not allocated. Case 3."); return 1;}                            
 }

puts("Give the string");
gets(s);
a[0]=strtok(s," "); n=0;
while (a[n]!=NULL) {
	++n;
a[n]=strtok(NULL," ");
}
	
for (i=0; i<n-1; ++i) {
	for (j=0; j<n-1; ++j) {
		if (strlen(a[j])<strlen(a[j+1])) { aux=a[j];
		a[j]=a[j+1];
		a[j+1]=aux; }
	}}

for (i=0; i<n; ++i) {puts(a[i]); }
free(a);
return 0;
}
