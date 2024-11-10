/*
10.
Convert a given binary tree into a doubly linked list in in-order traversal.
*/
#include<stdio.h>
#include<stdlib.h>
#define MAX_SIZE 100
struct Node{
    int data;
    struct Node* prev;
    struct Node* next;
};

struct Node* getNode(int x){
    struct Node* temp = (struct Node*)malloc(sizeof(struct Node));
    temp->data = x;
    temp->next = NULL;
    temp->prev = NULL;
}

struct Tree{
    int data;
    struct Tree* lchild;
    struct Tree* rchild;
};

struct Queue{
    struct Tree* a[MAX_SIZE];
    int front;
    int rear;
};

struct Stack{
    struct Tree* a[MAX_SIZE];
    int top;
};

void CreateS(struct Stack* S){
    S->top = -1;
}

void Push(struct Stack*S, struct Tree* node){
    if(S->top == MAX_SIZE - 1){
        printf("\nStack is Full");
    }
    else{
        S->a[++S->top] = node;
    }
}

struct Tree* Pop(struct Stack* S){
    struct Tree* node;
    if(S->top == -1){
        printf("\nThe stack is Empty");
    }
    else{
        node = S->a[S->top--];
    }
    return node;
}

void CreateQ(struct Queue* Q){
    Q->front =-1;
    Q->rear =-1;
}

void Enqueue(struct Queue* Q, struct Tree* node){
    if(Q->rear == MAX_SIZE){
        printf("\nQueue is Full");
    }
    else if(Q->front == -1){
        Q->front = Q->rear = 0;
        Q->a[Q->rear] = node;
    }
    else{
        Q->rear++;
        Q->a[Q->rear] = node;
    }
}

struct Tree* Dequeue(struct Queue* Q){
    struct Tree* node = NULL;
    if(Q->front == -1){
        printf("\nQueue is Empty");
    }
    else if(Q->front == Q->rear){
        node = Q->a[Q->front];
        Q->front = Q->rear = -1;
    }
    else{
        node = Q->a[Q->front];
        Q->front++;
    }
    return node;
}

int isEmpty(struct Stack* S){
    if(S->top == -1){
        return 1;
    }
    else{
        return 0;
    }
}

struct Tree* getTree(int x){
    struct Tree* temp = (struct Tree*)malloc(sizeof(struct Tree));
    temp->data = x;
    temp->lchild = NULL;
    temp->rchild = NULL;
}



struct Tree* Insert_BT(struct Tree* root, int data){
    struct Tree* new = getTree(data);
    struct Queue Q;
    struct Tree* curr;
    CreateQ(&Q);
    if(root == NULL){
        root = new;
        return root;
    }
    Enqueue(&Q, root);
    while(1){
        curr = Dequeue(&Q);
        if(curr->lchild != NULL && curr->rchild != NULL){
            Enqueue(&Q, curr->lchild);
            Enqueue(&Q, curr->rchild);
        }
        else if(curr->lchild == NULL){
            curr->lchild = new;
            break;
        }
        else if(curr->rchild == NULL){
            curr->rchild = new;
            break;
        }
    }
    return root;
}

struct Node* Insert_LL(struct Tree* root, struct Node* head){
    struct Tree* curr = root;
    struct Node* temp = NULL;
    struct Node* new;
    struct Stack S;
    CreateS(&S);
    while(curr != NULL || !isEmpty(&S)){
        while(curr != NULL){
            Push(&S, curr);
            curr = curr->lchild;
        }
        curr = Pop(&S);
        new = getNode(curr->data);
        if(head == NULL){
            head = new;
            temp = head;
        }
        else{
            temp->next = new;
            new->prev = temp;
            temp = temp->next;
        }
        curr = curr->rchild;
    }
    return head;
}

void Display_BT(struct Tree* root){
    if(root){
        Display_BT(root->lchild);
        printf("%d ", root->data);
        Display_BT(root->rchild);
    }
}

void Display_LL(struct Node* head){
    struct Node* temp = head;
    while(temp != NULL){
        printf("%d ", temp->data);
        temp = temp->next;
    }
}

int main(){
    struct Node* head = NULL;
    struct Tree* root = NULL;
    int repeat = 1;
    int op;
    int data;
    while(repeat){
        printf("\n1.Add an Element to Binary Tree\n2.Convert BinaryTree to Doubly LikedList\n3.Exit\nEnter the operation to be done:");
        scanf("%d", &op);
        switch(op){
            case 1:
                printf("\nEnter the element to insert:");
                scanf("%d", &data);
                root = Insert_BT(root, data);
                printf("\nBinary Tree: ");
                Display_BT(root);
                break;
            case 2:
                printf("\nConverted Doubly linked list: ");
                head = Insert_LL(root, head);
                Display_LL(head);
                head = NULL;
                break;
            case 3:
                printf("\nCode Exited!!\n");
                exit(0);
            default:
                printf("\nInvalid Operation");
        }
    }
}
