#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <limits.h>

typedef enum {
    OK = 0,
    ERR_ARGS = 1,
    ERR_MEM = 2,
    ERR_FLAG = 3,
    ERR_SEED = 4
} Eode;

unsigned int f_len(const char *str) {
    unsigned int len = 0;
    while (str[len] != '\0') {
        len++;
    }
    return len;
}

int reverse_str(char **res, const char *in) {
    if (!res || !in){
         return ERR_ARGS;
    }

    unsigned int len = f_len(in);
    *res = (char*)malloc((len + 1) * sizeof(char));
    if (!*res){
        return ERR_MEM;
    }

    for (unsigned int i = 0; i < len; i++) {
        (*res)[i] = in[len - 1 - i];
    }
    (*res)[len] = '\0';

    return OK;
}

int f_conc(char *dest, const char *src) {
    unsigned int dest_len = f_len(dest);
    unsigned int src_len = f_len(src);

    for (unsigned int i = 0; i <= src_len; i++) {
        dest[dest_len + i] = src[i];
    }

    return OK;
}

int f_upper(char **res, const char *in) {
    if (!res || !in) {
        return ERR_ARGS;
    }

    unsigned int len = f_len(in);
    *res = (char*)malloc((len + 1) * sizeof(char));
    if (!*res){
        return ERR_MEM;
    }
    for (unsigned int i = 0; i < len; i++) {
        (*res)[i] = (i % 2 == 1) ? toupper(in[i]) : in[i];
    }
    (*res)[len] = '\0';

    return OK;
}

int f_sort(char **res, const char *in) {
    if (!res || !in){
        return ERR_ARGS;
    }
    unsigned int len = f_len(in);
    *res = (char*)malloc((len + 1) * sizeof(char));
    if (!*res){
         return ERR_MEM;
    }
    char *digits = (char*)malloc(len * sizeof(char));
    char *letters = (char*)malloc(len * sizeof(char));
    char *others = (char*)malloc(len * sizeof(char));
    if (!digits || !letters || !others) {
        free(digits); 
        free(letters); 
        free(others);
        return ERR_MEM;
    }

    unsigned int d_cnt = 0, l_cnt = 0, o_cnt = 0;

    for (unsigned int i = 0; i < len; i++) {
        if (isdigit(in[i])) {
            digits[d_cnt++] = in[i];
        }
        else if (isalpha(in[i])) {
            letters[l_cnt++] = in[i];
        }
        else {
            others[o_cnt++] = in[i];
        }
    }

    unsigned int pos = 0;
    for (unsigned int i = 0; i < d_cnt; i++) {
        (*res)[pos++] = digits[i];
    }
    for (unsigned int i = 0; i < l_cnt; i++) {
        (*res)[pos++] = letters[i];
    }
    for (unsigned int i = 0; i < o_cnt; i++) {
        (*res)[pos++] = others[i];
    }
    (*res)[pos] = '\0';

    free(digits); 
    free(letters); 
    free(others);
    return OK;
}

int f_rand_conc(char **res, unsigned int seed, int argc, char *argv[]) {
    if (!res || argc < 4){
        return ERR_ARGS;
    }
    srand(seed);
    int cnt = argc - 3;
    *res = (char*)malloc(1); 
    if (!*res) {
        return ERR_MEM;
    }
    (*res)[0] = '\0';

    for (int i = 0; i < cnt; i++) {
        int rnd_idx = rand() % cnt;
        unsigned int len = f_len(argv[rnd_idx + 3]);
        *res = (char*)realloc(*res, f_len(*res) + len + 1);
        if (!*res) return ERR_MEM;
        f_conc(*res, argv[rnd_idx + 3]);
    }

    return OK;
}

int print_err(int tmp) {
    switch (tmp) {
        case ERR_ARGS: 
            printf("Error: Invalid arguments.\n"); 
            return ERR_ARGS;
        case ERR_MEM: 
            printf("Error: Memory allocation failed.\n");
            return ERR_MEM;
        case ERR_FLAG: 
            printf("Error: Invalid flag provided.\n");
            return ERR_FLAG;
        case ERR_SEED: 
            printf("Error: Invalid seed value.\n");
            return ERR_SEED;
        default: 
            break;
    }
    return OK;
}

int validate(const char *seed_str, unsigned int *seed) {
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
        print_err(ERR_ARGS);
        return ERR_ARGS;
    }

    const char *flag = argv[1];
    const char *input = argv[2];

    if (flag[0] != '-') {
        print_err(ERR_FLAG);
        return ERR_FLAG;
    }

    int status;
    char *result = NULL;

    switch (flag[1]) {
        case 'l':
            printf("Length of the string: %u\n", f_len(input));
            return OK;
            
        case 'r':
            status = reverse_str(&result, input);
            if (status != OK) {
                print_err(status);
                return status;
            }
            printf("Reversed string: %s\n", result);
            free(result);
            return OK;
            
        case 'u':
            status = f_upper(&result, input);
            if (status != OK) {
                print_err(status);
                return status;
            }
            printf("String with uppercase odd positions: %s\n", result);
            free(result);
            return OK;

        case 'n':
            status = f_sort(&result, input);
            if (status != OK) {
                print_err(status);
                return status;
            }
            printf("Sorted string: %s\n", result);
            free(result);
            return OK;

        case 'c':
            if (argc < 4) {
                print_err(ERR_ARGS);
                return ERR_ARGS;
            }

            unsigned int seed;
            if (!validate(argv[2], &seed)) {
                print_err(ERR_SEED);
                return ERR_SEED;
            }

            status = f_rand_conc(&result, seed, argc, argv);
            if (status != OK) {
                print_err(status);
                return status;
            }
            printf("Concatenated string: %s\n", result);
            free(result);
            return OK;

        default:
            print_err(ERR_FLAG);
            return ERR_FLAG;
    }
}