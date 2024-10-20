#include <stdio.h>
#include <stdlib.h>
#include <math.h>

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

    if (fa == 0 || fb == 0) {
        if (fa == 0) {
           *root = a;
           return SUCCESS;
        }
        else {
            *root = b;
            return SUCCESS;
        }
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

        if (fabs(fmid) < epsilon ) {
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
    return sin(x) - 0.5;  
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
            fprintf(stderr, "Функция имеет одинаковый знак на концах интервала.\n");
            break;
        case ERROR_INVALID_INTERVAL:
            fprintf(stderr, "Неверный интервал.\n");
            break;
        case ERROR_INVALID_EPSILON:
            fprintf(stderr, "Неверная точность.\n");
            break;
        case ERROR_MEMORY_ALLOCATION:
            fprintf(stderr, "Ошибка выделения памяти.\n");
            break;
        default:
            fprintf(stderr, "Неизвестная ошибка.\n");
            break;
    }
    return SUCCESS;
}

int main() {
    int choice;
    double a, b, epsilon, root;
    StatusCode status;


    printf("Выберите уравнение для решения:\n");
    printf("1: x^2 - 4\n");
    printf("2: x^3 - x - 2\n");
    printf("3: sin(x) - 0.5\n");
    printf("4: exp(x) - 3\n");
    printf("5: x^3 - 1\n");
    printf("6: x^5 - 3x^3 + 2\n");
    printf("Введите номер уравнения (от 1 до 6): ");
    if (scanf("%d", &choice) != 1) {
        fprintf(stderr, "Ошибка ввода. Нечисловое представление.\n");
        return EXIT_FAILURE;
    }

    double (*selected_func)(double);
    switch (choice) {
        case 1:
            selected_func = equation1;
            break;
        case 2:
            selected_func = equation2;
            break;
        case 3:
            selected_func = equation3;
            break;
        case 4:
            selected_func = equation4;
            break;
        case 5:
            selected_func = equation5;
            break;
        case 6:
            selected_func = equation6;
            break;
        default:
            fprintf(stderr, "Неверный номер уравнения.\n");
            return EXIT_FAILURE;
    }

    printf("Введите нижнюю границу интервала (a): ");
    if (scanf("%lf", &a) != 1) {
        fprintf(stderr, "Ошибка ввода. Нечисловое представление.\n");
        return EXIT_FAILURE;
    }

    printf("Введите верхнюю границу интервала (b): ");
    if (scanf("%lf", &b) != 1) {
        fprintf(stderr, "Ошибка ввода. Нечисловое представление.\n");
        return EXIT_FAILURE;
    }


    printf("Введите желаемую точность (epsilon): ");
    if (scanf("%lf", &epsilon) != 1 || epsilon <= 0) {
        fprintf(stderr, "Неверная точность.\n");
        return EXIT_FAILURE;
    }


    status = find_root(a, b, epsilon, selected_func, &root);
    if (status != SUCCESS) {
        print_error(status);
        return EXIT_FAILURE;
    }

    printf("Корень уравнения: %.5lf\n", root);
    return EXIT_SUCCESS;
}
