// Copyright Max Chetrusca, modified style Nov 10 2014
// lab_work1.c
// Programming I, 2010

#include <assert.h>
#include <math.h>
#include <stdio.h>

int main(void)
{ 
        float a = 0.0, b = 0.0, c = 0.0, dx = 0.0, x_in = 0.0, x_fin = 0.0;
        float F = 0.0, x = 0.0;
        int i = 0;
        printf("Dati a, b, c, x initial, x final si pasul diviziunii:\n");
        scanf("%f%f%f%f%f%f", &a, &b, &c, &x_in, &x_fin, &dx);
        x = x_in;
        assert(x > 0);
        assert(dx > 0);
        assert(x_fin > x_in);
        assert(b != 0);
        assert(c != 0);
        printf("Rezultatele obtinute:\n");
        while (x <= x_fin) {
                ++i;
                if ((x - 2.0 > 0.0) && (a == 0.0)) {
                        assert((sin(c)) != 0);
                        F = (a + log(x)) / sin(c) - b * b;
                } else if ((x - 2.0 < 0.0) && (a != 0.0)) {
                        F = (x - sin(x + 1.0)) / b; 
                } else {
                        assert(cos(2.0 * x) != 0);
                        F = (a * x + c) / cos(2.0 * x);
                }
                printf("%d. x=%.2f, F=%.2f\n", i, x, F);
                       x = x + dx;
        }
        return 0;
}

