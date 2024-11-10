/*
6.
Implement a program to reverse a singly linked list.
Write functions to create the linked list, reverse it, and display the list before and after reversal. Demonstrate your solution with sample data.*/



#include<stdio.h>
#include<stdlib.h>

struct Node {
    int data;
    struct Node *next;
};

struct Node *GetNode() {
    struct Node *N = (struct Node*)malloc(sizeof(struct Node));
    return N;
}

struct Node *create(int n) {
    struct Node *head = NULL, *temp = NULL;
    struct Node *newNode;
    int data, i = 0;

    for (i = 0; i < n; i++) {
        printf("Enter data: ");
        scanf("%d", &data);

        newNode = GetNode();
        if (newNode == NULL) {
            printf("Failed to allocate memory.\n");
            return NULL;
        }

        newNode->data = data;
        newNode->next = NULL;

        if (head == NULL) {
            head = newNode;
        } else {
            temp->next = newNode;
        }
        temp = newNode;
    }
    return head;
}

void rev(struct Node *head) {
    if (head == NULL) {
        return;
    }
    rev(head->next);
    printf("%d\t", head->data);
}

void display(struct Node *head) {
    struct Node *temp = head;
    while (temp != NULL) {
        printf("%d\t", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

int main() {
    struct Node *head = NULL;
    int nodes = 0;

    printf("Enter the number of nodes: ");
    scanf("%d", &nodes);

    head = create(nodes);
    
    printf("Original Linked List:\n");
    display(head);

    printf("Reversed Linked List (using recursion):\n");
    rev(head);

    return 0;
}