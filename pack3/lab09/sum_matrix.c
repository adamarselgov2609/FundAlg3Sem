#include <stdio.h>
#include <stdlib.h>

int main() {
    int n;
    printf("Введи размер динамического массива: ");
    scanf("%d", &n);

    while (n <= 0) {
        printf("Введите положительное число: ");
        scanf("%d", &n);
    }

    int* array = (int*)malloc(n * sizeof(int));
    
    if (array == NULL) {
        printf("Ошибка выделения памяти.\n");
        return 1;
    }

    for (int i = 0; i < n; i++) {
        scanf("%d", &array[i]);
    }

    for (int i = 0; i < n; i++) {
        printf("%d ", array[i]);
    }

    printf("\n");

    free(array);

    return 0;
}