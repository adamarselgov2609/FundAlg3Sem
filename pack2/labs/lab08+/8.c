#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define SUCCESS 0
#define ERROR_MEMORY_ALLOCATION 1
#define ERROR_INVALID_BASE 2
#define ERROR_INVALID_NUMBER 3

int is_valid_char(char c, int base) {
    if (isdigit(c)) {
        return c - '0' < base;
    } else if (isupper(c)) {
        return c - 'A' + 10 < base;
    }
    return 0;
}

int is_valid_number(const char* number, int base) {
    for (size_t i = 0; i < strlen(number); i++) {
        if (!is_valid_char(number[i], base)) {
            return 0; 
        }
    }
    return 1; 
}

int add_in_base(const char* num1, const char* num2, int base, char** result) {
    size_t len1 = strlen(num1);
    size_t len2 = strlen(num2);
    size_t maxLen = (len1 > len2 ? len1 : len2) + 1; 

    char* temp_result = (char*)malloc(maxLen + 1);
    if (!temp_result) {
        return ERROR_MEMORY_ALLOCATION;
    }

    temp_result[maxLen] = '\0'; 

    int carry = 0;
    int idx1 = len1 - 1;
    int idx2 = len2 - 1;
    int idxResult = maxLen - 1;

    while (idx1 >= 0 || idx2 >= 0 || carry > 0) {
        int digit1 = (idx1 >= 0) ? (isdigit(num1[idx1]) ? num1[idx1] - '0' : num1[idx1] - 'A' + 10) : 0;
        int digit2 = (idx2 >= 0) ? (isdigit(num2[idx2]) ? num2[idx2] - '0' : num2[idx2] - 'A' + 10) : 0;

        int sum = digit1 + digit2 + carry;
        carry = sum / base;
        int digitResult = sum % base;

        temp_result[idxResult--] = (digitResult < 10) ? (digitResult + '0') : (digitResult - 10 + 'A');

        idx1--;
        idx2--;
    }

    *result = strdup(temp_result + idxResult + 1);
    free(temp_result);

    if (*result == NULL || (*result)[0] == '\0') {
        free(*result);
        *result = strdup("0"); 
    }

    return SUCCESS;
}

int sum_in_base(int base, int count, char** numbers, char** result) {
    if (base < 2 || base > 36) {
        return ERROR_INVALID_BASE; 
    }

    for (int i = 0; i < count; i++) {
        if (!is_valid_number(numbers[i], base)) {
            return ERROR_INVALID_NUMBER; 
        }
    }

    *result = strdup(numbers[0]); 
    if (*result == NULL) {
        return ERROR_MEMORY_ALLOCATION;
    }

    for (int i = 1; i < count; i++) {
        char* nextNumber = numbers[i];
        char* newSum = NULL;

        int status = add_in_base(*result, nextNumber, base, &newSum);
        free(*result); 
        *result = newSum; 

        if (status != SUCCESS) {
            return status; 
        }
    }

    return SUCCESS;
}

int main(int argc, char *argv[] __attribute__((unused))) {
    if (argc < 4) {
        fprintf(stderr, "Usage: ./8.a <base> <number1> <number2> ... <numberN>\n");
        return EXIT_FAILURE;
    }

    int base = atoi(argv[1]);
    char* result = NULL;

    int status = sum_in_base(base, argc - 2, &argv[2], &result);

    if (status == SUCCESS) {
        printf("Sum in base %d: %s\n", base, result);
    } else if (status == ERROR_INVALID_BASE) {
        fprintf(stderr, "Error: Invalid base. It must be in range [2..36].\n");
    } else if (status == ERROR_INVALID_NUMBER) {
        fprintf(stderr, "Error: One or more numbers are invalid for the base %d.\n", base);
    } else if (status == ERROR_MEMORY_ALLOCATION) {
        fprintf(stderr, "Error: Memory allocation failed.\n");
    }

    free(result); 
    return status == SUCCESS ? EXIT_SUCCESS : EXIT_FAILURE;
}
