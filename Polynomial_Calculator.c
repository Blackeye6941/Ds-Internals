/*
Create a polynomial equation solver that adds and multiplies polynomials represented as linked lists.
*/

#include<stdio.h>
#include<stdlib.h>

struct Node{
  int coeff;
  int exp;
  struct Node *next;
};

typedef struct Node Node;

Node* getNode(){
  Node *newNode = (Node*)malloc(sizeof(Node));
  return newNode;
}

Node* insert(Node *head,int coeff,int exp){
  Node *newNode = getNode();
  if(newNode == NULL){
    printf("\nInsufficient Memory\n");
    return head;
  }

  newNode->coeff = coeff;
  newNode->exp = exp;
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

Node* accept(Node *head,int n){
  int coeff,exp;
  Node *temp = head;
  for(int i=0;i<n;i++){
    printf("\nEnter the exponential: ");
    scanf("%d",&exp);
    printf("Enter the coefficient: ");
    scanf("%d",&coeff);

    if(coeff != 0){
      head = insert(head,coeff,exp);
    }
  }
  return head;
}

Node* addition(Node *P1,Node *P2){
  Node *P3 = NULL;
  Node *t1 = P1;
  Node *t2 = P2;

  while(t1!=NULL && t2!=NULL){
    if(t1->exp > t2->exp){
      P3 = insert(P3,t1->coeff,t1->exp);
      t1 = t1->next;
    }else if(t1->exp < t2->exp){
      P3 = insert(P3,t2->coeff,t2->exp);
      t2 = t2->next;
    }else{
      int coeff = t1->coeff + t2->coeff;
      P3 = insert(P3,coeff,t1->exp);
      t1 = t1->next;
      t2 = t2->next;
    }
  }

  while(t1 != NULL){
    P3 = insert(P3,t1->coeff,t1->exp);
    t1 = t1->next;
  }

  while(t2 != NULL){
    P3 = insert(P3,t2->coeff,t2->exp);
    t2 = t2->next;
  }
  return P3;
}
 
Node* multiplication(Node *P1,Node *P2){
  Node *P3 = NULL;
  Node *t1 = P1;

  while(t1 != NULL){
    Node *t2 = P2;
    while(t2 != NULL){
      int coeff = t1->coeff * t2->coeff;
      int exp = t1->exp + t2->exp;

      Node *temp = P3;
      int flag = 0;
      while(temp != NULL && temp->next != NULL){
        if(temp->next->exp == exp){
          temp->next->coeff += coeff;
          flag = 1;
          break;  
        }else if(temp->next->exp < exp){
          Node *newNode = getNode();
          newNode->exp = exp;
          newNode->coeff = coeff;
          newNode->next = temp->next;
          temp->next = newNode;
          flag = 1;
          break;
        }
        temp = temp->next;
      }

      if(flag == 0){
        P3 = insert(P3,coeff,exp);
      }
      t2 = t2->next;
    }
    t1 = t1->next;
  }
  return P3;
}

void display(Node *head){
  Node *temp = head;
  while(temp != NULL){
    if(temp->coeff == 0){
      temp = temp->next;
      continue;
    }

    if(temp->exp == 0){
      printf("%d",temp->coeff);
    }else if(temp->exp == 1){
      printf("%dx",temp->coeff);
    }else{
      printf("%dx^(%d)",temp->coeff,temp->exp);
    }

    if(temp->next != NULL && temp->next->coeff > 0){
      printf("+");
    }
    temp = temp->next;
  }
  printf("\n");
}

void main(){
  do{
    printf("\nEnter a choice\n");
    printf("1.Addition\n");
    printf("2.Multiplication\n");
    printf("3.Exit\n");

    int a;
    scanf("%d",&a);
    if(a == 3){
      exit(-1);
    }

    int n1,n2;
    Node *P1=NULL,*P2=NULL,*P3=NULL;
    printf("\nEnter the no: of terms in first polynomial\n");
    scanf("%d",&n1);
    printf("\nFirst polynomial\n");
    P1 = accept(P1,n1);

    printf("\nEnter the no: of terms in second polynomial\n");
    scanf("%d",&n2);
    printf("\nSecond polynomial\n");
    P2 = accept(P2,n2);

    switch(a){
      case 1: P3 = addition(P1,P2);
      break;

      case 2: P3 = multiplication(P1,P2);
      break;

      default: printf("Enter a correct option");
    }

    printf("\nFirst polynomial: ");
    display(P1);
    printf("Second polynomial: ");
    display(P2);
    printf("Result polynomial: ");
    display(P3);
  }while(1);
}
