#include <stdio.h>
#include <math.h>

int main ()
{ 
float a,b,c,dx,xin,xfin;
float F,x;
int i;

printf("Dati a,b,c , x initial , x final si pasul diviziunii :");
scanf("%f%f%f%f%f%f",&a,&b,&c,&xin,&xfin,&dx);
i=0;
x=xin;
printf("Rezultatele obtinute : \n");

while (x<=xfin) 
                         {
                          ++i;
                          if  ((x-2>0)&&(a==0)) 
                                                              {
                                                                F=(a+log(x))/sin(c) -b*b ;
                                                               }
                         else if  ((x-2<0)&&(a!=0))
                                                                   {
                                                                    F=(x-sin(x+1))/b ; 
                                                                   }
                         else   
                               {
                                 F=(a*x+c)/cos(2*x);
                               };
                        printf("%i. x=%.2f , F=%.2f \n",i,x,F);
                       x=x+dx;
                       };


return 0 ;
}
