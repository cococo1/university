#include <stdio.h>

int main ()
{
 float A[50][50],max;
 int i,j,n,m,k;

 puts("Give the number of rows and columns:");
 scanf("%i%i",&n,&m);
 n=n+2;
 m=m+2;

 max=0;
 for (i=1; i<n-1; ++i) {
                 for (j=1; j<m-1; ++j) {
                                 printf("Give the element A[%i, %i]=",i,j);
                                 scanf("%f",&A[i][j]);
                                 if (A[i][j]>max) {
                                                   max=A[i][j];
                                                  }
                                        }
                        }




 for (i=0;i<n;++i) {
             for (j=0; j<m; ++j) {
                  if ((i==0)||(i==n-1)||(j==0)||(j==m-1)) {
                                                            A[i][j]=max; 
                                                          }
                                 }
                   }



 k=0;
 for (i=0; i<n; ++i) {
                      for (j=0; j<m; ++j) {
                          if ((A[i][j]<A[i-1][j]) && 
                            (A[i][j]<A[i-1][j+1]) && 
                            (A[i][j]<A[i][j+1]) && 
                            (A[i][j]<A[i+1][j+1]) && 
                           (A[i][j]<A[i+1][j]) &&
                           (A[i][j]<A[i+1][j-1]) && 
                           (A[i][j]<A[i][j-1]) && 
                           (A[i][j]<A[i-1][j-1])) 
                           {
                             ++k;
                           };
                                          }
                     }

 printf("\n There are %i minimal element(s).",k);

 return 0;

}

