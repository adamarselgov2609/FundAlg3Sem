#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef enum {
    SUCCESS = 0,
    ERROR_INVALID_INPUT = 1,
    ERROR_MEMORY_ALLOCATION = 2
} StatusCode;

StatusCode to_base_r(int number, int r, char** result) {
    int bit_size;
    if (r == 2) {
        bit_size = 1;
    } else if (r == 4) {
        bit_size = 2;
    } else if (r == 8) {
        bit_size = 3;
    } else if (r == 16) {
        bit_size = 4;
    } else if (r == 32) {
        bit_size = 5;
    } else {
        return ERROR_INVALID_INPUT;
    }

    *result = (char*)malloc(33);
    if (*result == NULL) {
        return ERROR_MEMORY_ALLOCATION;
    }

    (*result)[32] = '\0';
    int index = 31;
    int mask = (1 << bit_size) - 1;
    while (number > 0 && index >= 0) {
        int bits = number & mask;
        char ch = '0';
             
        for (int i = 0; i < bits; i++) {
            ch++;
        }
    
        if (bits >= 10) {
            ch = 'A';
            for (int i = 10; i < bits; i++) {
                ch++;
            }
        }

        (*result)[index] = ch;
        number >>= bit_size;
        index--;
    }

    while (index >= 0) {
        (*result)[index] = '0';
        index--;
    }

    return SUCCESS;
}

StatusCode validate_input(int input) {
    if (input < 0) {
        return ERROR_INVALID_INPUT;
    }
    return SUCCESS;
}

StatusCode print_results(int number, const char* bin, const char* quart, const char* oct, const char* hex, const char* base32) {
    printf("Число %d в системе счисления с основанием 2:  %s\n"
           "Число %d в системе счисления с основанием 4:  %s\n"
           "Число %d в системе счисления с основанием 8:  %s\n"
           "Число %d в системе счисления с основанием 16: %s\n"
           "Число %d в системе счисления с основанием 32: %s\n",
           number, bin, number, quart, number, oct, number, hex, number, base32);
    return SUCCESS;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Ошибка: необходимо ввести одно число.\n");
        return ERROR_INVALID_INPUT;
    }

    char* endptr;
    long number = strtol(argv[1], &endptr, 10);

    if (*endptr != '\0' || endptr == argv[1] || number < 0) {
        printf("Ошибка: недопустимое число. Введите положительное целое число.\n");
        return ERROR_INVALID_INPUT;
    }

    if (number > INT_MAX) {
        printf("Ошибка: число слишком велико.\n");
        return ERROR_INVALID_INPUT;
    }

    StatusCode status = validate_input((int)number);
    if (status != SUCCESS) {
        printf("Ошибка: недопустимое число. Введите положительное целое число.\n");
        return status;
    }

    char* bin = NULL;
    char* quart = NULL;
    char* oct = NULL;
    char* hex = NULL;
    char* base32 = NULL;

    if (to_base_r((int)number, 2, &bin) != SUCCESS ||
        to_base_r((int)number, 4, &quart) != SUCCESS ||
        to_base_r((int)number, 8, &oct) != SUCCESS ||
        to_base_r((int)number, 16, &hex) != SUCCESS ||
        to_base_r((int)number, 32, &base32) != SUCCESS) {
        printf("Ошибка: не удалось перевести число.\n");
        free(bin);
        free(quart);
        free(oct);
        free(hex);
        free(base32);
        return ERROR_MEMORY_ALLOCATION;
    }

    print_results((int)number, bin, quart, oct, hex, base32);

    free(bin);
    free(quart);
    free(oct);
    free(hex);
    free(base32);

    return SUCCESS;
}
