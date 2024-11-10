#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <math.h>


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

    printf("Введите количество чисел для среднего геометрического: ");
    scanf("%d", &count);

    if (count <= 0) {
        printf("Количество чисел должно быть положительным.\n");
        return 1;
    }

    double numbers[count];

    printf("Введите %d вещественных числа:\n", count);
    for (int i = 0; i < count; i++) {
        printf("Число %d: ", i + 1);
        scanf("%lf", &numbers[i]);
    }

    double mean = geometricMean(count, numbers[0], numbers[1], numbers[2], numbers[3], numbers[4], numbers[5]); 

    double base;
    int exp;
    printf("Введите основание для возведения в степень: ");
    scanf("%lf", &base);
    printf("Введите степень: ");
    scanf("%d", &exp);


    double result = power(base, exp);


    printf("Среднее геометрическое: %.2f\n", mean);
    printf("%.2f в степени %d = %.2f\n", base, exp, result);
    
    return 0;
}
