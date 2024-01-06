/*
Linear Queue implemented using Linked List
*/
#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

// node definition
typedef struct node {
    int info;
    struct node *next;
}node;

// node pointer
typedef node *NODEPTR;

// free a node
void freenode(NODEPTR p) {
    free(p);
}

// queue implementation using linked list
typedef struct queue
{
    NODEPTR front, rear;
}queue;

// global variable q
queue q;

int empty(queue *pq) {
    return ((pq->front == NULL) ? TRUE : FALSE);
}

void freeQueue(queue *pq) {
    NODEPTR tmp;
    NODEPTR p = pq->front;

    while (p != NULL) {
        tmp = p;
        p = p->next;
        freenode(tmp);
    }

    pq->front = NULL;
    pq->rear = NULL;

    printf("Queue nodes freed sucessfully!\n");
}

// allocate an empty node
NODEPTR getnode(void) {
    NODEPTR p;
    p = (NODEPTR) malloc(sizeof(node));

    if (p == NULL) {
        printf("\nMEMORY UNAVAILABLE\n");
        freeQueue(&q);
        exit(1);
    }
    return p;
}

void enqueue (queue *pq, int x) {
    NODEPTR p;
    p = getnode();
    p->info = x;
    p->next = NULL;

    if (pq->rear == NULL) {
        pq->front = p;
        pq->rear = p;
    }    
    else {
        (pq->rear)->next = p;
        pq->rear = p;
    }
}

int dequeue(queue *pq) {
    NODEPTR p;
    int x;
    p = pq->front;
    x = p->info;
    pq->front = p->next;
    if (pq->front == NULL)  
        pq->rear = NULL;
    freenode(p);
    return x;
}

void displayAll(queue *pq) {
    NODEPTR p;
    if (!empty(pq)) {
        for (p = pq->front; p!= NULL; p = p->next) {
            printf("%d\t", p->info);
        }
        printf("\n");
    }
    else 
        printf("Queue is currently empty\n");
}

void displayFirst(queue *pq) {
    NODEPTR first;
    if (!empty(pq)) {
        first = pq->front;
        printf("First Element: %d\n", first->info);
    }
    else 
        printf("Queue is currently empty!\n");
}

void main() {
    int mode, item;

    do {
        printf("Enter Mode: ");
        scanf("%d", &mode);

        switch(mode) {
            case 1:
                printf("Item: ");
                scanf("%d", &item);
                enqueue(&q, item);
                break;
            
            case 2:
                if (!empty(&q)) {
                    item = dequeue(&q);
                    printf("Dequeued element: %d\n", item);
                }
                else {
                    printf("Queue Underflow!\n");
                }
                break;

            case 3:
                displayFirst(&q);
                break;

            case 4:
                displayAll(&q);
                break;

            case 5:
                freeQueue(&q);
                printf("Exiting program...\n");
                exit(0);

            default:
                printf("Invalid Operation!\n");
        }
    } while (TRUE);
}