#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_NAME_LENGTH 100
#define NUM_EXAMS 5

typedef struct {
    unsigned int id;
    char name[MAX_NAME_LENGTH];
    char surname[MAX_NAME_LENGTH];
    char group[MAX_NAME_LENGTH];
    unsigned char grades[NUM_EXAMS];
} Student;

typedef enum {
    SUCCESS,
    ERROR_MEMORY,
    ERROR_FILE_OPEN,
    ERROR_INVALID_INPUT
} Status;

Status readStudentsFromFile(const char* filename, Student** students, int* count) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Error opening file\n");
        return ERROR_FILE_OPEN;
    }

    *count = 0;
    *students = NULL;

    while (!feof(file)) {
        Student student;
        if (fscanf(file, "%u %s %s %s", &student.id, student.name, student.surname, student.group) != 4) {
            fclose(file);
            fprintf(stderr, "Invalid input format\n");
            return ERROR_INVALID_INPUT;
        }
        for (int i = 0; i < NUM_EXAMS; i++) {
            if (fscanf(file, " %hhu", &student.grades[i]) != 1) {
                fclose(file);
                fprintf(stderr, "Invalid input format\n");
                return ERROR_INVALID_INPUT;
            }
        }

        (*count)++;
        *students = (Student*)realloc(*students, (*count) * sizeof(Student));
        if (!*students) {
            fclose(file);
            fprintf(stderr, "Memory allocation error\n");
            return ERROR_MEMORY;
        }
        (*students)[(*count) - 1] = student;
    }

    fclose(file);
    return SUCCESS;
}

int compareById(const void* a, const void* b) {
    return ((Student*)a)->id - ((Student*)b)->id;
}

int compareBySurname(const void* a, const void* b) {
    return strcmp(((Student*)a)->surname, ((Student*)b)->surname);
}

int compareByName(const void* a, const void* b) {
    return strcmp(((Student*)a)->name, ((Student*)b)->name);
}

int compareByGroup(const void* a, const void* b) {
    return strcmp(((Student*)a)->group, ((Student*)b)->group);
}

Status printStudent(FILE* file, Student* student) {
    if (fprintf(file, "ID: %u, Name: %s %s, Group: %s, Average Grade: %.2f\n",
                student->id, student->name, student->surname, student->group,
                (float)(student->grades[0] + student->grades[1] + student->grades[2] + student->grades[3] + student->grades[4]) / NUM_EXAMS) < 0) {
        fprintf(stderr, "Error writing student data\n");
        return ERROR_INVALID_INPUT;
    }
    return SUCCESS;
}

Status interactiveDialog(Student* students, int count, const char* traceFile) {
    FILE* trace = fopen(traceFile, "a");
    if (!trace) {
        fprintf(stderr, "Error opening trace file\n");
        return ERROR_FILE_OPEN;
    }

    while (1) {
        fprintf(stderr, "1. Search by ID\n");
        fprintf(stderr, "2. Search by Surname\n");
        fprintf(stderr, "3. Search by Name\n");
        fprintf(stderr, "4. Search by Group\n");
        fprintf(stderr, "5. Sort by ID\n");
        fprintf(stderr, "6. Sort by Surname\n");
        fprintf(stderr, "7. Sort by Name\n");
        fprintf(stderr, "8. Sort by Group\n");
        fprintf(stderr, "9. Print student by ID to trace file\n");
        fprintf(stderr, "10. Print students with above average grades to trace file\n");
        fprintf(stderr, "0. Exit\n");

        int choice;
        scanf("%d", &choice);

        if (choice == 0) break;

        switch (choice) {
            case 1: {
                unsigned int id;
                fprintf(stderr, "Enter ID: ");
                scanf("%u", &id);
                for (int i = 0; i < count; i++) {
                    if (students[i].id == id) {
                        printStudent(stdout, &students[i]);
                        break;
                    }
                }
                break;
            }
            case 2: {
                char surname[MAX_NAME_LENGTH];
                fprintf(stderr, "Enter Surname: ");
                scanf("%s", surname);
                for (int i = 0; i < count; i++) {
                    if (strcmp(students[i].surname, surname) == 0) {
                        printStudent(stdout, &students[i]);
                    }
                }
                break;
            }
            case 3: {
                char name[MAX_NAME_LENGTH];
                fprintf(stderr, "Enter Name: ");
                scanf("%s", name);
                for (int i = 0; i < count; i++) {
                    if (strcmp(students[i].name, name) == 0) {
                        printStudent(stdout, &students[i]);
                    }
                }
                break;
            }
            case 4: {
                char group[MAX_NAME_LENGTH];
                fprintf(stderr, "Enter Group: ");
                scanf("%s", group);
                for (int i = 0; i < count; i++) {
                    if (strcmp(students[i].group, group) == 0) {
                        printStudent(stdout, &students[i]);
                    }
                }
                break;
            }
            case 5:
                qsort(students, count, sizeof(Student), compareById);
                fprintf(stderr, "Sorted by ID\n");
                break;
            case 6:
                qsort(students, count, sizeof(Student), compareBySurname);
                fprintf(stderr, "Sorted by Surname\n");
                break;
            case 7:
                qsort(students, count, sizeof(Student), compareByName);
                fprintf(stderr, "Sorted by Name\n");
                break;
            case 8:
                qsort(students, count, sizeof(Student), compareByGroup);
                fprintf(stderr, "Sorted by Group\n");
                break;
            case 9: {
                unsigned int id;
                fprintf(stderr, "Enter ID: ");
                scanf("%u", &id);
                for (int i = 0; i < count; i++) {
                    if (students[i].id == id) {
                        if (printStudent(trace, &students[i]) == SUCCESS) {
                            fprintf(stdout, "Student data written to trace file\n");
                        } else {
                            fprintf(stdout, "Error writing student data to trace file\n");
                        }
                        break;
                    }
                }
                break;
            }
            case 10: {
                float totalAverage = 0.0;
                for (int i = 0; i < count; i++) {
                    totalAverage += (students[i].grades[0] + students[i].grades[1] + students[i].grades[2] + students[i].grades[3] + students[i].grades[4]) / NUM_EXAMS;
                }
                totalAverage /= count;

                for (int i = 0; i < count; i++) {
                    float average = (students[i].grades[0] + students[i].grades[1] + students[i].grades[2] + students[i].grades[3] + students[i].grades[4]) / NUM_EXAMS;
                    if (average > totalAverage) {
                        if (fprintf(trace, "Surname: %s, Name: %s\n", students[i].surname, students[i].name) < 0) {
                            fprintf(stderr, "Error writing student data to trace file\n");
                        }
                    }
                }
                fprintf(stderr, "Students with above average grades written to trace file\n");
                break;
            }
            default:
                fprintf(stderr, "Invalid choice\n");
        }
    }

    fclose(trace);
    return SUCCESS;
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        fprintf(stdout, "Usage: ./a.out <input_file> <trace_file>\n");
        return ERROR_INVALID_INPUT;
    }

    Student* students;
    int count;

    Status status = readStudentsFromFile(argv[1], &students, &count);
    if (status != SUCCESS) {
        fprintf(stderr, "Error reading file\n");
        return -1;
    }

    status = interactiveDialog(students, count, argv[2]);
    if (status != SUCCESS) {
        fprintf(stderr, "Error during interactive dialog\n");
    }

    free(students);
    return 0;
}