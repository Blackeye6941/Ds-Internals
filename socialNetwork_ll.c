/*
Design a simplified social network where each user has a list of friends. Implement the following:
1. A singly linked list to store a user’s friends.
2. Functions to add a new friend, remove a friend, and display the list of friends.
3. Create a function to merge two users' friend lists into one, eliminating duplicates.
4. Demonstrate the operations with sample data.
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct Node{
  char name[20];
  struct Node *next;
};

typedef struct Node Friend;

Friend* createFriend(){
  Friend *newFriend = (Friend*)malloc(sizeof(Friend));
  return newFriend;
}

Friend* addFriend(Friend *User,char name[]){
  Friend* newFriend = createFriend();
  strcpy(newFriend->name,name);
  newFriend->next = NULL;

  Friend *temp = User;
  while(temp->next != NULL){
    temp = temp->next;
  }

  temp->next = newFriend;
  return User;
}

Friend* removeFriend(Friend *User,char name[]){
  Friend *temp = User;
  while(temp->next != NULL && strcmp(temp->next->name,name) != 0){
    temp = temp->next;
  }

  if(temp->next == NULL){
    printf("No matching friend\n");
  }else{
    Friend *friend = temp->next;
    temp->next = temp->next->next;
    free(friend);
    printf("Friend removed successfully\n");
  }
  return User;
}

int isPresent(Friend *User,char name[]){
  Friend *temp = User->next;
  while(temp != NULL){
    if(strcmp(temp->name,name) == 0){
      return 1;
    }
    temp = temp->next;
  }
  return 0;
}

Friend *merge(Friend *User1,Friend *User2){
  Friend *User3 = createFriend();
  strcpy(User3->name,"Friends");
  User3->next = NULL;
  Friend *temp = User1->next;

  while(temp != NULL){
    User3 = addFriend(User3,temp->name);
    temp = temp->next;
  }

  temp = User2->next;
  while(temp != NULL){
    if(!isPresent(User3,temp->name)){
      User3 = addFriend(User3,temp->name);
    }
    temp = temp->next;
  }
  return User3;
}

int findIndex(Friend *Users[],char name[],int n){
  for(int i=0;i<n;i++){
    if(strcmp(Users[i]->name,name) == 0){
      return i;
    }
  }
  return -1;
}

void display(Friend *User){
  if(User->next == NULL){
    printf("\nNo friends\n");
  }else{
    printf("\n");
    Friend *temp = User->next;
    while(temp != NULL){
      printf("%s\n",temp->name);
      temp = temp->next;
    }
  }
}

void updateUser(Friend *Users[],int i){
  char name[20];
  int c;
  do{
    printf("\nEnter a choice\n");
    printf("1.Add friend\n");
    printf("2.Remove friend\n");
    printf("3.Display\n");
    printf("4.Back to main menu\n");

    scanf("%d",&c);

    switch(c){
      case 1: printf("\nEnter the friend name: ");
              scanf("%s",name);
              Users[i] = addFriend(Users[i],name);
              printf("Friend added successfully\n");
      break;

      case 2: printf("\nEnter the friend name: ");
              scanf("%s",name);
              Users[i] = removeFriend(Users[i],name);
      break;

      case 3: display(Users[i]);
      break;

      case 4: return;

      default: printf("\nEnter a correct option\n");
    }
  }while(1);
}

void main(){
  Friend *Users[20];
  int i=0,l;

  do{
    printf("\nEnter a choice\n");
    printf("1.Add User\n");
    printf("2.Update User\n");
    printf("3.Merge users\n");
    printf("4.Display\n");
    printf("5.Exit\n");

    int c;
    char name[20];
    scanf("%d",&c);

    switch(c){
      case 1: printf("\nEnter the user name: ");
              scanf("%s",name);
              Users[i] = createFriend();
              strcpy(Users[i]->name,name);
              Users[i]->next = NULL;
              updateUser(Users,i);
              i++;
      break;

      case 2: printf("\nEnter the name of user to update: ");
              scanf("%s",name);
              l = findIndex(Users,name,i);
              if(l == -1){
                printf("User does not exist\n");
              }else{
                updateUser(Users,l);
              }
      break;

      case 3: printf("\nEnter the name of users to merge\n");
              char name1[20];
              char name2[20];
              scanf("%s",name1);
              scanf("%s",name2);

              int j = findIndex(Users,name1,i);
              int k = findIndex(Users,name2,i);

              if(j==-1 || k==-1){
                printf("\nUser does not exists\n");
              }else{
                Friend *User = merge(Users[j],Users[k]);
                display(User);
              }
      break;

      case 4: printf("\nEnter the name of user to display: ");
              scanf("%s",name);
              l = findIndex(Users,name,i);
              if(l == -1){
                printf("User does not exist\n");
              }else{
                display(Users[l]);
              }
      break;

      case 5: exit(0);

      default: printf("\nEnter a correct option\n");
    }
  }while(1);
}