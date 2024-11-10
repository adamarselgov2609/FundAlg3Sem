#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

typedef enum StatusCode {
    SUCCESS = 0,
    ERROR_SAME_SIGN = 1,
    ERROR_INVALID_INTERVAL = 2,
    ERROR_INVALID_EPSILON = 3,
    ERROR_MEMORY_ALLOCATION = 4,
} StatusCode;

StatusCode find_root(double a, double b, double epsilon, double (*func)(double), double *root) {
    double fa = func(a);
    double fb = func(b);

    if (!fa || !fb) {
        *root = !fa ? a : b;
        return SUCCESS;
    }

    if (fa * fb > 0) {
        return ERROR_SAME_SIGN;
    }

    if (epsilon <= 0) {
        return ERROR_INVALID_EPSILON;
    }

    while ((b - a) > epsilon) {
        double midpoint = (a + b) / 2.0;
        double fmid = func(midpoint);

        if (fabs(fmid) < epsilon) {
            *root = midpoint;
            return SUCCESS;
        }

        if (fa * fmid < 0) {
            b = midpoint;
            fb = fmid;
        } else {
            a = midpoint;
            fa = fmid;
        }
    }

    *root = (a + b) / 2.0;
    return SUCCESS;
}

double equation1(double x) {
     return x * x - 4;
}

double equation2(double x) {
     return x * x * x - x - 2;
}

double equation3(double x) {
     return sin(x);
}

double equation4(double x) {
    return exp(x) - 3;
}

double equation5(double x) {
     return x * x * x - 1;
}

double equation6(double x) {
     return x * x * x * x * x - 3 * x * x * x + 2;
}

StatusCode print_error(StatusCode status) {
    switch (status) {
        case ERROR_SAME_SIGN:
            fprintf(stdout, "Функция имеет одинаковый знак на концах интервала.\n");
            break;
        case ERROR_INVALID_EPSILON:
            fprintf(stdout, "Неверная точность.\n");
            break;
        default:
            fprintf(stdout, "Неизвестная ошибка.\n");
            break;
    }
    return SUCCESS;
}

StatusCode solve_equations() {
    double a, b, epsilon;
    double root;
    int equation_choice;
    StatusCode status;

    double (*equations[])(double) = {equation1, equation2, equation3, equation4, equation5, equation6};
    const char *equation_names[] = {
        "x^2 - 4",
        "x^3 - x - 2",
        "sin(x) - 0.5",
        "exp(x) - 3",
        "x^3 - 1",
        "x^5 - 3x^3 + 2"
    };

    printf("Выберите уравнение для решения:\n");
    for (int i = 0; i < 6; ++i) {
        printf("%d: %s\n", i + 1, equation_names[i]);
    }

    printf("Введите номер уравнения (1-6): ");
    if (scanf("%d", &equation_choice) != 1 || equation_choice < 1 || equation_choice > 6) {
        fprintf(stdout, "Неверный ввод. Попробуйте снова.\n");
        return ERROR_INVALID_INTERVAL;
    }

    printf("Введите нижнюю границу интервала a: ");
    scanf("%lf", &a);

    printf("Введите верхнюю границу интервала b: ");
    scanf("%lf", &b);

    if (a >= b) {
        fprintf(stdout, "Неверный интервал. Левая граница должна быть меньше правой.\n");
        return ERROR_INVALID_INTERVAL;
    }

    printf("Введите точность epsilon: ");
    scanf("%lf", &epsilon);

    printf("Решаем уравнение %s на интервале [%.2f, %.2f] с точностью %.5f\n", equation_names[equation_choice - 1], a, b, epsilon);
    
    status = find_root(a, b, epsilon, equations[equation_choice - 1], &root);

    if (status == ERROR_SAME_SIGN || status == ERROR_INVALID_EPSILON) {
        print_error(status);
    } else {
        printf("Корень уравнения: %.5lf\n", root);
    }

    return SUCCESS;
}

int main() {
    solve_equations();
    return EXIT_SUCCESS;
}
