/*
14.
Design a data structure to manage course enrollments and waitlists for an online course registration system.
Requirements:
  Create a data structure to represent courses, including:
    Course ID
    Course name
    Capacity
    Enrollment list (linked list of students)
    Waitlist (linked list of students)
  Implement functions for:
    Enrolling students in courses
    Removing students from courses
    Adding students to waitlists
    Removing students from waitlists
    Displaying course enrollment and waitlist information
  Handle errors for:
    Attempting to enroll in a full course
    Removing a student from a course they are not enrolled in
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 2

struct students{
  char name[20];
  struct students *next;
};

typedef struct students Students;

Students* getStudentNode(){
  Students *newNode = (Students*)malloc(sizeof(Students));
  return newNode;
}

struct course{
  int id;
  char name[20];
  int capacity;
  Students *enroll;
  Students *waiting;
  int enrollCount;
  int waitCount;
};

typedef struct course Course;

Course* getCourseNode(){
  Course *newNode = (Course*)malloc(sizeof(Course));
  return newNode;
} 

void addCourse(Course *courses[]){
  char *arr[] = {"Maths","Physics","Chemistry"};
  Course *current = NULL;

  for(int i=0;i<3;i++){
    Course *newNode = getCourseNode();
    newNode->id = i+1;
    strcpy(newNode->name,arr[i]);
    newNode->capacity = MAX;
    newNode->enrollCount = 0;
    newNode->waitCount = 0;
    newNode->enroll = newNode->waiting = NULL;

    courses[i] = newNode;
  }
}

Students* addwaiting(Course *course,char name[]){
  Students *newNode = getStudentNode();
  strcpy(newNode->name,name);
  newNode->next = NULL;

  Students *temp = course->waiting;
  if(temp == NULL){
    course->waiting = newNode;
  }else{
    while(temp->next != NULL){
      temp = temp->next;
    }
    temp->next = newNode;
  }
  
  (course->waitCount)++;
  printf("%s is added to waiting list\n",name);
  return course->waiting;
}

Course* enroll(Course *course,char name[]){
  if(course->enrollCount == MAX){
    printf("Cousre is full\n");
    course->waiting = addwaiting(course,name);
    return course;
  }

  Students *newNode = getStudentNode();
  strcpy(newNode->name,name);
  newNode->next = NULL;

  Students *temp = course->enroll;
  if(temp == NULL){
    course->enroll = newNode;
  }else{
    while(temp->next != NULL){
      temp = temp->next;
    }
    temp->next = newNode;
  }
  
  (course->enrollCount)++;
  printf("Enrolled succsessfully\n");
  return course;
}

Students* removeWaiting(Course *course){
  Students *temp = course->waiting;
  course->waiting = course->waiting->next;
  (course->waitCount)--;

  printf("%s is moved from waiting and ",temp->name);
  free(temp);
  return course->waiting;
}

Course* removeEnroll(Course *course,char name[]){
  Students *temp = course->enroll;
  if(strcmp(temp->name,name) == 0){
    course->enroll = course->enroll->next;
    free(temp);
    (course->enrollCount)--;
  }else{
    while(temp->next != NULL && strcmp(temp->next->name,name) != 0){
      temp = temp->next;
    }

    if(temp->next == NULL){
      printf("\nStudent not enrolled\n");
      return course;
    }else{
      Students *delete = temp->next;
      temp->next = temp->next->next;
      free(delete);
      (course->enrollCount)--;
    }
  }
  printf("Student removed\n");

  if(course->waitCount > 0){
    char name2[20];
    strcpy(name2,course->waiting->name);
    course->waiting = removeWaiting(course);
    course = enroll(course,name2);
  }
  return course;
}

void display(Course *course){
  if(course->enrollCount == 0){
    printf("\nNo students enrolled");
  }else{
    printf("\nEnrollment list: ");
    Students *temp = course->enroll;
    while(temp != NULL){
      printf("%s ",temp->name);
      temp = temp->next;
    }
  }

  if(course->waitCount == 0){
    printf("\nNo students in waiting list");
  }else{
    printf("\nWaiting list: ");
    Students *temp = course->waiting;
    while(temp != NULL){
      printf("%s ",temp->name);
      temp = temp->next;
    }
  }
  printf("\n");
}

void displayAll(Course *courses[]){
  for(int i=0;i<3;i++){
    printf("\nCourse id: %d\n",courses[i]->id);
    printf("Course name: %s\n",courses[i]->name);
    printf("Capacity: %d",courses[i]->capacity);
    display(courses[i]);
  }
}

void main(){
  Course *courses[3];
  addCourse(courses);
  int i,c;
  char name[20];

  do{
    printf("\nEnter a choice\n");
    printf("1.Maths\n");
    printf("2.Physics\n");
    printf("3.Chemistry\n");
    printf("4.Display courses\n");
    printf("5.Exit\n");

    scanf("%d",&i);
    if(i == 4){
      displayAll(courses);
      continue;
    }else if(i == 5){
      exit(0);
    }

    i--;
    do{
      printf("\nEnter a choice\n");
      printf("1.Enroll students\n");
      printf("2.Remove students\n");
      printf("3.Display enrollment and waiting list\n");
      printf("4.Back to courses\n");

      scanf("%d",&c);
      switch(c){
        case 1: printf("\nEnter the name of student: ");
                scanf("%s",name);
                courses[i] = enroll(courses[i],name);
        break;

        case 2: printf("\nEnter the name of student: ");
                scanf("%s",name);
                courses[i] = removeEnroll(courses[i],name);
        break;

        case 3: display(courses[i]);
        break;

        case 4: break;

        default: printf("\nEnter a correct option\n"); 
      }
    }while(c != 4);
  }while(1);
}