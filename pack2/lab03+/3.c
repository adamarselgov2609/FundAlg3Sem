#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

typedef enum {
    SUCCESS = 0,
    ERROR_INVALID_ARGUMENTS,
    ERROR_FILE_NOT_FOUND,
    ERROR_MEMORY_ALLOCATION
} StatusCode;

int my_strlen(const char *str) {
    int length = 0;
    while (str[length] != '\0') {
        length++;
    }
    return length;
}

int find_substring(const char *string, const char *substring) {
    if (!string || !substring) return -1;
    
    int string_len = my_strlen(string);
    int substring_len = my_strlen(substring);
    
    for (int i = 0; i <= string_len - substring_len; i++) {
        int j = 0;
        while (j < substring_len && string[i + j] == substring[j]) {
            j++;
        }
        if (j == substring_len) {
            return i;
        }
    }
    return -1;  
}

StatusCode read_file(const char *file_path, char **buffer) {
    FILE *file = fopen(file_path, "r");
    if (!file) return ERROR_FILE_NOT_FOUND;

    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);

    *buffer = malloc(length + 1);
    if (!(*buffer)) {
        fclose(file);
        return ERROR_MEMORY_ALLOCATION;
    }

    fread(*buffer, 1, length, file);
    (*buffer)[length] = '\0';

    fclose(file);
    return SUCCESS;
}

char* next_line(char *buffer, int *index) {
    if (buffer[*index] == '\0') {
        return NULL;
    }

    char *start = &buffer[*index];
    while (buffer[*index] != '\n' && buffer[*index] != '\0') {
        (*index)++;
    }

    if (buffer[*index] == '\n') {
        buffer[*index] = '\0';
        (*index)++;
    }

    return start;
}

StatusCode search_in_file(const char *file_path, const char *substring) {
    char *buffer = NULL;
    StatusCode status = read_file(file_path, &buffer);
    if (status != SUCCESS) return status;

    int line_number = 1;
    int index = 0;
    char *line;

    while ((line = next_line(buffer, &index)) != NULL) {
        int position = find_substring(line, substring);
        if (position != -1) {
            printf("Файл: %s, строка: %d, позиция: %d\n", file_path, line_number, position + 1);
        }
        line_number++;
    }

    free(buffer);
    return SUCCESS;
}

StatusCode search_in_files(const char *substring, int file_count, const char **file_paths) {
    for (int i = 0; i < file_count; i++) {
        const char *file_path = file_paths[i];
        StatusCode status = search_in_file(file_path, substring);
        if (status != SUCCESS) {
            fprintf(stderr, "Ошибка при работе с файлом %s\n", file_path);
            return status;
        }
    }
    return SUCCESS;
}

StatusCode validate_arguments(int argc, char *argv[] __attribute__((unused))) {
    if (argc < 3) {
        fprintf(stderr, "Usage: ./3.a <substring> <file1> <file2> ...\n");
        return ERROR_INVALID_ARGUMENTS;
    }
    return SUCCESS;
}

int main(int argc, char *argv[]) {
    StatusCode status = validate_arguments(argc, argv);
    if (status != SUCCESS) {
        return status;
    }

    const char *substring = argv[1];

    status = search_in_files(substring, argc - 2, (const char **) &argv[2]);

    return status;
}
