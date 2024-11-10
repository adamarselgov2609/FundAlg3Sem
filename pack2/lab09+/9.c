#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <math.h>

#define EPSILON 0.00000000001

typedef enum {
    SUCCESS = 0,
    INVALID_ARGUMENTS = 1,
    MEMORY_ERROR = 2,
    FILE_ERROR = 3,
    INVALID_NUMBER = 4
} StatusCode;


int gcd(int a, int b) {
    while (b != 0) {
        int t = b;
        b = a % b;
        a = t;
    }
    return a;
}

StatusCode simplify_fraction(int *numerator, int *denominator) {
    int divisor = gcd(*numerator, *denominator);
    *numerator /= divisor;
    *denominator /= divisor;
    return SUCCESS;
}

StatusCode has_finite_representation(int denominator, int base, int *result) {
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

StatusCode check_finite_representation(int base, int count, const double* numbers, int *results) {
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

        int numerator = (int) number;
        simplify_fraction(&numerator, &denominator);

        StatusCode status = has_finite_representation(denominator, base, &results[i]);
        if (status != SUCCESS) {
            return status;
        }
    }

    return SUCCESS;
}


StatusCode print_results(int count, const int* results, const double* numbers, int base) {
    for (int i = 0; i < count; i++) {
        printf("Number %.6f %s a finite representation in base %d.", numbers[i], results[i] ? "has" : "does not have", base);
    }
    return SUCCESS;

}

int main(int argc, char *argv[] __attribute__((unused))) {
    if (argc < 3) {
        printf("Usage: ./9.a <base> <decimal1> <decimal2> ...\n");
        return INVALID_ARGUMENTS;
    }

    int base = atoi(argv[1]);
    int count = argc - 2;
    double *numbers = (double *)malloc(count * sizeof(double));
    int *results = (int *)malloc(count * sizeof(int));

    if (!numbers || !results) {
        printf("Memory allocation error\n");
        free(numbers);
        free(results);
        return MEMORY_ERROR;
    }

    for (int i = 0; i < count; i++) {
        numbers[i] = atof(argv[i + 2]);
    }

    StatusCode status = check_finite_representation(base, count, numbers, results);
    if (status == SUCCESS) {
        print_results(count, results, numbers, base);
    } else {
        printf("An error occurred during calculation: %d\n", status);
    }

    free(numbers);
    free(results);
    return status;
}
