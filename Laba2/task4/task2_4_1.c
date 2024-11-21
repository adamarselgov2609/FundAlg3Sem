#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>

typedef enum {
    SUCCESS = 0,
    ERR_INVALID_VERTICES = -1,
    ERR_MEMORY_ALLOCATION = -2,
    ERR_INVALID_INPUT = -3,
    ERR_NOT_CONVEX = -4
} Eode;

Eode is_convex(int n, double* x, double* y) {
    if (n < 3) return ERR_INVALID_VERTICES;

    bool sign = false;
    bool first = true;

    for (int i = 0; i < n; i++) {
        int j = (i + 1) % n;
        int k = (i + 2) % n;

        double cross_product = (x[j] - x[i]) * (y[k] - y[j]) - (y[j] - y[i]) * (x[k] - x[j]);

        if (first) {
            sign = (cross_product > 0);
            first = false;
        } else if ((cross_product > 0) != sign) {
            return ERR_NOT_CONVEX;
        }
    }

    return SUCCESS;
}

double polynomial_value(double x, int degree, ...) {
    va_list args;
    va_start(args, degree);

    double result = 0;
    for (int i = degree; i >= 0; i--) {
        double coef = va_arg(args, double);
        result += coef * pow(x, i);
    }

    va_end(args);
    return result;
}

int num_digits(long long n, int base) {
    int digits = 0;
    while (n > 0) {
        digits++;
        n /= base;
    }
    return digits;
}

bool is_kaprekar(long long num, int base) {
    if (num == 0) return false;

    long long squared = num * num;
    int digits = num_digits(num, base);

    long long divisor = pow(base, digits);
    long long right = squared % divisor;
    long long left = squared / divisor;

    return (left + right == num);
}

void find_kaprekar_numbers(int base, int count, long long* numbers) {
    for (int i = 0; i < count; i++) {
        if (is_kaprekar(numbers[i], base)) {
            printf("%lld is a Kaprekar number in base %d\n", numbers[i], base);
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: <function_number> arguments\n");
        return ERR_INVALID_INPUT;
    }

    int n = atoi(argv[1]);

    switch (n) {
        case 1: {
            if (argc < 3) {
                printf("Usage: 1 <number_of_vertices> <x1 y1> <x2 y2> ...\n");
                return ERR_INVALID_INPUT;
            }

            int count = atoi(argv[2]);

            if (count < 3) {
                printf("The number of vertices must be more than 2.\n");
                return ERR_INVALID_VERTICES;
            }

            if (count > 100) {
                printf("The number of vertices exceeds the maximum allowed (100).\n");
                return ERR_INVALID_VERTICES;
            }

            double *x = malloc(count * sizeof(double));
            double *y = malloc(count * sizeof(double));
            if (x == NULL || y == NULL) {
                printf("Memory allocation failed\n");
                free(x);
                free(y);
                return ERR_MEMORY_ALLOCATION;
            }

            for (int i = 0; i < count; i++) {
                if (argc < 4 + 2 * i) {
                    printf("Insufficient arguments for vertices.\n");
                    free(x);
                    free(y);
                    return ERR_INVALID_INPUT;
                }
                x[i] = atof(argv[3 + 2 * i]);
                y[i] = atof(argv[4 + 2 * i]);
            }

            Eode convex = is_convex(count, x, y);

            if (convex == SUCCESS) {
                printf("The polygon is convex.\n");
            } else {
                printf("The polygon is not convex.\n");
            }

            free(x);
            free(y);
            return 0;
        }

        case 2: {
            if (argc < 4) {
                printf("Usage: %s 2 <degree> <x> <coeff1> <coeff2> ...\n", argv[0]);
                return ERR_INVALID_INPUT;
            }

            int degree = atoi(argv[2]);
            if (degree < 0) {
                printf("Invalid degree.\n");
                return ERR_INVALID_INPUT;
            }

            double* coeffs = malloc((degree + 1) * sizeof(double));
            if (coeffs == NULL) {
                printf("Memory allocation failed\n");
                return ERR_MEMORY_ALLOCATION;
            }

            for (int i = degree; i >= 0; i--) {
                if (argc < 4 + degree - i) {
                    printf("Insufficient arguments for coefficients.\n");
                    free(coeffs);
                    return ERR_INVALID_INPUT;
                }
                coeffs[i] = atof(argv[3 + degree - i]);
            }

            double x = atof(argv[3 + degree + 1]);

            double result = polynomial_value(x, degree, coeffs[degree], coeffs[degree - 1], coeffs[degree - 2]);
            printf("Polynomial value at x = %.2f: %.2f\n", x, result);

            free(coeffs);
            return 0;
        }

        case 3: {
            if (argc < 4) {
                printf("Usage: %s 3 <base> <count> <number1> <number2> ...\n", argv[0]);
                return ERR_INVALID_INPUT;
            }

            int base = atoi(argv[2]);
            if (base < 2) {
                printf("Invalid base.\n");
                return ERR_INVALID_INPUT;
            }

            int count = atoi(argv[3]);
            if (count < 1) {
                printf("Invalid count.\n");
                return ERR_INVALID_INPUT;
            }

            long long* numbers = malloc(count * sizeof(long long));
            if (numbers == NULL) {
                printf("Memory allocation failed\n");
                return ERR_MEMORY_ALLOCATION;
            }

            for (int i = 0; i < count; i++) {
                if (argc < 4 + i) {
                    printf("Insufficient arguments for numbers.\n");
                    free(numbers);
                    return ERR_INVALID_INPUT;
                }
                numbers[i] = atoll(argv[4 + i]);
            }

            printf("Kaprekar numbers in base %d:", base);
            find_kaprekar_numbers(base, count, numbers);

            free(numbers);
            return 0;
        }

        default:
            printf("Invalid option selected.\n");
            return ERR_INVALID_INPUT;
    }
}