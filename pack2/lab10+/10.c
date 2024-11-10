#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef enum StatusCode {
    SUCCESS = 0,
    FAILURE = 1,
    ERROR_VALUE = 2,
    ERROR_FUNC = 3,
    ERROR_MEMORY = 4
} StatusCode;


StatusCode my_pow(double *res, double x, int n) {
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



StatusCode koeff_of_newton(double *result, int n, int k) {
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


StatusCode decomposition(double a, int n, double f, double *res) {
    for (int k = 0; k <= n; k++) {
        double bin;
        
        if (koeff_of_newton(&bin, n, k) != 0) {
            printf("Ошибка при вычислении коэффициентов\n");
            return ERROR_VALUE;
        }
        
        double ap;
        if (my_pow(&ap, a, k) != 0) {
            printf("Ошибка в функции my_pow\n");
            return ERROR_FUNC;
        }

        res[n - k] += bin * ap * f;
    }
    return SUCCESS;
}


StatusCode convert_to_massive(double a, double **res, int n, ...) {
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
        if (decomposition(a, i, fs[i], koef) != 0) {
            free(fs);
            free(koef);
            printf("Ошибка в функции decomposition\n");
            return ERROR_FUNC;
        }
    }

    free(fs);
    *res = koef;
    return SUCCESS;
}

int main() {
    double *result;

    printf("Для примера x^4 - 3x^2 + x - 2 в точке a = 3:\n");
    if (convert_to_massive(3, &result, 4, -2.0, 1.0, -3.0, 0.0, 1.0) != SUCCESS) {
        printf("Ошибка при конвертации для n = %d\n", 4);
        return ERROR_VALUE;
    }

    printf("Результаты разложения:\n");
    for (int i = 0; i <= 4; i++) {
        printf("g[%d] = %f\n", i, result[i]);
    }
    free(result);

    printf("\nДля примера 2x^3 + 3x^2 - x + 5 в точке a = 2:\n");
    if (convert_to_massive(2, &result, 3, 5.0, -1.0, 3.0, 2.0) != SUCCESS) {
        printf("Ошибка при конвертации для n = %d\n", 3);
        return ERROR_VALUE;
    }

    printf("Результаты разложения:\n");
    for (int i = 0; i <= 3; i++) {
        printf("g[%d] = %f\n", i, result[i]);
    }
    free(result);

    printf("\nДля примера -x^2 + 4x + 6 в точке a = -1:\n");
    if (convert_to_massive(-1, &result, 2, 6.0, 4.0, -1.0) != SUCCESS) {
        printf("Ошибка при конвертации для n = %d\n", 2);
        return ERROR_VALUE;
    }

    printf("Результаты разложения:\n");
    for (int i = 0; i <= 2; i++) {
        printf("g[%d] = %f\n", i, result[i]);
    }
    free(result);

    return SUCCESS;
}
