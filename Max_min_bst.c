/*
9.
Implement efficient algorithms to find the maximum and minimum values in a BST.
*/

#include<stdio.h>
#include<stdlib.h>

struct Node{
  int info;
  struct Node *leftChild,*rightChild;
};

typedef struct Node Node;

Node* getNode(){
  Node *newNode = (Node*)malloc(sizeof(Node));
  return newNode;
}

Node* insert(Node *root,int data){
  Node *newNode = getNode(); 
  if(newNode == NULL){
    printf("\nInsufficient memory\n");
    return root;
  }

  newNode->info = data;
  newNode->leftChild = NULL;
  newNode->rightChild = NULL;
  if(root == NULL){
    return newNode;
  }

  Node *temp = root;
  while(1){
    if(data < temp->info){
      if(temp->leftChild != NULL){
        temp = temp->leftChild;
      }else{
        temp->leftChild = newNode;
        break;
      }
    }else if(data > temp->info){
      if(temp->rightChild != NULL){
        temp = temp->rightChild;
      }else{
        temp->rightChild = newNode;
        break;
      }
    }else{
      printf("\nElement already exists\n");
      free(newNode);
      break;
    }
  }
  return root;
}

int succ(Node *temp){
  temp = temp->rightChild;
  while(temp->leftChild != NULL){
    temp = temp->leftChild;
  }
  return temp->info;
}

Node* delete(Node *root,int data){
  Node *temp = root,*parent = NULL;

  if(root == NULL){
    printf("\nTree is empty\n");
    return root;
  }

  while(temp != NULL){
    if(data > temp->info){
      parent = temp; 
      temp = temp->rightChild;
    }else if(data < temp->info){
      parent = temp;
      temp = temp->leftChild;
    }else{
      break;
    }
  }

  if(temp == NULL){
    printf("\nElement not found\n");
    return root;
  }else if(parent == NULL){
    if(temp->rightChild == NULL){
      root = root->leftChild;
      free(temp);
      return root;
    }else if(temp->leftChild == NULL){
      root = root->rightChild;
      free(temp);
      return root;
    }
  }

  if(temp->leftChild == NULL && temp->rightChild == NULL){
    if(parent->leftChild == temp){
      parent->leftChild = NULL;
    }else{
      parent->rightChild = NULL;
    }
    free(temp);
  }else if(temp->leftChild != NULL && temp->rightChild != NULL){
    int item = succ(temp);
    root = delete(root,item);
    temp->info = item;
  }else{
    if(temp->leftChild != NULL){
      if(parent->leftChild == temp){
        parent->leftChild = temp->leftChild;
      }else{
        parent->rightChild = temp->leftChild;
      }
    }else{
      if(parent->leftChild == temp){
        parent->leftChild = temp->rightChild;
      }else{
        parent->rightChild = temp->rightChild;
      }
      free(temp);
    }
  }
  
  return root;
}

int findMax(Node *root){
  Node *temp = root;
  while(temp->rightChild != NULL){
    temp = temp->rightChild;
  }
  return temp->info;
}

int findMin(Node *root){
  Node *temp = root;
  while(temp->leftChild != NULL){
    temp = temp->leftChild;
  }
  return temp->info;
}

void display(Node *root){
  if(root != NULL){
    display(root->leftChild);
    printf("%d ",root->info);
    display(root->rightChild);
  }
}

void main(){
  Node *root =  NULL;
  do{
    printf("\nEnter a choice\n");
    printf("1.Insert\n");
    printf("2.Delete\n");
    printf("3.Display\n");
    printf("4.Find maximum element\n");
    printf("5.Find minimum element\n");
    printf("6.Exit\n");

    int a,c,max,min;
    scanf("%d",&c);

    switch(c){
      case 1: printf("\nEnter an element: ");
              scanf("%d",&a);
              root = insert(root,a);
      break;

      case 2: printf("\nEnter an element to delete: ");
              scanf("%d",&a);
              root = delete(root,a);
      break;

      case 3: printf("\n");
              if(root == NULL){
                printf("Tree is empty");
              }else{
                display(root);
              }
              printf("\n");
      break;

      case 4: printf("\n");
              if(root == NULL){
                printf("Tree is empty");
              }else{
                max = findMax(root);
                printf("Maximum element: %d",max);
              }
              printf("\n");
      break;

      case 5: printf("\n");
              if(root == NULL){
                printf("Tree is empty");
              }else{
                min = findMin(root);
                printf("Minimum element: %d",min);
              }
              printf("\n");
      break;

      case 6: exit(0);

      default: printf("\nEnter a correct choice\n");
    }
  }while(1);
}