/*
17.
Design a parking management system that utilizes a stack data structure to efficiently manage vehicle entries and exits. The system should ensure that the last vehicle that enters the parking lot is the first to exit.
Requirements:
  Implement a stack to store vehicle information (e.g., license plate number, entry time).
Develop functions for:
  Vehicle entry: Push vehicle information onto the stack.
  Vehicle exit: Pop the top element from the stack and display the exiting vehicle's information.
  Display parking status: Show the number of vehicles currently parked.
  Search vehicle: Check if a specific vehicle is parked.
Handle errors for:
  Attempting to exit a vehicle when the parking lot is empty.
  Searching for a vehicle not in the parking lot.
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct Node{
  char vehicleNo[20];
  char time[20];
  struct Node *next;
};

typedef struct Node Parking;

Parking* createParking(){
  Parking *newParking = (Parking*)malloc(sizeof(Parking));
  return newParking;
}

int isEmpty(Parking *Vehicle){
  if(Vehicle == NULL){
    return 1;
  }
  return 0;
}

Parking* pushVehicle(Parking *Vehicle,char vehicleNo[],char time[]){
  Parking *newParking = createParking();

  if(newParking == NULL){
    printf("\nInsufficient memory\n");
  }else{
    strcpy(newParking->vehicleNo,vehicleNo);
    strcpy(newParking->time,time);

    newParking->next = Vehicle;
    Vehicle = newParking;
  }
}

Parking* popVehicle(Parking *Vehicle,char vehicleNo[],char time[]){
  Parking *lastVehicle = Vehicle;
  Vehicle = (Vehicle)->next;
  strcpy(vehicleNo,lastVehicle->vehicleNo);
  strcpy(time,lastVehicle->time);
  free(lastVehicle);
  return Vehicle;
}

void search(Parking *Vehicle,char vehicleNo[]){
  Parking *temp = Vehicle;
  while(temp != NULL && strcmp(temp->vehicleNo,vehicleNo) != 0){
    temp = temp->next;
  }

  if(temp == NULL){
    printf("\nVehicle is not present\n");
  }else{
    printf("\nVehicle found\n");
    printf("Entry time: %s\n",temp->time);
  }
}

int display(Parking *Vehicle){
  Parking *temp = Vehicle;
  int count = 0;
  while(temp != NULL){
    temp = temp->next;
    count++;
  }
  return count;
}

void main(){
  Parking *Vehicle = NULL;

  do{
    printf("\nEnter a choice\n");
    printf("1.Add a Vehicle\n");
    printf("2.Pop a Vehicle\n");
    printf("3.Search a Vehicle\n");
    printf("4.Display no: of Vehicles\n");
    printf("5.Exit\n");

    int c,count;
    char vehicleNo[20],time[20];
    scanf("%d",&c);

    switch(c){
      case 1: printf("\nEnter the vehicle no: ");
              scanf("%s",vehicleNo);
              printf("Enter the entry time: ");
              scanf("%s",time);
              Vehicle = pushVehicle(Vehicle,vehicleNo,time);
              printf("Vehicle added successfully\n");
      break;

      case 2: if(!isEmpty(Vehicle)){
                Vehicle = popVehicle(Vehicle,vehicleNo,time);
                printf("\nVehicle No: %s\n",vehicleNo);
                printf("Entry time: %s\n",time);
              }else{
                printf("\nParking lot is empty\n");
              }
      break;

      case 3: printf("\nEnter the vehicle no: to search: ");
              scanf("%s",vehicleNo);
              search(Vehicle,vehicleNo);
      break;

      case 4: count = display(Vehicle);
              printf("\nNo: of vehicles in parking lot: %d\n",count);
      break;

      case 5: exit(0);

      default: printf("\nEnter a correct option\n");
    }
  }while(1);
}
