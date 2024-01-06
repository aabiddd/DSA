/*
A simple menu driven program that utilizes the concept of stack on a static array
*/
#include <stdio.h>
#include <windows.h>
#define MAX 5 // Max size for the stack

void push(int [], int*);
void pop(int [], int, int*);
void displayAll(int [], int);
void displayTop(int [], int);

void main() {
    int stack[MAX];
    int item, top = -1;
    int mode;    

    do {
        printf("1. Push an item into the stack\n");
        printf("2. Pop an item from the stack\n");
        printf("3. Display all items present in the stack\n");
        printf("4. Display the top item of the stack\n");
        printf("5. Exit the program\n\n");

        printf("Enter mode: ");
        scanf("%d", &mode);

        switch (mode) {
            // Push items into the stack
            case 1:
                push(stack, &top);
                break;

            // Pop items from the stack
            case 2:
                pop(stack, top, &item);
                if (top != -1) {
                    printf("Popped Item: %d\n", item);
                    top--;
                }
                break;

            // Display all items 
            case 3:
                displayAll(stack, top);
                break;
            
            // Display the top element
            case 4:
                displayTop(stack, top);
                break;

            case 5:
                exit(0);

            default:
                printf("Enter valid paramter!\n");  
        }

        printf("\n");
    } while (1);
}

void push(int stack[MAX], int *top) {
    int item;

    if (*top == MAX - 1) {
        printf("Stack full Xa!\n");
    }
    else { 
        printf("Enter an item to be pushed: ");
        scanf("%d", &item);

        *top += 1;
        stack[*top] = item;
    }
}

void pop(int stack[MAX], int top, int *item) {
    if (top == -1) {
        printf("Stack khali xa!\n");
        return;
    }

    *item = stack[top];
    return;
}

void displayAll(int stack[MAX], int top) {
    int i;
    if (top == -1) {
        printf("Stack Khali Xa!\n");
    }
    else {
        for (i = top; i >= 0; i--) {
            printf("%d\t", stack[i]);
        }
        printf("\n");
    }
}

void displayTop(int stack[MAX], int top) {
    if (top == -1) {
        printf("Stack Khali Xa!\n");
    }
    else {
        printf("TopMost Item: %d", stack[top]);
    }
}