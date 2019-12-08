#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node *previous;
    struct Node *next;
} Node;

typedef struct DoubleLinkedList {
    Node * head;
    Node * tail;
    int length;
} DoubleLinkedList;

Node * new_node(int value) {
    Node * node = (Node *)malloc(sizeof(Node));
    node->value = value;
    node->previous = NULL;
    node->next = NULL;
    return(node);
}

DoubleLinkedList * new_list() {
    DoubleLinkedList * list = (DoubleLinkedList *)malloc(sizeof(DoubleLinkedList));
    list->length = 0;
    list->head = NULL;
    list->tail = NULL;
    return(list);
}

void append(DoubleLinkedList **list, int value) {
    DoubleLinkedList * ptr = *list;
    Node * node = new_node(value);
    if (ptr->length == 0) {
        ptr->head = node;
        ptr->tail = node;
        (ptr->length)++;
    }
    else {
        node->previous = ptr->tail;
        ptr->tail->next = node;
        ptr->tail = node;
        (ptr->length)++;
    }
}

void prepend(DoubleLinkedList **list, int value) {
    DoubleLinkedList * ptr = *list;
    Node * node = new_node(value);
    if (ptr->length == 0) {
        ptr->head = node;
        ptr->tail = node;
        (ptr->length)++;
    }
    else {
        node->next = ptr->head;
        ptr->head->previous = node;
        ptr->head = node;
        (ptr->length)++;
    }
}

void print_list(DoubleLinkedList **list) {
    Node * ptr = (*list)->head;
    printf("[");
    if (ptr != NULL) {
        while (ptr->next != NULL) {
            printf("%d ", ptr->value);
            ptr = ptr->next;
        }
        printf("%d", ptr->value);
    }
    printf("]\n");
}

int main(int argc, char **argv) {
    // create a new list
    DoubleLinkedList * list = new_list();
    printf("Current list is: ");
    print_list(&list);
    // append some nodes to the list
    for (int i = 0; i < 10; i++) {
        printf("Append %d\n", i);
        append(&list, i);
        printf("Current list is: ");
        print_list(&list);
    }
    // prepend some nodes to the list
    for (int i = 1; i < 10; i++) {
        printf("Prepend %d\n", i);
        prepend(&list, i);
        printf("Current list is: ");
        print_list(&list);
    }
}
