#include <stdio.h>

int main ()
{
 int i,n,n1,B[50];
 float A[50];
 float min;
 printf("Enter the number of elements:\n");
 scanf("%i",&n);

 for (i=0; i<n; ++i) 
                     {
                      printf("Enter element number %i : ",i+1);
                      scanf("%f",&A[i]);
                      printf("\n");
                     };

 min=A[0];
 n1=0;

 for (i=1; i<n; ++i) 
                    {
                      if (A[i]<min) 
                                   {
                                    min=A[i]; 
                                   };
                     };

 for (i=0; i<n; ++i) 
                    {
                      
if (A[i]==min) 
                                    {
                                     B[n1]=i+1; ++n1; 
                                    };
                   };

 printf("Results :\n");
 printf("The value of the minimal elements is %.3f \n",min);
 printf("The quantity of the minimal elements is : %i \n",n1);
 printf("These are the positions of the minimal elements in array :\n");
 for (i=0; i<n1; ++i) 
                    {
                     printf("%i  ",B[i]); 
                    };


 return 0;
}

