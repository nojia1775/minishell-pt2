#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char *data;
    struct Node *next;
} Node;

Node* createNode(const char *data) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->data = strdup(data);
    newNode->next = NULL;
    return newNode;
}

void appendNode(Node **head, const char *data) {
    Node *newNode = createNode(data);
    if (*head == NULL) {
        *head = newNode;
    } else {
        Node *temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

void printList(Node *head) {
    Node *temp = head;
    while (temp != NULL) {
        printf("%s\n", temp->data);
        temp = temp->next;
    }
}

void freeList(Node *head) {
    Node *temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp->data);
        free(temp);
    }
}

void splitStringToList(const char *str, Node **head) {
    const char *start = str;
    char *token = NULL;
    int in_quotes = 0;
    char quote_char = '\0';

    while (*str) {
        if (!in_quotes && (*str == ' ' || *str == '\0')) {
            if (str > start) {
                token = strndup(start, str - start);
                appendNode(head, token);
                free(token);
            }
            start = str + 1;
        } else if ((*str == '"' || *str == '\'') && (in_quotes == 0 || *str == quote_char)) {
            if (in_quotes) {
                in_quotes = 0;
                token = strndup(start, str - start + 1);
                appendNode(head, token);
                free(token);
                start = str + 1;
            } else {
                in_quotes = 1;
                quote_char = *str;
                start = str;
            }
        }
        str++;
    }
    if (str > start) {
        token = strndup(start, str - start);
        appendNode(head, token);
        free(token);
    }
}

int main(int argc, char **argv) {
    Node *head = NULL;

    splitStringToList(argv[1], &head);
    printList(head);
    freeList(head);

    return 0;
}