#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <math.h>

typedef enum {
    ERR_INPUT = -1,
    OK = 2,
}Eode;


double geometricMean(int count, ...) {
    if (count <= 0) {
        return 0.0; 
    }
    
    double product = 1.0;
    va_list args;

    va_start(args, count);
    for (int i = 0; i < count; i++) {
        double num = va_arg(args, double);
        product *= num; 
    }
    va_end(args);
    
    return pow(product, 1.0 / count);
}


double power(double base, int exp) {
    if (exp == 0) {
        return 1.0; 
    } else if (exp < 0) {
        return 1.0 / power(base, -exp); 
    } else if (exp % 2 == 0) {
        double half = power(base, exp / 2);
        return half * half; 
    } else {
        return base * power(base, exp - 1); 
    }
}


int main() {
    int count;

    fprintf(stderr,"Enter the number of numbers for the geometric mean: ");
    scanf("%d", &count);

    if (count <= 0) {
        fprintf(stdout,"The number of numbers must be positive.\n");
        return ERR_INPUT;
    }

    double numbers[count];

    fprintf(stderr,"Enter %d real numbers:\n", count);
    for (int i = 0; i < count; i++) {
        fprintf(stderr,"Number %d: ", i + 1);
        if (scanf("%lf", &numbers[i]) != 1){
            fprintf(stdout,"Argument must be a number\n");
            return ERR_INPUT;
        }
    }
    double mean = geometricMean(count, numbers[0], numbers[1], numbers[2], numbers[3], numbers[4], numbers[5]);

    double base;
    int exp;
    fprintf(stderr,"Enter the base for exponentiation: ");
    if(scanf("%lf", &base) != 1 || exp < 0){
        fprintf(stdout,"Argument must be a number\n");
        return ERR_INPUT;
    }
    fprintf(stderr,"Enter the exponent: ");
    if (scanf("%d", &exp) != 1 || exp < 0){
        fprintf(stdout,"Argument must be a number\n");
        return ERR_INPUT;
    }

    double result = power(base, exp);

    fprintf(stdout,"GEOM:%.2f  EXP:%.2f\n", mean, result);
    
    return 0;
}
