/*
3.
Implement a phone directory using a Binary Search Tree (BST). Your system should allow:
1. Adding new contacts to the directory.
2. Deleting a contact from the directory.
3. Searching for a contact by name.
4. Displaying the directory in sorted order.
5. Demonstrate these operations with test cases showing the structure of the BST before and after each operation.
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct Node{
  char name[20];
  char phNo[11];
  struct Node *leftChild,*rightChild;
};

typedef struct Node Contact;

Contact* createContact(){
  Contact *newContact = (Contact*)malloc(sizeof(Contact));
  return newContact;
}

Contact* addContact(Contact *root,char name[],char phNo[]){
  Contact *newContact = createContact();

  if(newContact == NULL){
    printf("\nInsufficient memory\n");
    return root;
  }
  strcpy(newContact->name,name);
  strcpy(newContact->phNo,phNo);
  newContact->leftChild = NULL;
  newContact->rightChild = NULL;

  if(root == NULL){
    printf("\nContact added succesfully\n");
    return newContact;
  }

  Contact *temp = root;
  while(1){
    if(strcmp(name,temp->name) < 0){
      if(temp->leftChild == NULL){
        temp->leftChild = newContact;
        break;
      }else{
        temp = temp->leftChild;
      }
    }else if(strcmp(name,temp->name) > 0){
      if(temp->rightChild == NULL){
        temp->rightChild = newContact;
        break;
      }else{
        temp = temp->rightChild;
      }
    }else{
      printf("\nContact already exists\n");
      free(newContact);
      return root;
    }
  }
  printf("\nContact added succesfully\n");
  return root;
}

void search(Contact *root,char name[]){
  if(root == NULL){
    printf("\nContact list is empty\n");
    return;
  }

  Contact *temp = root;
  int flag = 0;
  while(temp != NULL){
    if(strcmp(name,temp->name) < 0){
      temp = temp->leftChild;
    }else if(strcmp(name,temp->name) > 0){
      temp = temp->rightChild;
    }else{
      flag = 1;
      break;
    }
  }

  if(flag == 1){
    printf("\nContact found\n");
    printf("Phone no: %s\n",temp->phNo);
  }else{
    printf("\nContact not found\n");
  }
}

void succ(Contact *temp,char name[],char phNo[]){
  temp = temp->rightChild;
  while(temp->leftChild != NULL){
    temp = temp->leftChild;
  }
  strcpy(name,temp->name);
  strcpy(phNo,temp->phNo);
}

Contact* deleteContact(Contact *root,char name[]){
  Contact *temp = root,*parent = NULL;

  if(root == NULL){
    printf("Contact list is empty");
    return root;
  }

  while(temp != NULL){
    if(strcmp(name,temp->name) < 0){
      parent = temp;
      temp = temp->leftChild;
    }else if(strcmp(name,temp->name) > 0){
      parent = temp;
      temp = temp->rightChild;
    }else{
      break;
    }
  }

  if(temp == NULL){
    printf("\nContact is not found\n");
    return root;
  }else if(parent == NULL){            //if contact is in root
    if(temp->leftChild == NULL){
      root = root->rightChild;
      free(temp);
      printf("\nContact deleted succesfully\n");
      return root;
    }else if(temp->rightChild == NULL){
      root = root->leftChild;
      free(temp);
      printf("\nContact deleted succesfully\n");
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
    char newName[20], newPhnNo[11];
    succ(temp,newName,newPhnNo);

    root = deleteContact(root,newName);
    strcpy(temp->name,newName);
    strcpy(temp->phNo,newPhnNo);
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
    }
    free(temp);
  }
  printf("\nContact deleted succesfully\n");
  return root;
}

void display_sorted(Contact *root){
  if(root){
    display_sorted(root->leftChild);
    printf("Name: %s, Phone no: %s \n",root->name,root->phNo);
    display_sorted(root->rightChild);
  }
}

void main(){
  Contact *root = NULL;

  do{
    printf("\nEnter a choice\n");
    printf("1.Add a contact\n");
    printf("2.Delete a contact\n");
    printf("3.Search for a contact\n");
    printf("4.Display contacts in sorted order\n");
    printf("5.Exit\n");

    int c;
    char name[20],phNo[11];
    scanf("%d",&c);

    switch(c){
      case 1: printf("\nEnter the name: ");
              scanf("%s",name);
              printf("Enter the phone no: ");
              scanf("%s",phNo);
              root = addContact(root,name,phNo);
      break;

      case 2: printf("\nEnter the name: ");
              scanf("%s",name);
              root = deleteContact(root,name);
      break;

      case 3: printf("\nEnter the name to search: ");
              scanf("%s",name);
              search(root,name);
      break;

      case 4: printf("\n");
              if(root != NULL){
                display_sorted(root);
              }else{
                printf("Contact list is empty\n");
              }
      break;

      case 5: exit(0);

      default: printf("\nEnter a correct option\n");
    }
  }while(1);
}