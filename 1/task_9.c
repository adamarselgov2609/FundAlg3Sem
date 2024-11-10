#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <math.h>

#define EPSILON 0.00000000001

#define SUCCESS 0
#define INVALID_ARGUMENTS 1
#define MEMORY_ERROR 2
#define FILE_ERROR 3
#define INVALID_NUMBER 4

int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int simplify_fraction(int *numerator, int *denominator) {
    int divisor = gcd(*numerator, *denominator);
    *numerator /= divisor;
    *denominator /= divisor;
    return SUCCESS;
}

int has_finite_representation(int denominator, int base, int *result) {
    if (denominator <= 0 || base <= 1) {
        return INVALID_ARGUMENTS;
    }

    int prime_factors[] = {2, 3, 5, 7};
    int prime_count = sizeof(prime_factors) / sizeof(prime_factors[0]);

    for (int i = 0; i < prime_count; i++) {
        while (denominator % prime_factors[i] == 0 && prime_factors[i] < base) {
            denominator /= prime_factors[i];
        }
    }

    *result = (denominator == 1);
    return SUCCESS;
}

int check_finite_representation(int base, int count, const double* numbers, int *results) {
    if (base <= 1 || count <= 0 || numbers == NULL || results == NULL) {
        return INVALID_ARGUMENTS;
    }

    for (int i = 0; i < count; i++) {
        double number = numbers[i];

        if (number <= 0 || number >= 1) {
            return INVALID_NUMBER;
        }

        int denominator = 1;
        while (fabs(number - floor(number)) > EPSILON) {
            number *= 10;
            denominator *= 10;
        }

        int numerator = (int)number;
        simplify_fraction(&numerator, &denominator);

        int status = has_finite_representation(denominator, base, &results[i]);
        if (status != SUCCESS) {
            return status;
        }
    }

    return SUCCESS;
}

int print_results(int count, const int* results, const double* numbers, int base) {
    for (int i = 0; i < count; i++) {
        if (results[i]) {
            printf("The number %.6f has a finite representation in base %d.\n", numbers[i], base);
        } else {
            printf("The number %.6f does not have a finite representation in base %d.\n", numbers[i], base);
        }
    }
    return SUCCESS;
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Usage: ./9.a <base> <decimal1> <decimal2> ...\n");
        return INVALID_ARGUMENTS;
    }

    int base = atoi(argv[1]);
    int count = argc - 2;

    double *numbers = (double *)malloc(count * sizeof(double));
    if (!numbers) {
        printf("Memory allocation error for numbers.\n");
        return MEMORY_ERROR;
    }

    int *results = (int *)malloc(count * sizeof(int));
    if (!results) {
        printf("Memory allocation error for results.\n");
        free(numbers);
        return MEMORY_ERROR;
    }

    for (int i = 0; i < count; i++) {
        numbers[i] = atof(argv[i + 2]);
    }

    int status = check_finite_representation(base, count, numbers, results);
    if (status != SUCCESS) {
        printf("An error occurred during calculation. Error code: %d\n", status);
    } else {
        print_results(count, results, numbers, base);
    }

    free(numbers);
    free(results);
    return status;
}