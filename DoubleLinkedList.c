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
    // Allocate a new node
    Node * node = (Node *)malloc(sizeof(Node));
    node->value = value;
    node->previous = NULL;
    node->next = NULL;
    return(node);
}

DoubleLinkedList * new_list() {
    // Allocate a new list
    DoubleLinkedList * list = (DoubleLinkedList *)malloc(sizeof(DoubleLinkedList));
    list->length = 0;
    list->head = NULL;
    list->tail = NULL;
    return(list);
}

void append(DoubleLinkedList **list, int value) {
    // Append nodes to the tail of the list
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
    // Prepend nodes to the head of the list
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
    // Print the contents of the list
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

Node * pop(DoubleLinkedList **list) {
    // Remove the first element of the list and return a pointer to it
    DoubleLinkedList * ptr = *list;
    Node * node;
    // Book-keeping actions depend on the number of nodes in the list
    switch (ptr->length) {
        case 0:
            // Empty list so we return NULL
            return(NULL);
        case 1:
            // Only one node in the list, so we must also ensure that both
            // the head and the tail are properly updated
            node = ptr->head;
            ptr->head = NULL;
            ptr->tail = NULL;
            (ptr->length)--;
            return(node);
        default:
            // Two or more nodes in the list so we default to ensuring the
            // head points to the new head and the head's previous pointer is
            // updated
            node = ptr->head;
            ptr->head = node->next;
            ptr->head->previous = NULL;
            (ptr->length)--;
            return(node);
    }
}

Node * rpop(DoubleLinkedList **list) {
    // Remove the last element of the list and return a pointer to it
    DoubleLinkedList * ptr = *list;
    Node * node;
    switch (ptr->length) {
        case 0:
            // Empty list so we return NULL
            return(NULL);
        case 1:
            // Only one node in the list, so we must also ensure that both
            // the head and the tail are properly updated
            node = ptr->tail;
            ptr->head = NULL;
            ptr->tail = NULL;
            (ptr->length)--;
            return(node);
        default:
            // Two or more nodes in the list so we default to ensuring the
            // tail points to the new tail and the tail's next pointer is
            // updated
            node = ptr->tail;
            ptr->tail = node->previous;
            ptr->tail->next = NULL;
            (ptr->length)--;
            return(node);
    }
}

int main(int argc, char **argv) {
    // used to hold node pointers returned by pop and rpop
    Node *node;
    // flag to flip between pop and rpop
    int flag = 1;
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

    // Alternation bewteen pop() and rpop() calls until the list is empty
    while(list->head != NULL) {
        if (flag == 1) {
            node = pop(&list);
            flag = 0;
            printf("pop() called: ");
        }
        else {
            node = rpop(&list);
            flag = 1;
            printf("rpop() called: ");
        }
        print_list(&list);
        printf("Node %d was returned ", node->value);
        free(node);
        printf("and freed.\n");
    }
}
