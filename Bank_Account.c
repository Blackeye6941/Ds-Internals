/*
20.
Design a banking system using a linked list to efficiently manage customer accounts and transactions.
Requirements:
Create a linked list node structure to represent customer accounts, including:
Account number,Customer name,Balance,Next node pointer,Transaction history (linked list of transactions )

Implement functions for:
Creating new accounts,Depositing and withdrawing funds,Displaying account information and transaction history[Not Implemented],
Transferring funds between accounts,
Searching for accounts by account number or customer name

Handle errors for:
Attempting to access a non-existent account,
Insufficient funds for transactions
*/

#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<string.h>

typedef struct Node {
    int AccNo, balance;
    char name[10];
    int pin[4];
    struct Node *next;
} Bank;

Bank *GetNode() {
    Bank *b = (Bank *)malloc(sizeof(Bank));
    return b;
}

int accountExists(Bank *account, int AccNo) {
    Bank *ptr = account;
    while (ptr != NULL) {
        if (ptr->AccNo == AccNo) {
            return 1;
        }
        ptr = ptr->next;
    }
    return 0;
}

Bank *CreateAccount(Bank *account, const char *name) {
    Bank *newNode = GetNode();
    int uniqueAccNo;
    do {
        uniqueAccNo = rand() % 90000 + 10000;
    } while (accountExists(account, uniqueAccNo));

    newNode->AccNo = uniqueAccNo;
    newNode->balance = 0;
    strncpy(newNode->name, name, sizeof(newNode->name) - 1);
    newNode->name[sizeof(newNode->name) - 1] = '\0';

    for (int i = 0; i < 4; i++) {
        newNode->pin[i] = rand() % 10;
    }
    newNode->next = NULL;
    printf("Account Created Successfully\nAccount Number is %d\n", newNode->AccNo);

    if (account == NULL) return newNode;
    else {
        Bank *temp = account;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
    return account;
}

Bank *deposit(Bank *account, int AccNo, int amount) {
    Bank *ptr = account;
    while (ptr != NULL) {
        if (ptr->AccNo == AccNo) {
            ptr->balance += amount;
            printf("Amount deposited successfully\n");
            return account;
        }
        ptr = ptr->next;
    }
    printf("Account doesn't exist\n");
    return account;
}

Bank *withdraw(Bank *account, int AccNo, int amount) {
    Bank *ptr = account;
    while (ptr != NULL) {
        if (ptr->AccNo == AccNo) {
            if (ptr->balance >= amount) {
                ptr->balance -= amount;
                printf("Amount withdrawn successfully\n");
            } else {
                printf("Insufficient balance\n");
            }
            return account;
        }
        ptr = ptr->next;
    }
    printf("Account doesn't exist\n");
    return account;
}

Bank *transfer(Bank *account, int ac1, int ac2, int amount) {
    Bank *fromAccount = NULL, *toAccount = NULL;
    Bank *ptr = account;
    while (ptr != NULL) {
        if (ptr->AccNo == ac1) fromAccount = ptr;
        if (ptr->AccNo == ac2) toAccount = ptr;
        ptr = ptr->next;
    }
    
    if (fromAccount == NULL || toAccount == NULL) {
        printf("One or both accounts do not exist\n");
        return account;
    }

    if (fromAccount->balance >= amount) {
        fromAccount->balance -= amount;
        toAccount->balance += amount;
        printf("Amount transferred successfully\n");
    } else {
        printf("Insufficient balance in source account\n");
    }
    return account;
}

int SearchAccount(Bank *account) {
    int option = 0, acc = 0;
    char name[10];
    Bank *ptr = account;

    printf("How to Search?\n1 - Account Number\t2 - Name: ");
    scanf("%d", &option);

    switch (option) {
        case 1:
            printf("Enter account number: ");
            scanf("%d", &acc);
            while (ptr != NULL) {
                if (ptr->AccNo == acc) return 1;
                ptr = ptr->next;
            }
            break;

        case 2:
            printf("Enter name of Account Holder: ");
            scanf("%s", name);
            while (ptr != NULL) {
                if (strcmp(ptr->name, name) == 0) return 1;
                ptr = ptr->next;
            }
            break;
    }
    return -1;
}

void display(Bank *account) {
    Bank *ptr = account;
    int j = 0;
    while (ptr != NULL) {
        printf("\nDetails of Person %d\n", j + 1);
        printf("Name: %s\n", ptr->name);
        printf("Account Number: %d\n", ptr->AccNo);
        printf("Pin: ");
        for (int i = 0; i < 4; i++) {
            printf("%d", ptr->pin[i]);
        }
        printf("\nBalance: %d\n", ptr->balance);
        ptr = ptr->next;
        j++;
    }
}

void displayOneAccount(Bank *account, int AccNo) {
    Bank *ptr = account;
    while (ptr != NULL) {
        if (ptr->AccNo == AccNo) {
            printf("\nAccount Details:\n");
            printf("Name: %s\n", ptr->name);
            printf("Account Number: %d\n", ptr->AccNo);
            printf("Pin: ");
            for (int i = 0; i < 4; i++) {
                printf("%d", ptr->pin[i]);
            }
            printf("\nBalance: %d\n", ptr->balance);
            return;
        }
        ptr = ptr->next;
    }
    printf("Account not found\n");
}

int main() {
    srand(time(NULL));
    Bank *head = NULL;
    char name[10];
    int choice = 0, amount = 0;
    int AC1 = 0, AC2 = 0, AccNo = 0;

    while (choice != 7) {
        printf("\nWelcome to ABC Bank\n");
        printf("Please Enter your Choice:\n");
        printf("1 - Create Account\n2 - Deposit\n3 - Withdraw\n4 - Transfer\n5 - Search Account\n6 - Display Accounts\n7 - Exit\n");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter name: ");
                scanf("%s", name);
                head = CreateAccount(head, name);
                break;

            case 2:
                printf("Enter the Account Number: ");
                scanf("%d", &AccNo);
                printf("Enter the amount to be deposited: ");
                scanf("%d", &amount);
                head = deposit(head, AccNo, amount);
                displayOneAccount(head, AccNo);
                break;

            case 3:
                printf("Enter the Account Number: ");
                scanf("%d", &AccNo);
                printf("Enter the amount to be withdrawn: ");
                scanf("%d", &amount);
                head = withdraw(head, AccNo, amount);
                displayOneAccount(head, AccNo);
                break;

            case 4:
                printf("Enter the 1st Account Number: ");
                scanf("%d", &AC1);
                printf("Enter the 2nd Account Number: ");
                scanf("%d", &AC2);
                printf("Enter the amount to be transferred: ");
                scanf("%d", &amount);
                head = transfer(head, AC1, AC2, amount);
                break;

            case 5:
                if (SearchAccount(head) == 1) {
                    printf("Account Exists\n");
                } else {
                    printf("Account doesn't Exist\n");
                }
                break;

            case 6:
                display(head);
                break;

            case 7:
                printf("Exiting...\n");
                break;

            default:
                printf("Invalid choice\n");
        }
    }
    return 0;
}
