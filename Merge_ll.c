/*
Given two sorted linked lists, write a program to merge them into one sorted linked list. Implement functions to create the linked lists, merge them, and display the resulting linked list. Provide test cases to show how the merge operation works.
*/

#include<stdio.h>
#include<stdlib.h>

struct Node{
  int data;
  struct Node *next;
};

typedef struct Node Node;

Node* getNode(){
  Node *newNode = (Node*)malloc(sizeof(Node));
  return newNode;
}

Node* insert(Node *head,int element){
  Node *newNode = getNode();
  if(newNode == NULL){
    printf("\nInsufficient Memory\n");
    return head;
  }

  newNode->data = element;
  newNode->next = NULL;
  if(head == NULL){
    return newNode;
  }

  Node *temp=head;
  while(temp->next!=NULL){
    temp = temp->next;
  }
  temp->next = newNode;

  return head;
}

Node* fill(Node *head,int n){
  printf("\nEnter the elements in ascending order\n");
  int element;
  for(int i=0;i<n;i++){
    scanf("%d",&element);
    head = insert(head,element);
  }
  return head;
}

Node* merge(Node *head1,Node *head2){
  Node *head3 = NULL;

  Node *t1 = head1;
  Node *t2 = head2;

  while(t1 != NULL && t2 != NULL){
    if(t1->data < t2->data){
      head3 = insert(head3,t1->data);
      t1 = t1->next;
    }else if(t1->data > t2->data){
      head3 = insert(head3,t2->data);
      t2 = t2->next;
    }else{
      head3 = insert(head3,t1->data);
      head3 = insert(head3,t2->data);
      t1 = t1->next;
      t2 = t2->next;
    }
  }

  while(t1 != NULL){
    head3 = insert(head3,t1->data);
    t1 = t1->next;
  }

  while(t2 != NULL){
    head3 = insert(head3,t2->data);
    t2 = t2->next;
  }

  return head3;
}

void display(Node *head){
  if(head == NULL){
    printf("\nList is empty\n");
    return;
  }

  Node *temp;
  temp = head;
  while(temp!=NULL){
    printf("%d ",temp->data);
    temp = temp->next;
  }
}

void main(){
  Node *head1 = NULL,*head2 = NULL,*head3;
  int n1,n2;

  printf("Enter the no: of elements in first linked list\n");
  scanf("%d",&n1);
  head1 = fill(head1,n1);

  printf("\nEnter the no: of elements in second linked list\n");
  scanf("%d",&n2);
  head2 = fill(head2,n2);

  head3 = merge(head1,head2);

  printf("\nFirst Linked list: ");
  display(head1);
  printf("\nSecond linked list: ");
  display(head2);
  printf("\nMerged list: ");
  display(head3);
}