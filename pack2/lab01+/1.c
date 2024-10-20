#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <limits.h>

typedef enum StatusCode {
    SUCCESS = 0,
    ERROR_INVALID_ARGUMENTS = 1,
    ERROR_MEMORY_ALLOCATION = 2,
    ERROR_INVALID_FLAG = 3,
    ERROR_INVALID_SEED = 4
} StatusCode;


unsigned int my_strlen(const char *str) {
    unsigned int length = 0;
    while (str[length] != '\0') {
        length++;
    }
    return length;
}


StatusCode reverse_string(char **result, const char *input) {
    if (result == NULL || input == NULL) {
        return ERROR_INVALID_ARGUMENTS;
    }

    unsigned int length = my_strlen(input);
    *result = (char*)malloc((length + 1) * sizeof(char));
    if (*result == NULL) {
        return ERROR_MEMORY_ALLOCATION;
    }

    for (unsigned int i = 0; i < length; i++) {
        (*result)[i] = input[length - 1 - i];
    }
    (*result)[length] = '\0';

    return SUCCESS;
}

StatusCode my_strcat(char *dest, const char *src) {
    unsigned int dest_len = my_strlen(dest);
    unsigned int src_len = my_strlen(src);

    for (unsigned int i = 0; i <= src_len; i++) {
        dest[dest_len + i] = src[i];
    }

    return SUCCESS;
}

StatusCode uppercase_odd_positions(char **result, const char *input) {
    if (result == NULL || input == NULL) {
        return ERROR_INVALID_ARGUMENTS;
    }

    unsigned int length = my_strlen(input);
    *result = (char*)malloc((length + 1) * sizeof(char));
    if (*result == NULL) {
        return ERROR_MEMORY_ALLOCATION;
    }

    for (unsigned int i = 0; i < length; i++) {
        if (i % 2 == 1) {
            (*result)[i] = toupper(input[i]);  
        } else {
            (*result)[i] = input[i];
        }
    }
    (*result)[length] = '\0';

    return SUCCESS;
}

StatusCode sort_string_by_category(char **result, const char *input) {
    if (result == NULL || input == NULL) {
        return ERROR_INVALID_ARGUMENTS;
    }

    unsigned int length = my_strlen(input);
    *result = (char*)malloc((length + 1) * sizeof(char));
    if (*result == NULL) {
        return ERROR_MEMORY_ALLOCATION;
    }

    char *digits = (char*)malloc(length * sizeof(char));
    char *letters = (char*)malloc(length * sizeof(char));
    char *others = (char*)malloc(length * sizeof(char));
    if (digits == NULL || letters == NULL || others == NULL) {
        free(digits);
        free(letters);
        free(others);
        return ERROR_MEMORY_ALLOCATION;
    }

    unsigned int digit_count = 0, letter_count = 0, other_count = 0;

    for (unsigned int i = 0; i < length; i++) {
        if (isdigit(input[i])) {
            digits[digit_count++] = input[i];
        } else if (isalpha(input[i])) {
            letters[letter_count++] = input[i];
        } else {
            others[other_count++] = input[i];
        }
    }

    unsigned int pos = 0;
    for (unsigned int i = 0; i < digit_count; i++) {
        (*result)[pos++] = digits[i];
    }
    for (unsigned int i = 0; i < letter_count; i++) {
        (*result)[pos++] = letters[i];
    }
    for (unsigned int i = 0; i < other_count; i++) {
        (*result)[pos++] = others[i];
    }

    (*result)[pos] = '\0'; 
    free(digits);
    free(letters);
    free(others);

    return SUCCESS;
}

StatusCode concatenate_strings(char **result, unsigned int seed, int argc, char *argv[]) {
    if (result == NULL || argc < 4) {
        return ERROR_INVALID_ARGUMENTS;
    }


    srand(seed);

    int count = argc - 3;
    *result = (char*)malloc(1); 
    if (*result == NULL) {
        return ERROR_MEMORY_ALLOCATION;
    }
    (*result)[0] = '\0'; 

    for (int i = 0; i < count; i++) {
        int random_index = rand() % count; 

        unsigned int length = my_strlen(argv[random_index + 3]);
        *result = (char*)realloc(*result, my_strlen(*result) + length + 1);
        if (*result == NULL) {
            return ERROR_MEMORY_ALLOCATION;
        }

        my_strcat(*result, argv[random_index + 3]);
    }
    
    return SUCCESS;
}

StatusCode print_error(StatusCode code) {
    switch (code) {
        case ERROR_INVALID_ARGUMENTS:
            fprintf(stderr, "Error: Invalid arguments.\n");
            break;
        case ERROR_MEMORY_ALLOCATION:
            fprintf(stderr, "Error: Memory allocation failed.\n");
            break;
        case ERROR_INVALID_FLAG:
            fprintf(stderr, "Error: Invalid flag provided.\n");
            break;
        case ERROR_INVALID_SEED:
            fprintf(stderr, "Error: Invalid seed value.\n");
            break;
        default:
            break;
    }

    return SUCCESS;
}

int validate_seed(const char *seed_str, unsigned int *seed) {
    char *endptr = NULL;
    long value = strtol(seed_str, &endptr, 10);

    if (*endptr != '\0' || value < 0 || value > UINT_MAX) {
        return 0;
    }

    *seed = (unsigned int)value;
    return 1;
}



int main(int argc, char *argv[]) {
    if (argc < 3) {
        print_error(ERROR_INVALID_ARGUMENTS);
        return ERROR_INVALID_ARGUMENTS;
    }

    const char *flag = argv[1];
    const char *input_string = argv[2];

    if (flag[0] != '-') {
        print_error(ERROR_INVALID_FLAG);
        return ERROR_INVALID_FLAG;
    }

    if (flag[1] == 'l') {
        unsigned int length = my_strlen(input_string);
        printf("Length of the string: %u\n", length);
        return SUCCESS;
    }
    else if (flag[1] == 'r') {
        char *reversed = NULL;
        StatusCode status = reverse_string(&reversed, input_string);
        if (status != SUCCESS) {
            print_error(status);
            return status;
        }

        printf("Reversed string: %s\n", reversed);
        free(reversed);  
        return SUCCESS;
    }
    else if (flag[1] == 'u') {
        char *uppercased = NULL;
        StatusCode status = uppercase_odd_positions(&uppercased, input_string);
        if (status != SUCCESS) {
            print_error(status);
            return status;
        }

        printf("String with uppercase odd positions: %s\n", uppercased);
        free(uppercased);  
        return SUCCESS;
    }
    else if (flag[1] == 'n') {
        char *sorted = NULL;
        StatusCode status = sort_string_by_category(&sorted, input_string);
        if (status != SUCCESS) {
            print_error(status);
            return status;
        }

        printf("Sorted string: %s\n", sorted);
        free(sorted);  
        return SUCCESS;
    }
    else if (flag[1] == 'c') {
        if (argc < 4) {
            print_error(ERROR_INVALID_ARGUMENTS);
            return ERROR_INVALID_ARGUMENTS;
        }

        unsigned int seed;
        if (!validate_seed(argv[2], &seed)) {
            print_error(ERROR_INVALID_SEED);
            return ERROR_INVALID_SEED;
        }

        char *concatenated = NULL;
        StatusCode status = concatenate_strings(&concatenated, seed, argc, argv);
        if (status != SUCCESS) {
            print_error(status);
            return status;
        }

        printf("Concatenated string: %s\n", concatenated);
        free(concatenated);  
        return SUCCESS;
    }

    print_error(ERROR_INVALID_FLAG);
    return ERROR_INVALID_FLAG;
}
