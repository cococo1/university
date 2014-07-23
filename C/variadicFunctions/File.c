//
//  File.c
//  qasd21
//
//  Created by Maxim Chetrusca on 7/23/14.
//  Copyright (c) 2014 Maxim Chetrusca. All rights reserved.
//

#include <stdio.h>
#include <stdarg.h> //this is needed for variadic functions

// n - how many numbers
int sumNumbers(int n, ...); //variable number of parameters

int main(void) {
  printf("The sum is: %i \n", sumNumbers(4, 1, -3, 6, 5));
  printf("The sum is: %i \n", sumNumbers(8, 1, 2, 4, 4, 5, 6, 7, 8));
  return 0;
}

int sumNumbers(int n, ...) {
  int sum = 0;
  va_list ap; // stores all the arguments
  va_start(ap, n); // indicates after which argument (n) the optional ones start
  for (int i = 0; i < n; i++) {
    sum += va_arg(ap, int); // retrieve an opt. argument of type int
  }
  va_end(ap); //we're done
  return sum;
}
