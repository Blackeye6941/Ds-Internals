/* MUSIC PLAYLIST MANAGEMENT SYSTSEM USING LINKED LISTS*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct Song {
    int pos;
    char title[100];
    char artist[100];
    char genre[100];
    float duration;
    struct Song* next;
};

bool songExists(struct Song* head, char title[100]) {
    struct Song* temp = head;
    while (temp != NULL && strcmp(temp->title, title) != 0) {
        temp = temp->next;
    }
    return temp != NULL;
}

void insert_beginning(struct Song** head) {
    struct Song* newSong = (struct Song*)malloc(sizeof(struct Song));
    
    printf("Enter Song title: ");
    scanf("%s", newSong->title);

    printf("Enter Artist name: ");
    scanf("%s", newSong->artist);

    printf("Enter genre: ");
    scanf("%s", newSong->genre);

    printf("Enter duration: ");
    scanf("%f", &newSong->duration);

    if(!songExists(*head,newSong->title)){
        newSong->next = *head;
        *head = newSong;
    } else{
        printf("Song already exists");
    }
}

void insert_end(struct Song** head) {
    struct Song* newSong = (struct Song*)malloc(sizeof(struct Song));
    printf("Enter Song title: ");
    scanf("%s", newSong->title);

    printf("Enter Artist name: ");
    scanf("%s", newSong->artist);

    printf("Enter genre: ");
    scanf("%s", newSong->genre);

    printf("Enter duration: ");
    scanf("%f", &newSong->duration);

    newSong->next = NULL;

    if(!songExists(*head,newSong->title)){
        if (*head == NULL) {
            *head = newSong;
        } else {
            struct Song* temp = *head;
            while (temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = newSong;
        }
    }  else{
        printf("Song already exists");
    }
    
}

void insert_random(struct Song** head, int key) {
    struct Song* newSong = (struct Song*)malloc(sizeof(struct Song));
    printf("Enter Song title: ");
    scanf("%s", newSong->title);

    printf("Enter Artist name: ");
    scanf("%s", newSong->artist);

    printf("Enter genre: ");
    scanf("%s", newSong->genre);

    printf("Enter duration: ");
    scanf("%f", &newSong->duration);

    if(!songExists(*head,newSong->title)){
        struct Song* temp = *head;
        while (temp->next != NULL && temp->pos != key) {
            temp = temp->next;
        }

        newSong->next = temp->next;
        temp->next = newSong;
    } else{
        printf("Song already exitst");
    }
}

void delete_by_title(struct Song** head, char title[]) {
    struct Song* temp = *head;
    struct Song* prev = NULL;

    if (temp != NULL && strcmp(temp->title, title) == 0) {
        *head = temp->next;
        free(temp);
        printf("Deleted song\n");
        return;
    }

    while (temp != NULL && strcmp(temp->title, title) != 0) {
        prev = temp;
        temp = temp->next;
    }

    if(temp==NULL){
        printf("Song does not exists");
        return;
    }

    prev->next = temp->next;
    free(temp);
    printf("Deleted song\n");
}

void playSong(struct Song* head, char title[100]) {
    struct Song* temp = head;
    while (temp != NULL && strcmp(title, temp->title) != 0) {
        temp = temp->next;
    }

    if (temp != NULL) {
        printf("Title: %s\n", temp->title);
        printf("Artist: %s\n", temp->artist);
        printf("Genre: %s\n", temp->genre);
        printf("Duration: %.2f\n", temp->duration);
    } else {
        printf("Song not found\n");
    }
}

void display(struct Song* head) {
    struct Song* temp = head;
    while (temp != NULL) {
        printf("Title: %s, Artist: %s, Genre: %s, Duration: %.2f\n", temp->title, temp->artist, temp->genre, temp->duration);
        temp = temp->next;
    }
}

struct Song* search(struct Song* head, char title[100]) {
    struct Song* temp = head;
    while (temp != NULL && strcmp(temp->title, title) != 0) {
        temp = temp->next;
    }
    return temp;
}

int main() {
    struct Song* head = NULL;
    int choice;
    char title[100];
    int position;

    while (1) {
        printf("\nMenu:\n");
        printf("1. Insert song at the beginning\n");
        printf("2. Insert song at the end\n");
        printf("3. Insert song at a specific position\n");
        printf("4. Delete song by title\n");
        printf("5. Play song\n");
        printf("6. Display all songs\n");
        printf("7. Search for a song\n");
        printf("8. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                insert_beginning(&head);
                break;
            case 2:
                insert_end(&head);
                break;
            case 3:
                printf("Enter position to insert: ");
                scanf("%d", &position);
                insert_random(&head, position);
                break;
            case 4:
                printf("Enter title of the song to delete: ");
                scanf("%s", title);
                delete_by_title(&head, title);
                break;
            case 5:
                printf("Enter title of the song to play: ");
                scanf("%s", title);
                playSong(head, title);
                break;
            case 6:
                display(head);
                break;
            case 7:
                printf("Enter title of the song to search: ");
                scanf("%s", title);
                struct Song* found = search(head, title);
                if (found != NULL) {
                    printf("Song found: %s by %s\n", found->title, found->artist);
                } else {
                    printf("Song not found\n");
                }
                break;
            case 8:
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
