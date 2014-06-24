//
//  main.c
//  
//
//  Created by Maxim Chetrusca on 3/9/14.
//
//

#include <stdio.h>
#include <complex.h> //C99
//#include <threads.h> //C11 ... no support :(

main(void)
{
    complex a = 1 + 3 * I;
    printf(" %f %fi",creal(a), cimag(a));
    
}