/* 
12.
 SOCIAL NETWORK REPRESENTATION USING SPARSE MATRIX */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 100
#define NETWORK_SIZE 10

struct userInfo {
    char name[100];
    char id[100];
    int friends[MAX_SIZE];
    int r, c;
    int numberOfFriends;
};

int create_network(int net[MAX_SIZE][MAX_SIZE]) {
    int nusers;
    printf("Enter number of users: ");
    scanf("%d", &nusers);

    for (int i = 0; i < nusers; i++) {
        for (int j = 0; j < nusers; j++) {
            net[i][j] = 0;
        }
    }
    printf("Social network created with %d users\n", nusers);
    return nusers;
}

struct userInfo* create_user(int net[MAX_SIZE][MAX_SIZE], int n) {
    struct userInfo* user = (struct userInfo*)malloc(sizeof(struct userInfo)); // Allocate memory for user

    printf("Enter name of the user: ");
    scanf("%s", user->name);

    printf("Enter id of the user: ");
    scanf("%s", user->id);

    // Initialize user position
    int flag = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j && net[i][j] != 2 && flag == 0) {
                user->r = i;
                user->c = j;
                net[i][j] = 2;
                flag = 1;
                break;
            }
        }
    }
    printf("Created user \n");
    return user;
}

void addFriend(int net[MAX_SIZE][MAX_SIZE], struct userInfo* users[], int user_count, struct userInfo* user) {
    char id[100];
    printf("Enter id: ");
    scanf("%s", id);

    int col = -1;
    for (int i = 0; i < user_count; i++) {
        if (strcmp(users[i]->id, id) == 0) {
            printf("%d",users[i]->c);
            col = users[i]->c;
            break;
        }
    }

    if (col != -1) {
        net[user->r][col] = 1;
        printf("Added friend: %s\n", id);
    } else {
        printf("User not found: %s\n", id);
    }
}

void display(int net[MAX_SIZE][MAX_SIZE], int user_count) {
    for (int i = 0; i < user_count; i++) {
        for (int j = 0; j < user_count; j++) {
            printf("%d\t", net[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void sparse_matrix(int net[MAX_SIZE][MAX_SIZE], int n, int spt_net[MAX_SIZE][3]) {
    int count = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (net[i][j] != 0 && net[i][j] != 2) {
                count++;
            }
        }
    }

    spt_net[0][0] = n;
    spt_net[0][1] = n;
    spt_net[0][2] = count;

    int tc = 1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (net[i][j] != 0 && net[i][j] != 2) {
                spt_net[tc][0] = i;
                spt_net[tc][1] = j;
                spt_net[tc][2] = net[i][j];
                tc++;
            }
        }
    }
}

int main() {
    int net[MAX_SIZE][MAX_SIZE];
    int spt_net[MAX_SIZE][3];
    int user_count = create_network(net);

    struct userInfo* users[10];
    int choice;
    char userId[100];

    int tc = 0;
    while (1) {
        printf("\nMenu:\n");
        printf("1. Create user\n");
        printf("2. Add friend\n");
        printf("3. Display network\n");
        printf("4. Convert to sparse matrix\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                if (user_count < 10) {
                    users[tc++] = create_user(net, NETWORK_SIZE);
                } else {
                    printf("Maximum number of users reached.\n");
                }
                break;
            case 2:
                printf("UserId: ");
                scanf("%s", userId);
                int flag = 0;
                for(int i=0;i<user_count;i++){
                    if(strcmp(users[i]->id, userId) == 0){
                        flag = 1;
                        addFriend(net,users,user_count,users[i]);
                        break;
                    }
                }
                if(flag!=1){
                    printf("user not found on the index: %s",userId);
                }
            case 3:
                display(net, user_count);
                break;
            case 4:
                sparse_matrix(net, user_count, spt_net);
                printf("Sparse matrix representation:\n");
                for (int i = 0; i <= spt_net[0][2]; i++) {
                    printf("%d %d %d\n", spt_net[i][0], spt_net[i][1], spt_net[i][2]);
                }
                break;
            case 5:
                printf("Exiting...\n");
                for (int i = 0; i < user_count; i++) {
                    if (users[i] != NULL) {
                        free(users[i]);
                    }
                }
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
