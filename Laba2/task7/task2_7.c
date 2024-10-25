#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef enum Eode{
    SUCCESS = 0,
    ERROR_SAME_SIGN = 1,
    ERROR_INVALID_INTERVAL = 2,
    ERROR_INVALID_EPSILON = 3,
    ERROR_MEMORY_ALLOCATION = 4,
} Eode;

Eode dixot(double a, double b, double epsilon, double (*func)(double), double *root) {
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

double f1(double x) {
    return x * x - 4; 
}

double f2(double x) {
    return x * x * x - x - 2; 
}

double f3(double x) {
    return sin(x) - 0.5;  
}

double f4(double x) {
    return exp(x) - 3;  
}

double f5(double x) {
    return x * x * x - 1;  
}

double f6(double x) {
    return x * x * x * x * x - 3 * x * x * x + 2;  
}

Eode print_err(Eode status) {
    switch (status) {
        case ERROR_SAME_SIGN:
            fprintf(stderr, "The function has the same sign at both ends of the interval.\n");
            break;
        case ERROR_INVALID_INTERVAL:
            fprintf(stderr, "Invalid interval.\n");
            break;
        case ERROR_INVALID_EPSILON:
            fprintf(stderr, "Invalid precision.\n");
            break;
        case ERROR_MEMORY_ALLOCATION:
            fprintf(stderr, "Memory allocation error.\n");
            break;
        default:
            fprintf(stderr, "Unknown error.\n");
            break;
    }
    return SUCCESS;
}

int main() {
    int choice;
    double a, b, epsilon, root;
    Eode status;

    printf("Choose an equation to solve:\n");
    printf("Enter the equation number (1 to 6): ");
    if (scanf("%d", &choice) != 1) {
        fprintf(stderr, "Input error.\n");
        return EXIT_FAILURE;
    }

    double (*selected_func)(double);
    switch (choice) {
        case 1:
            selected_func = f1;
            break;
        case 2:
            selected_func = f2;
            break;
        case 3:
            selected_func = f3;
            break;
        case 4:
            selected_func = f4;
            break;
        case 5:
            selected_func = f5;
            break;
        case 6:
            selected_func = f6;
            break;
        default:
            fprintf(stderr, "Wrong number of equation\n");
            return EXIT_FAILURE;
    }

    printf("Enter the lower bound of the interval (a): ");
    if (scanf("%lf", &a) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    printf("Enter the upper bound of the interval (b): ");
    if (scanf("%lf", &b) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }


    printf("epsilon: ");
    if (scanf("%lf", &epsilon) != 1 || epsilon <= 0) {
        fprintf(stderr, "Invalid epsilon\n");
        return EXIT_FAILURE;
    }


    status = dixot(a, b, epsilon, selected_func, &root);
    if (status != SUCCESS) {
        print_err(status);
        return EXIT_FAILURE;
    }

    printf("Root: %.5lf\n", root);
    return 0;
}