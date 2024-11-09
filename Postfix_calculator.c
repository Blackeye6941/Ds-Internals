/*
Implement a simple calculator that converts infix expressions to postfix notation for
evaluation.
*/

#include<stdio.h>
#include<string.h>
#include<math.h>
#define MAX_SIZE 100

struct lifo{
  int st[MAX_SIZE];
  int top;
};

typedef struct lifo stack;
char s1[MAX_SIZE];
int i=0;

void createStack(stack *s){
  s->top = -1;
}

int isFull(stack *s){
  if(s->top == MAX_SIZE-1){
    return 1;
  }
  return 0;
}

int isEmpty(stack *s){
  if(s->top == -1){
    return 1;
  }
  return 0;
}

void push(stack *s,int element){
  if(isFull(s)){
    printf("Stack is full");
    return;
  }

  s->st[++s->top] = element;
}

int pop(stack *s){
  return s->st[s->top--];
}

int operator(char element){
  int result;

  if(element == '('){
    result = 0;
  }else if(element == '+' || element == '-'){
    result = 1;
  }else if(element == '*' || element == '/'){
    result = 2;
  }else if(element == '^'){
    result = 3;
  }

  return result;
}

int isOperator(char c){
  if(c == '+' || c == '-' || c == '/' || c == '*' || c== '^' || c == '(' || c== ')'){
    return 1;
  }
  return 0;
}

void conversion(stack *s,char element){
  if(isOperator(element)){

    if(isEmpty(s) || element == '('){
      push(s,element);
    }else if(element == ')'){
      while(s->st[s->top] != '('){
        s1[i++] = pop(s);
      }
      pop(s);
    }else{
      while(operator(s->st[s->top]) >= operator(element)){
        if(isEmpty(s)){
          break;
        }
        s1[i++] = pop(s);
      }
      push(s,element);
    }
  }else{
    s1[i++] = element;
  }
}

void accept_values(int values[]){
  int j=0;
  char c;
  while((c=s1[j])!='\0'){
    if(!isOperator(c) && !values[c-65]){
      printf("Enter value of %c: ",c);
      scanf("%d",&values[c-65]);
    }
    j++;
  }
}

void evaluate(stack *s,char c,int values[]){
  if(isOperator(c)){

    int op1 = pop(s);
    int op2 = pop(s);
    int result;

    switch(c){
      case '+': result = op1 + op2;
      break;

      case '-': result = op2 - op1;
      break;

      case '*': result = op1 * op2;
      break;

      case '/': result = op2/op1; 
      break;

      case '^': result = (int)pow(op2,op1);
    }
    push(s,result);
  }else{
    push(s,values[c-65]);
  }
} 

void main(){
  stack s;
  int values[58] = {0};
  createStack(&s);

  char s2[MAX_SIZE];
  printf("Enter the infix expression: ");
  scanf("%s",s2);

  int j=0,n;
  char c;
  while((c=s2[j++])!='\0'){
    conversion(&s,c);
  }

  while(!isEmpty(&s)){
    s1[i++] = pop(&s);
  }
  s1[i] = '\0';
  printf("Postfix: %s\n\n",s1);

  accept_values(values);
  
  createStack(&s);
  j=0;
  while((c=s1[j++])!='\0'){
    evaluate(&s,c,values);
  }

  int result = pop(&s);
  printf("\nResult = %d",result);
}