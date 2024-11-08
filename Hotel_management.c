/*
Create an efficient data structure to manage bookings in a hotel management system, ensuring easy insertion, deletion, searching, and retrieval of booking information.
Requirements:
  Design a data structure to store booking information, including:
  Booking ID (unique identifier)
  Guest name
  Room number
  Check-in date
  Check-out date
  Room type (single, double, suite)
Implement functions for:
  Inserting new bookings
  Deleting existing bookings
  Searching bookings by booking ID or room number
  Retrieving booking information by booking ID
  Updating booking status
  Displaying all bookings
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

struct Node{
  char name[20],check_in[20],check_out[20],room_type[20];
  int id,room_no;
  struct Node *next;
  struct Node *prev;
};

typedef struct Node Room;

Room* getRoom(){
  Room *newRoom = (Room*)malloc(sizeof(Room));
  return newRoom;
}

int idExists(Room *bookings, int id){
  Room *temp = bookings;
  while(temp != NULL){
    if(temp->id == id){
      return 1;
    }
    temp = temp->next;
  }
  return 0;
}

void display(Room *booking){
  printf("\nBooking id: %d\n",booking->id);
  printf("Guest name: %s\n",booking->name);
  printf("Room number: %d\n",booking->room_no);
  printf("Check-in date: %s\n",booking->check_in);
  printf("Check-out date: %s\n",booking->check_out);
  printf("Room type: %s\n",booking->room_type);
}

Room* insert(Room *bookings,char name[],int room_no,char check_in[],char check_out[],char room_type[]){
  Room *newRoom = getRoom();
  if(newRoom == NULL){
    printf("\nInufficient memory\n");
    return bookings;
  }

  int id;
  do{
    id = rand() % 90000 + 10000;
  }while (idExists(bookings, id));

  newRoom->id = id;
  strcpy(newRoom->name,name);
  newRoom->room_no = room_no;
  strcpy(newRoom->check_in,check_in);
  strcpy(newRoom->check_out,check_out);
  strcpy(newRoom->room_type,room_type);
  newRoom->next = NULL;

  if(bookings == NULL){
    newRoom->prev = NULL;
    printf("\nRoom booked successfully\n");
    display(newRoom);
    return newRoom;
  }

  Room *temp = bookings;
  while(temp->next != NULL){
    temp = temp->next;
  }
  temp->next = newRoom;
  newRoom->prev = temp;

  printf("\nRoom booked successfully\n");
  display(newRoom);
  return bookings;
}

Room* searchId(Room *bookings,int id){
  Room *temp = bookings;
  while(temp != NULL && temp->id != id){
    temp = temp->next;
  }
  return temp;
}

Room* searchRoom(Room *bookings,int room_no){
  Room *temp = bookings;
  while(temp != NULL && temp->room_no != room_no){
    temp = temp->next;
  }
  return temp;
}

void retrieveBooking(Room *bookings,int id){
  Room *temp = searchId(bookings,id);
  if(temp == NULL){
    printf("\nBooking not found\n");
  }else{
    display(temp);
  }
}

Room* delete(Room *bookings,int id){
  Room *temp = searchId(bookings,id);
  if(temp == NULL){
    printf("\nBooking not found\n");
  }else{
    if(temp->prev == NULL){
      bookings = bookings->next;
      if(bookings != NULL){
        bookings->prev = NULL;
      }
    }else{
      temp->prev->next = temp->next;
      if(temp->next != NULL){
        temp->next->prev = temp->prev;
      }
    }
    printf("\nBooking deleted successfully\n");
    free(temp);
  }
  return bookings;
}

void update(Room *bookings,int id){
  Room *temp = searchId(bookings,id);
  if(temp == NULL){
    printf("\nBooking not found\n");
    return;
  }

  do{
    printf("\nEnter a choice to update\n");
    printf("1.Guest name\n");
    printf("2.Room number\n");
    printf("3.Check-in date\n");
    printf("4.Check-out date\n");
    printf("5.Room type\n");
    printf("6.Finish update\n");

    int c;
    scanf("%d",&c);
    switch(c){
      case 1: printf("\nEnter the name: ");
              scanf("%s",temp->name);
      break;

      case 2: printf("\nEnter room no: ");
              scanf("%d",&temp->room_no);
      break;

      case 3: printf("\nEnter check-in date: ");
              scanf("%s",temp->check_in);
      break;

      case 4: printf("\nEnter check-out date: ");
              scanf("%s",temp->check_out);
      break;

      case 5: printf("\nEnter room type: ");
              scanf("%s",temp->room_type);
      break;

      case 6: return;

      default: printf("\nEnter a correct option\n");
    }
  }while(1);
}

void displayAll(Room *bookings){
  Room *temp = bookings;
  if(temp == NULL){
    printf("\nNo Bookings\n");
    return;
  }
  int i=1;
  while(temp != NULL){
    printf("\nBooking %d",i);
    display(temp);
    temp = temp->next;
    i++;
  }
}

void main(){
  srand(time(0));
  Room *bookings = NULL;

  do{
    printf("\nEnter a choice\n");
    printf("1.Insert new Booking\n");
    printf("2.Delete existing booking\n");
    printf("3.Search booking\n");
    printf("4.Retrieve booking information\n");
    printf("5.Update booking status\n");
    printf("6.Display all bookings\n");
    printf("7.Exit\n");
    
    int c,id,room_no;
    char name[20],check_in[20],check_out[20],room_type[20];
    scanf("%d",&c);
    switch(c){
      case 1: printf("\nEnter guest name: ");
              scanf("%s",name);
              printf("Enter room no: ");
              scanf("%d",&room_no);
              printf("Enter check-in date: ");
              scanf("%s",check_in);
              printf("Enter check-out date: ");
              scanf("%s",check_out);
              printf("Enter the room_type: ");
              scanf("%s",room_type);
              bookings = insert(bookings,name,room_no,check_in,check_out,room_type);
      break;

      case 2: printf("\nEnter booking id to delete: ");
              scanf("%d",&id);
              bookings = delete(bookings,id);
      break;

      case 3: printf("\nEnter a choice\n");
              printf("1.Search by booking id\n");
              printf("2.Search by room no\n");

              int c1;
              Room *temp;
              scanf("%d",&c1);
              switch(c1){
                case 1: printf("\nEnter booking id to searchId: ");
                        scanf("%d",&id);
                        temp = searchId(bookings,id);
                break;

                case 2: printf("\nEnter room no to searchId: ");
                        scanf("%d",&room_no);
                        temp = searchRoom(bookings,room_no);
                break;
              }

              if(temp == NULL){
                printf("Booking not found\n");
              }else{
                printf("Booking found\n");
              }
      break;

      case 4: printf("\nEnter booking id to retrieve infromation: ");
              scanf("%d",&id);
              retrieveBooking(bookings,id);
      break;

      case 5: printf("\nEnter the booking id to update: ");
              scanf("%d",&id);
              update(bookings,id);
      break;

      case 6: displayAll(bookings);
      break;

      case 7: exit(0);

      default: printf("\nEnter a correct option\n");
    }
  }while(1);
}
