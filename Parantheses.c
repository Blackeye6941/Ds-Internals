/*V. Implement a program using a stack to check whether a string containing parentheses ( and) is balanced. Demonstrate your solution with various test cases.
*/
#include <stdio.h>
#include <string.h>
#define MAX_SIZE 100

struct Stack {
    char a[MAX_SIZE];
    int top;
};

void CreateS(struct Stack* S) {
    S->top = -1;
}

void Push(struct Stack* S, char c) {
    if (S->top == MAX_SIZE - 1) {
        printf("\nStack is Full");
    } else {
        S->a[++S->top] = c;
    }
}

void Pop(struct Stack* S) {
    if (S->top == -1) {
        printf("\nThe stack is Empty");
    } else {
        S->top--;
    }
}

char Top(struct Stack* S) {
    if (S->top == -1) {
        return '\0'; 
    }
    return S->a[S->top];
}

int isEmpty(struct Stack* S) {
    return S->top == -1;
}

int Check(char* Exp, int n) {
    struct Stack S;
    CreateS(&S);

    for (int i = 0; i < n; i++) {
        if (Exp[i] == '{' || Exp[i] == '[' || Exp[i] == '(') {
            Push(&S, Exp[i]);
        } else if ((Exp[i] == '}' && Top(&S) == '{') || 
                   (Exp[i] == ']' && Top(&S) == '[') || 
                   (Exp[i] == ')' && Top(&S) == '(')) {
            Pop(&S);
        } else if (Exp[i] == '}' || Exp[i] == ']' || Exp[i] == ')') {
            return 0;  // Mismatched closing bracket
        }
    }

    return isEmpty(&S); 
}

int main() {
    char Exp[100];
    printf("Enter the expression: ");
    fgets(Exp, sizeof(Exp), stdin); // Allows input with spaces and multiple lines
    //scanf wont take multiple words. It only scans the first word.

    int result = Check(Exp, strlen(Exp));
    if (result) {
        printf("\nThe expression is balanced\n");
    } else {
        printf("\nThe expression is not balanced\n");
    }

    return 0;
}
