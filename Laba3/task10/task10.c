#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 10

typedef struct Node {
    char data;
    struct Node* children[MAX];
    int childCount;
} Node;

typedef enum {
    SUCCESS,
    ERROR_MEMORY,
    ERROR_FILE_OPEN,
    ERROR_FILE_CLOSE,
    ERROR_INVALID_EXPRESSION
} Status;

Node* createNode(char data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) return NULL;

    newNode->data = data;
    newNode->childCount = 0;
    memset(newNode->children, 0, sizeof(newNode->children));
    return newNode;
}

Status addChild(Node* parent, Node* child) {
    if (parent->childCount < MAX) {
        parent->children[parent->childCount++] = child;
        return SUCCESS;
    }
    return ERROR_INVALID_EXPRESSION;
}

Node* buildTree(const char* expression) {
    Node* stack[100];
    int stackTop = -1; 
    Node* current = NULL;
    Node* root = NULL;

    for (int i = 0; expression[i] != '\0'; i++) {
        char currentChar = expression[i];

        if (currentChar >= 'A' && currentChar <= 'Z') {
            Node* newNode = createNode(currentChar);
            if (!newNode) return NULL;

            if (stackTop >= 0) {
                if (addChild(stack[stackTop], newNode) != SUCCESS) return NULL;
            } else {
                root = newNode;
            }
            current = newNode;
        } else if (currentChar == '(') {
            stack[++stackTop] = current;
        } else if (currentChar == ')') {
            stackTop--; 
        }
    }
    return root;
}

Status printTree(Node* node, int depth, int isLastChild[]) {
    if (node == NULL) return SUCCESS;

    for (int i = 0; i < depth; i++) {
        if (isLastChild[i])
            printf("    ");
        else
            printf("│   ");
    }

    if (depth > 0) {
        if (isLastChild[depth - 1])
            printf("└── "); 
        else
            printf("├── ");
    }

    printf("%c\n", node->data); 

    for (int i = 0; i < node->childCount; i++) {
        isLastChild[depth] = (i == node->childCount - 1);
        if (printTree(node->children[i], depth + 1, isLastChild) != SUCCESS) return ERROR_INVALID_EXPRESSION;
    }
    return SUCCESS;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: ./a.out <input_file> <output_file>\n");
        return ERROR_INVALID_EXPRESSION;
    }

    FILE *inputFile = fopen(argv[1], "r");
    if (!inputFile) {
        printf("Error opening input file\n");
        return ERROR_FILE_OPEN;
    }

    FILE *outputFile = freopen(argv[2], "w", stdout);
    if (!outputFile) {
        printf("Error opening output file\n");
        fclose(inputFile);
        return ERROR_FILE_OPEN;
    }

    char buffer[1024];
    int isLastChild[100];

    while (fgets(buffer, sizeof(buffer), inputFile)) {
        buffer[strcspn(buffer, "\n")] = '\0';

        if (strlen(buffer) == 0) continue;

        Node* root = buildTree(buffer);
        if (!root) {
            printf("Error building tree\n");
            continue;
        }

        printf("Expression: %s\n", buffer);
        if (printTree(root, 0, isLastChild) != SUCCESS) {
            printf("Error printing tree\n");
        }
        printf("\n");
    }

    fclose(inputFile);
    fclose(outputFile);
    return SUCCESS;
}