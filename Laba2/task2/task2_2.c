#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <math.h>

enum {
    ERR_INPUT = -1,
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

    printf("Enter the number of numbers for the geometric mean: ");
    scanf("%d", &count);

    if (count <= 0) {
        printf("The number of numbers must be positive.\n");
        return ERR_INPUT;
    }

    double numbers[count];

    printf("Enter %d real numbers:\n", count);
    for (int i = 0; i < count; i++) {
        printf("Number %d: ", i + 1);
        if (scanf("%lf", &numbers[i]) != 1){
            printf("Argument must be a number\n");
            return ERR_INPUT;
        }
    }
    double mean = geometricMean(count, numbers[0], numbers[1], numbers[2], numbers[3], numbers[4], numbers[5]);

    double base;
    int exp;
    printf("Enter the base for exponentiation: ");
    scanf("%lf", &base);
    printf("Enter the exponent: ");
    scanf("%d", &exp);

    double result = power(base, exp);

    printf("Geometric mean: %.2f\n", mean);
    printf("%.2f raised to the power of %d = %.2f\n", base, exp, result);
    
    return 0;
}
