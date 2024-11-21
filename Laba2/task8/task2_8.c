#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdarg.h>

typedef enum {
    OK = 0,
    ERROR = 1,
    ERROR_INVALID_BASE = 2,
    ERROR_INVALID_NUMBER = 3,
    ERROR_MEMORY = 4
} Status;

int char_to_digit(char c) 
{
    if (c >= '0' && c <= '9') 
    {
        return c - '0';
    }
    if (toupper(c) >= 'A' && toupper(c) <= 'Z') 
    {
        return toupper(c) - 'A' + 10;
    }
    return -1;
}

char digit_to_char(int digit) 
{
    if (digit < 10)
    {
        return digit + '0';
    }
    return digit - 10 + 'A';
}

char* add_numbers(const char* num1, const char* num2, int base) 
{
    int len1 = strlen(num1);
    int len2 = strlen(num2);
    int max_len = (len1 > len2) ? len1 : len2;
    
    char* result = (char*)calloc(max_len + 2, sizeof(char));
    if (!result) 
    {
        return NULL;
    }
    
    int carry = 0;
    int i = len1 - 1;
    int j = len2 - 1;
    int k = max_len;
    result[k + 1] = '\0';
    
    while (i >= 0 || j >= 0 || carry) 
    {
        int sum = carry;
        if (i >= 0) 
        {
            sum += char_to_digit(num1[i--]);
        }
        if (j >= 0) 
        {
            sum += char_to_digit(num2[j--]);
        }
        
        result[k--] = digit_to_char(sum % base);
        carry = sum / base;
    }
    
    char* final_result = strdup(result + k + 1);
    free(result);
    return final_result;
}

int is_valid_number(const char* num, int base) 
{
    if (!num || !*num) 
    {
        return 0;
    }
    
    for (int i = 0; num[i]; i++) 
    {
        int digit = char_to_digit(num[i]);
        if (digit == -1 || digit >= base) 
        {
            return 0;
        }
    }
    return 1;
}

char* sum_in_base(int base, int count, ...) 
{
    if (base < 2 || base > 36 || count < 1) 
    {
        return NULL;
    }
    
    va_list args;
    va_start(args, count);
    
    char* sum = strdup(va_arg(args, char*));
    if (!sum || !is_valid_number(sum, base)) 
    {
        free(sum);
        va_end(args);
        return NULL;
    }
    
    for (int i = 1; i < count; i++) 
    {
        char* next_num = va_arg(args, char*);
        if (!is_valid_number(next_num, base)) 
        {
            free(sum);
            va_end(args);
            return NULL;
        }
        
        char* new_sum = add_numbers(sum, next_num, base);
        free(sum);
        if (!new_sum) 
        {
            va_end(args);
            return NULL;
        }
        sum = new_sum;
    }
    
    va_end(args);
    return sum;
}

int main(int argc, char* argv[]) 
{
    if (argc < 4) 
    {
        printf("Usage:  <base> <number1> <number2> ... <numberN>\n");
        return ERROR;
    }

    int base = atoi(argv[1]);
    if (base < 2 || base > 36) 
    {
        printf("Error: Base must be between 2 and 36\n");
        return ERROR_INVALID_BASE;
    }

    int count = argc - 2;

    for (int i = 2; i < argc; i++) 
    {
        if (!is_valid_number(argv[i], base)) 
        {
            printf("Error: Invalid number for base %d\n", base);
            return ERROR_INVALID_NUMBER;
        }
    }

    char* result = sum_in_base(base, count, argv[2], argv[3], argv[4], argv[5], argv[6]);
    if (!result) 
    {
        printf("Error: Failed to calculate sum\n");
        return ERROR_MEMORY;
    }

    printf("Sum in base %d: %s\n", base, result);
    free(result);

    return OK;
}