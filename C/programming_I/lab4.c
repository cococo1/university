#include <stdio.h>
#include <stdlib.h>

float** allocation(int n,int m);
void input(float** A, int n, int m);
void output(float** A, int n , int m);
void random1(float** A ,int n, int m);
void clearing(float** A,int n);
void sort(float **A, int n , int m);


int main ()
{ float **A=NULL;
  int n,m,operation;

 while (1) { 
	      puts("\t Menu: \n 1.Memory allocation \n 2.Input the array      elements \n 3.Filling the array with random elements \n 4.Sorting the   elements from columns in decreasing order ");
	      puts("5.Output the array elements \n  6.Clearing the allocated memory \n 0. Exit the program \n \n Introduce the number of operation you want to be performed:");
	     scanf("%i",&operation);
	     switch (operation) {
		                   case 0 :  return 0; 
		                   case 1 : puts("Give n and m:");
                                        scanf("%i%i",&n,&m);
                                        A=allocation(n,m);
				                break;
		                   case 2 : input(A,n,m); break;
		                   case 3 : random1(A,n,m); break;
		                   case 4 : sort(A,n,m); break;
		                   case 5 : output(A,n,m); break;
		                   case 6 : clearing(A,n); break;
		                default : puts("Unknown command."); puts("Press any key"); 
	                        }
	
            }

 return 0;
}



float** allocation(int n,int m)
{ float **A=NULL;
  int i,j;
  puts("***Alocation.");
  A=(float**)malloc(n*sizeof(float*));
  if (A==NULL) 
{ puts("Memory was not allocated for case 1."); return NULL;                          }
 for (i=0; i<n; ++i)
       {
        A[i]=(float*)calloc(m,sizeof(float));
        if (A[i]==NULL) {  puts("Memory was not allocated for case 2.");    return NULL;            }
       }
 puts("Press any key");
 return A ;
}


void input(float** A, int n, int m)
{
int i,j;
 puts("***Inputing the elements:");
 for (i=0; i<n; ++i) {
     for (j=0; j<m; ++j) {
         printf("A[%i,%i]=",i,j);
         scanf("%f",&A[i][j]);
         puts("");
                         }
                  }
 puts("Press any key");
}




void output(float** A, int n , int m)
{int i,j;
 puts("\n ***Output:");
 for (i=0; i<n; ++i) {
     for (j=0; j<m; ++j) {
          printf(" %.0f ",A[i][j]); }
          puts("");  }
 puts("Press any key \n");
}

void random1(float **A,int n, int m)
{ int i,j;
  puts("***Filling the array with random elements.");
  for (i=0; i<n; ++i) {
      for (j=0; j<m; ++j) { A[i][j]=rand()%100; }
                      }
  puts("Press any key");
}

void clearing(float** A, int n)
{
  int i;
 for (i=0; i<n; ++i) {
     free(A[i]);     }      
 free(A);
 A=NULL;
 puts("***Memory deallocated. \n Press any key ");
}

void sort(float **A, int n , int m)
{int i,j,k; float aux; 
 puts("***Sorting the array's column in decreasing order.");
 for (k=0; k<m; ++k) {
     for (i=0; i<n-1; ++i) {
	   for (j=i+1; j<n; ++j) {
		  if (A[j][k]>A[i][k]) { aux=A[j][k];
		                         A[j][k]=A[i][k]; 
		                         A[i][k]=aux;
                                   }
	                         }
                           }
                     }
 puts("Press any key");
}
