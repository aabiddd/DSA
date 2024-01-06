/*
Linear Queue implemented statically
*/
#include <stdio.h>
#define TRUE 1
#define FALSE 0
#define MAX 5

// struct implementation
typedef struct queue
{
    int items[MAX];
    int front, rear;
} queue;

// function prototypes
int empty(queue);
int full(queue);
void enqueue(queue*, int*);
void dequeue(queue*, int*);
void displayFront(queue);
void displayAll(queue);

int main() {
    int mode, item;
    queue q;
    // for linear queue:
    q.front = 0;
    q.rear = -1;

    do {
        printf("\nMODE: ");
        scanf("%d", &mode);

        switch(mode) {
            case 1:
                printf("Enter the item to insert: ");
                scanf("%d", &item);
                enqueue(&q, &item);
                break;

            case 2:
                if (!empty(q)) {
                    dequeue(&q, &item);
                    printf("Removed Item: %d\n", item);
                }
                else {
                    dequeue(&q, &item);
                }
                break;

            case 3:
                displayFront(q);
                break;

            case 4:
                displayAll(q);
                break;

            case 5:
                printf("Exitting program...\n");
                return 0; // exit normally

            default:
                printf("\nInvalid Statement!\n");
        }
    } while (TRUE);

    return 1;
}

int empty(queue q) {
    return ((q.front > q.rear) ? TRUE : FALSE);
}

int full(queue q) {
    return ((q.rear == MAX - 1) ? TRUE : FALSE);
}

void enqueue(queue *q, int *x) {
    if (full(*q)) {
        printf("\nOverflow! Item %d not enqueued!\n", *x);
    }
    else {
        q->rear += 1;
        q->items[q->rear] = *x;
    }
}

void dequeue(queue *q, int *x) {
    if (empty(*q)) {
        printf("\nUnderflow! Queue is EMPTY.\n");
    }
    else {
        *x = q->items[q->front];
        q->front += 1;
    }
}

void displayFront(queue q) {
    if (!empty(q))
        printf("\nFirst Element: %d\n", q.items[q.front]);
    else
        printf("\nNo elements currently present.\n");
}

void displayAll(queue q) {
    int i;
    if (!empty(q)) {
        printf("\nAll Elements:\t");
        for (int i = q.front; i <= q.rear; i++) {
            printf("%d\t", q.items[i]);
        }
        printf("\n");
    }
    else
        printf("\nNo elements currently present.\n");
}