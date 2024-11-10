#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Booking {
    int id;
    char name[30];
    int room_no;
    char in_date[12];
    char out_date[12];
    int room_type;
    struct Booking* next;
};

struct Booking* CreateBooking() {
    struct Booking* temp = (struct Booking*)malloc(sizeof(struct Booking));
    return temp;
}

struct Booking* Insert_Booking(struct Booking* head) {
    int id;
    char name[30];
    int room_no;
    char in_date[12];
    char out_date[12];
    int room_type;

    printf("\nEnter Unique Booking ID: ");
    scanf("%d", &id);
    printf("\nEnter Guest Name: ");
    scanf("%s", name);
    printf("\nEnter room number: ");
    scanf("%d", &room_no);
    
    // Check if the room is already booked
    struct Booking* temp2 = head;
    while(temp2 != NULL) {
        if(temp2->room_no == room_no) {
            printf("\nRoom already Booked!!\n");
            return head;
        }
        temp2 = temp2->next;
    }
    
    printf("\nEnter Check-In date (DD/MM/YY): ");
    scanf("%s", in_date);
    printf("\nEnter Check-Out date (DD/MM/YY): ");
    scanf("%s", out_date);
    printf("\nEnter Room type (1. Single, 2. Double, 3. Suite): ");
    scanf("%d", &room_type);

    struct Booking* new = CreateBooking();
    new->id = id;
    new->room_no = room_no;
    new->room_type = room_type;
    strcpy(new->name, name);
    strcpy(new->in_date, in_date);
    strcpy(new->out_date, out_date);
    new->next = NULL;

    // Insert at the end of the list
    if(head == NULL) {
        head = new;
    } else {
        struct Booking* temp = head;
        while(temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = new;
    }
    return head;
}

void Display(struct Booking* head) {
    struct Booking* temp = head;
    printf("\n--------------------------------------------------");
    if(temp == NULL) {
        printf("\nNo Bookings");
    } else {
        while(temp != NULL) {
            printf("\nBooking ID: %d", temp->id);
            printf("\nGuest Name: %s", temp->name);
            printf("\nRoom number: %d", temp->room_no);
            printf("\nCheck In date: %s", temp->in_date);
            printf("\nCheck Out date: %s", temp->out_date);
            if(temp->room_type == 1) {
                printf("\nRoom Type: Single");
            } else if(temp->room_type == 2) {
                printf("\nRoom Type: Double");
            } else {
                printf("\nRoom Type: Suite");
            }
            printf("\n--------------------------------------------------");
            temp = temp->next;
        }
    }
}

struct Booking* Delete_Booking(struct Booking* head) {
    int id;
    struct Booking* temp = head;
    struct Booking* prev = NULL;

    if(head == NULL) {
        printf("\nNo bookings to delete!");
        return head;
    }

    printf("\nEnter Booking Id to delete: ");
    scanf("%d", &id);

    // Special case for head node
    if(temp != NULL && temp->id == id) {
        head = temp->next;  // Update head
        free(temp);
        printf("\nBooking %d Deleted\n", id);
        return head;
    }

    // Search for the booking to delete
    while(temp != NULL && temp->id != id) {
        prev = temp;
        temp = temp->next;
    }

    if(temp == NULL) {
        printf("\nBooking ID not found\n");
        return head;
    }

    // Unlink the node from the linked list
    prev->next = temp->next;
    free(temp);
    printf("\nBooking %d Deleted\n", id);

    return head;
}

void Search_Booking(struct Booking* head) {
    int op, id, room_no;
    struct Booking* temp = head;
    printf("\n1. Search By ID\n2. Search by Room Number: ");
    scanf("%d", &op);

    if(op == 1) {
        printf("\nEnter ID: ");
        scanf("%d", &id);
        while(temp != NULL && temp->id != id) {
            temp = temp->next;
        }
        if(temp == NULL) {
            printf("\nBooking not found!\n");
        } else {
            printf("\nBooking found!\nRoom no: %d\tGuest name: %s\n", temp->room_no, temp->name);
        }
    }
    else if(op == 2) {
        printf("\nEnter Room Number: ");
        scanf("%d", &room_no);
        while(temp != NULL && temp->room_no != room_no) {
            temp = temp->next;
        }
        if(temp == NULL) {
            printf("\nBooking not found!\n");
        } else {
            printf("\nBooking found!\nRoom no: %d\tGuest name: %s\n", temp->room_no, temp->name);
        }
    }
    else {
        printf("\nInvalid choice!\n");
    }
}

void Retrieve_Booking(struct Booking* head) {
    int op, id, room_no;
    struct Booking* temp = head;
    printf("\n1. Search By ID\n2. Search by Room Number: ");
    scanf("%d", &op);

    if(op == 1) {
        printf("\nEnter ID: ");
        scanf("%d", &id);
        while(temp != NULL && temp->id != id) {
            temp = temp->next;
        }
        if(temp == NULL) {
            printf("\nBooking not found!\n");
        } else {
            printf("\nBooking ID: %d", temp->id);
            printf("\nGuest Name: %s", temp->name);
            printf("\nRoom number: %d", temp->room_no);
            printf("\nCheck In date: %s", temp->in_date);
            printf("\nCheck Out date: %s", temp->out_date);
            if(temp->room_type == 1) {
                printf("\nRoom Type: Single");
            } else if(temp->room_type == 2) {
                printf("\nRoom Type: Double");
            } else {
                printf("\nRoom Type: Suite");
            }
        }
    }
    else if(op == 2) {
        printf("\nEnter Room Number: ");
        scanf("%d", &room_no);
        while(temp != NULL && temp->room_no != room_no) {
            temp = temp->next;
        }
        if(temp == NULL) {
            printf("\nBooking not found!\n");
        } else {
            printf("\nBooking ID: %d", temp->id);
            printf("\nGuest Name: %s", temp->name);
            printf("\nRoom number: %d", temp->room_no);
            printf("\nCheck In date: %s", temp->in_date);
            printf("\nCheck Out date: %s", temp->out_date);
            if(temp->room_type == 1) {
                printf("\nRoom Type: Single");
            } else if(temp->room_type == 2) {
                printf("\nRoom Type: Double");
            } else {
                printf("\nRoom Type: Suite");
            }
        }
    }
    else {
        printf("\nInvalid choice!\n");
    }
}

struct Booking* Update_Booking(struct Booking* head) {
    struct Booking* temp = head;
    int id, p;
    char name[30];
    int room_no;
    char in_date[12];
    char out_date[12];
    int room_type;

    printf("\nEnter booking ID: ");
    scanf("%d", &id);

    // Search for the booking by ID
    while(temp != NULL && temp->id != id) {
        temp = temp->next;
    }

    if(temp == NULL) {
        printf("\nBooking not found!\n");
    } else {
        printf("\nBooking found!\nRoom no: %d\tGuest name: %s\n", temp->room_no, temp->name);
        printf("\n1. Update Name\n2. Update Check-In date\n3. Update Room Number\n4. Update Room Type\n5. Update Check-Out date\nEnter operation: ");
        scanf("%d", &p);

        switch(p) {
            case 1:
                printf("\nEnter new name: ");
                scanf("%s", name);
                strcpy(temp->name, name);  // Corrected: strcpy instead of strncpy
                break;
            case 2:
                printf("\nEnter new check-in date: ");
                scanf("%s", in_date);
                strcpy(temp->in_date, in_date);
                break;
            case 3:
                printf("\nEnter new room number: ");
                scanf("%d", &room_no);  // Corrected: use &room_no
                temp->room_no = room_no;
                break;
            case 4:
                printf("\nEnter new room type: ");
                scanf("%d", &room_type);  // Corrected: use &room_type
                temp->room_type = room_type;
                break;
            case 5:
                printf("\nEnter new check-out date: ");
                scanf("%s", out_date);
                strcpy(temp->out_date, out_date);
                break;
            default:
                printf("\nInvalid Input. Process Exited\n");
        }
    }
    return head;
}

int main() {
    int op;
    struct Booking* head = NULL;

    while(1) {
        printf("\n1. Insert New Booking\n2. Delete Existing Booking\n3. Search Bookings by Id or Room Number\n4. Retrieve Booking Info\n5. Update Booking Status\n6. Display All Bookings\n7. Exit\nEnter process to be done: ");
        scanf("%d", &op);

        switch(op) {
            case 1:
                head = Insert_Booking(head);
                break;
            case 2:
                head = Delete_Booking(head);
                break;
            case 3:
                Search_Booking(head);
                break;
            case 4:
                Retrieve_Booking(head);
                break;
            case 5:
                head = Update_Booking(head);
                break;
            case 6:
                Display(head);
                break;
            case 7:
                exit(0);
            default:
                printf("\nEnter Valid Process!!\n");
        }
    }

    return 0;
}
