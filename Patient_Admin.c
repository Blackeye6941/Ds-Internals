/*
4.
Design a system to manage patient priorities in a hospital. Implement the following:

1. A max heap to manage patient priorities where higher priority patients are served
   first. 
2. Functions to insert a new patient with a given priority, remove the highest priority patient, and display the current state of the heap.
3. Demonstrate these operations with sample patient data.
*/

#include<stdio.h>
#include<stdlib.h>
#define MAX_SIZE 100
struct Patient{
    int id;
    int priority;
};

void swap(struct Patient *a, struct Patient *b){
    struct Patient temp = *a;
    *a = *b;
    *b = temp;
}

void Max_Heapify(struct Patient a[], int i, int n){
    int l = 2*i;
    int r = 2*i+1;
    int largest = i;
    if(l<=n && a[l].priority > a[largest].priority){
        largest = l;
    }
    if(r<=n && a[r].priority > a[largest].priority){
        largest = r;
    }
    if(largest != i){
        swap(&a[i], &a[largest]);
        Max_Heapify(a, largest, n);
    }
}

void Build_Max_Heap(struct Patient a[], int n){
    for(int i=n/2;i>0;i--){
        Max_Heapify(a, i, n);
    }
}

void Sort_Patients(struct Patient a[], int n){
    Build_Max_Heap(a, n);
    for(int i=n;i>1;i--){
        swap(&a[1], &a[i]);
        Max_Heapify(a, 1, i-1);
    }
}

void Display(struct Patient a[], int n) {
    if (n == 0) {
        printf("\nNo Patients to treat\n");
        return;
    }
    printf("\nCurrent Patients in the heap:\n");
    for (int i = 1; i <= n; i++) {
        printf("ID: %d, Priority: %d\n", a[i].id, a[i].priority);
    }
}

int Is_Unique(struct Patient a[], int n, int id, int p) {
    for (int i = 1; i <= n; i++) {
        if (a[i].id == id) {
            return 0;  // ID already exists
        }
        if(a[i].priority == p){
            return 0;
        }
    }
    return 1;  // ID is unique
}

int main(){
    int op, id, p,i=0; //p-Priority
    struct Patient Patients[MAX_SIZE];
     struct Patient max;
    while(1){
        printf("\n1.Add a patient\n2.Treat a patient\n3.Show Current state\n4.Exit\nEnter the process to be done: ");
        scanf("%d", &op);
        switch(op){
            case 1:
                printf("\nEnter the ID of patient: ");
                scanf("%d", &id);
                printf("\nEnter the priority of patient: ");
                scanf("%d", &p);
                if(!Is_Unique(Patients, i, id, p)){
                    printf("\nID or Priority already Exists!!\nEnter Valid ID/Priority !!");
                    break;
                }
                i++;
                Patients[i].id = id;
                Patients[i].priority = p;
                Sort_Patients(Patients, i);
                Display(Patients, i);
                break;
            case 2:
                if (i == 0) {
                    printf("\nNo patients to treat!!\n");
                } else {
                        max = Patients[1];  
                        printf("Patient to be treated: ID: %d (Priority: %d)\n", max.id, max.priority);       
                        swap(&Patients[1], &Patients[i]);
                        i--; 
                        Build_Max_Heap(Patients, i);
                        printf("Patient with ID %d (Priority: %d) has been treated and removed.\n", max.id, max.priority);
                }
                break;
            case 3:
                printf("------------------");
                Display(Patients, i);
                printf("------------------");
                break;
            case 4:
                printf("\nCode Exited!!\n");
                exit(0);
        }
    }
}