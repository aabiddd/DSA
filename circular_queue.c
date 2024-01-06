/*
Circular Queue, also implemented statically
*/
#include <stdio.h>
#include <windows.h>

#define MAX 5
#define TRUE 1
#define FALSE 0

typedef struct queue {
    int items[MAX];
    int front, rear;
} queue;

int isEmpty(queue q);
int isFull(queue q); 
void enqueue(queue *q, int x);
int dequeue(queue *q);
void traverse(queue q);
void peek(queue q);

int main() {
    queue q;
    int mode, item;

    q.front = 0;
    q.rear = 0;

    do {
        printf("1. Enqueue\n2. Dequeue\n3. Display First\n4. Display All\n5. Exit\n");
        printf("Enter mode: ");
        scanf("%d", &mode);

        switch (mode) {
            case 1: 
                if (isFull(q) == TRUE) {
                    printf("\033[1;31mQueue is FULL!\033[0m\n");
                }
                else {
                    printf("Enter item: ");
                    scanf("%d", &item);
                    enqueue(&q, item);
                }
                break;
        
            case 2:
                if (isEmpty(q) == TRUE) {
                    printf("\033[1;31mQueue is Empty!\033[0m\n");
                }
                else {
                    item = dequeue(&q);
                    printf("Dequeue Item: %d\n", item);
                }
                break;

            case 3:
                peek(q);
                break;

            case 4:
                traverse(q);
                break;
            
            case 5:
                printf("\033[1;32mExitting program...\033[0m\n");
                exit(0);

            default:
                printf("\033[1;31mInvalid Operation!\033[0m\n");
        }
    } while (TRUE);
}

int isEmpty(queue q) {
    return ((q.front == q.rear) ? TRUE : FALSE);
}

int isFull(queue q) {
    return ((q.front == (q.rear + 1) % MAX) ? TRUE : FALSE);
}

void enqueue(queue *q, int x) {
    q->items[q->rear] = x;
    q->rear = (q->rear + 1) % MAX;
}

int dequeue(queue *q) {
    int x;
    x = q->items[q->front];
    q->front = (q->front + 1) % MAX;
    return x;
}

void traverse(queue q) {
    int i;
    if (!isEmpty(q)) {
        printf("\n");
        for (i = q.front; i != q.rear; i=((i + 1) % MAX)) {
            printf("%d\t", q.items[i]);
        }
        printf("\n");
    }
    else {
        printf("\033[1;31mQueue is Currently Empty!\033[0m\n");
    }
}

void peek(queue q) {
    if (!isEmpty(q)) {
        printf("\nFirst Item: %d\n", q.items[q.front]);
    }
    else
        printf("\033[1;31mQueue is Currently Empty!\033[0m\n");
}
