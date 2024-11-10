#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <math.h>
#include <float.h>

typedef enum Eode {
    SUCCESS = 0,
    ERROR_MEMORY,
    ERROR_VALUE,
    ERROR_FUNC
} Eode;

int my_pow(double *res, double x, int n) {
    *res = 1.0;

    if (x == 0 && n < 0) {
        printf("Ошибка: деление на ноль\n");
        return ERROR_VALUE;
    }

    if (n < 0) {
        x = 1 / x;
        n = -n;
    }

    for (int i = 0; i < n; i++) {
        *res *= x;
    }

    return SUCCESS;
}

int koeff_of_newton(double *result, int n, int k) {
    if (n < 0 || k < 0 || k > n) {
        printf("Недопустимые значения n и k\n");
        return ERROR_VALUE;
    }
    
    *result = 1;
    for (int i = n - k + 1; i <= n; i++) {
        *result *= i;
    }
    for (int i = 2; i <= k; i++) {
        *result /= i;
    }

    return SUCCESS;
}

int decomposition(double a, int n, double f, double *res) {
    for (int k = 0; k <= n; k++) {
        double bin;
        if (koeff_of_newton(&bin, n, k) != SUCCESS) {
            printf("Ошибка при вычислении коэффициентов\n");
            return ERROR_FUNC;
        }

        double ap;
        if (my_pow(&ap, a, k) != SUCCESS) {
            printf("Ошибка в функции my_pow\n");
            return ERROR_FUNC;
        }

        res[n - k] += bin * ap * f;
    }
    return SUCCESS;
}

int reexpand_polynomial(double a, double **result, int n, ...) {
    double *fs = malloc((n + 1) * sizeof(double));
    if (!fs) {
        printf("Не удалось выделить память\n");
        return ERROR_MEMORY;
    }

    va_list valist;
    va_start(valist, n);

    for (int i = 0; i <= n; i++) {
        fs[i] = va_arg(valist, double);
    }
    va_end(valist);

    double *koef = malloc((n + 1) * sizeof(double));
    if (!koef) {
        free(fs);
        printf("Не удалось выделить память\n");
        return ERROR_MEMORY;
    }

    for (int i = 0; i <= n; i++) {
        koef[i] = 0.0;
    }

    for (int i = n; i >= 0; i--) {
        if (decomposition(a, i, fs[i], koef) != SUCCESS) {
            free(fs);
            free(koef);
            printf("Ошибка в функции decomposition\n");
            return ERROR_FUNC;
        }
    }

    free(fs);
    *result = koef;
    return SUCCESS;
}

int validateDouble(const char *arg, double *value) {
    char *endptr;
    *value = strtod(arg, &endptr);
    if (*endptr != '\0' || (*value == 0 && arg[0] != '0')) {
        return 0;
    }
    return 1;
}

int main(int argc, char *argv[]) {
    if (argc < 4) {
        fprintf(stderr, "Usage: %s <a> <degree> <coefficient1> <coefficient2> ...\n", argv[0]);
        return -1;
    }

    double a;
    int degree;

    if (!validateDouble(argv[1], &a)) {
        fprintf(stderr, "Invalid 'a' value. It must be a number.\n");
        return -1;
    }

    char *endptr;
    degree = strtol(argv[2], &endptr, 10);
    if (*endptr != '\0' || degree < 0 || argc != degree + 4) {
        fprintf(stderr, "Invalid degree or number of coefficients.\n");
        return -1;
    }

    double *coefficients = (double *)malloc((degree + 1) * sizeof(double));
    if (coefficients == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    for (int i = 0; i <= degree; i++) {
        if (!validateDouble(argv[i + 3], &coefficients[i])) {
            fprintf(stderr, "Invalid coefficient for x^%d.\n", i);
            free(coefficients);
            return -1;
        }
    }

    double *result;
    int status = reexpand_polynomial(a, &result, degree, coefficients[0], coefficients[1], coefficients[2]);
    
    if (status != SUCCESS) {
        free(coefficients);
        return status;
    }

    printf("Resulting coefficients:\n");
    for (int i = 0; i <= degree; i++) {
        printf("g%d = %f\n", i, result[i]);
    }

    free(result);
    free(coefficients);

    return 0;
}
