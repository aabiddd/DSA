/* 
Implementation of Singly Linear Linked List
qn. Write a menu driven program to implement singly linear linked list that perfrom following operations:
1. Insert at first
2. Insert at last
3. Insert at any specific position
4. Delete first node
5. Delete last node
6. Delete a node at any specific position
7. Traverse and display
8. Search an element
*/
#include <stdio.h>
#include <windows.h>

#define TRUE 1
#define FALSE 0

typedef struct node {
    int info;
    struct node *next;
} node;

// initialization of an empty node
node *start = NULL;

void freeList(node **);
node* getNode(void);
int isEmpty(node*);
int numOfNodes(node*);
void firstInsert(node**, int);
void lastInsert(node**, int);
void nInsert(node**, int);
void firstDelete(node**);
void lastDelete(node**);
void nDelete(node**);
void traverse(node*);
void search(node*, int);

void main() {
    int mode, item;

    do {
        printf("\033[1;36m1. Insert an item at first position\n");
        printf("2. Insert an item at last position\n");
        printf("3. Insert an item at a specific position\n");
        printf("4. Delete an item at first position\n");
        printf("5. Delete an item at last position\n");
        printf("6. Delete an item at a specific position\n");
        printf("7. Traverse through the list and Display\n");
        printf("8. Search for an item\n");
        printf("9. Number of items in the list\n");
        printf("10. Exit program\033[1;0m\n");

        printf("\nEnter mode:");
        scanf("%d", &mode);

        // menu driven program
        switch(mode) {
            case 1:
                printf("Enter the item to insert: ");
                scanf("%d", &item);
                firstInsert(&start, item);
                break;

            case 2:
                printf("Enter the item to insert: ");
                scanf("%d", &item);
                lastInsert(&start, item);
                break;

            case 3:
                if (isEmpty(start) == TRUE)
                    printf("Insert some items first!\n");
                    // if below fxn gets called when no node is present, it can get stuck in an indefinite loop. so....
                else {
                    printf("Enter the item to insert: ");
                    scanf("%d", &item);
                    nInsert(&start, item);
                }
                break;

            case 4:
                if (isEmpty(start) == TRUE)
                    printf("List is empty!\n");
                else {
                    firstDelete(&start);
                }
                break;

            case 5:
                if (isEmpty(start) == TRUE)
                    printf("List is empty!\n");
                else {
                    lastDelete(&start);
                }
                break;

            case 6:
                if (isEmpty(start) == TRUE)
                    printf("List is empty!\n");
                else {
                    nDelete(&start);
                }
                break;

            case 7:
                if (isEmpty(start) == TRUE)
                    printf("List is empty!\n");
                else   
                    traverse(start);
                break;

            case 8:
                if (isEmpty(start) == TRUE)
                    printf("List is empty!\n");
                else {
                    printf("Enter the item to be searched: ");
                    scanf("%d", &item);
                    search(start, item);
                }
                break;

            case 9:
                printf("No. of items: %d\n", numOfNodes(start));
                break;

            case 10:
                freeList(&start);
                printf("Exitting program...\n");
                exit(0);

            default:
                printf("Invalid Operation!\n");
        }

    } while (TRUE);
}

void freeList(node **list) {
    node *ptr = *list;
    while (ptr != NULL) {
        node *next = ptr->next;
        free(ptr);
        ptr = next;
    }
    printf("Initial List freed!\n");
}

node* getNode(void) {
    node *p = malloc(sizeof(node));

    if (p == NULL) {
        printf("Memory Unavailable!\n");
        freeList(&start);
        exit(1);
    }
    return p;
}

int isEmpty(node* start) {
    return ((start == NULL) ? TRUE : FALSE);
}

int numOfNodes(node *start) {
    node *i;
    int count = 0;
    for (i = start; i != NULL; i = i->next) {
        count++;
    }
    return count;
}

void firstInsert(node** start, int x) {
    node *item = getNode();
    item->info = x;

    if (isEmpty(*start) == TRUE) {
        item->next = NULL;
        *start = item;
    }
    else {
        item->next = *start;
        *start = item;
    }
} 

void lastInsert(node **start, int x) {
    node *item, *tmp;
    item = getNode();
    item->info = x;
    item->next = NULL;
    
    if (isEmpty(*start) == TRUE) 
        *start = item;
    else {
        tmp = *start;
        while (tmp->next != NULL) {
            tmp = tmp->next;
        }
        tmp->next = item;
    }
}

void nInsert(node **start, int x) {
    int n, count = 1;
    node *item, *tmp;
    item = getNode();
    item->info = x;
    
    do {
        printf("Enter the position to insert: ");
        scanf("%d", &n);
        if (n > numOfNodes(*start))
            printf("Position is a bit too HIGH (No item is present at that posn yet)!!\n");
    } while ((n <= 0) || (n > numOfNodes(*start))); // valid node number ko lagi

    /*
    TODO: 0 bata indexing start garera, apply python ko jasto negative/reverse indexing sheet to insert values?!
    */

    if (n == 1) {
        firstInsert(&(*start), x);
    }
    else {
        tmp = *start;
        while (count < (n-1)) {
            tmp = tmp->next;
            count++;
        }
        item->next = tmp->next;
        tmp->next = item;
    }
}

void firstDelete(node **start) {
    node *ptr;
    if ((*start)->next == NULL) {
        printf("Deleted Item is: %d\n", (*start)->info);
        free(*start);
        *start = NULL;
    }
    else {
        ptr = *start;
        *start = (*start)->next;
        printf("Deleted Item is: %d\n", ptr->info);
        free(ptr);
    }
}

void lastDelete(node **start) {
    node *ptr, *tmp;
    if ((*start)->next == NULL) {
        printf("Deleted Item is: %d\n", (*start)->info);
    }
    else {
        ptr = *start;
        while (ptr->next != NULL) {
            tmp = ptr;
            ptr = ptr->next;
        }
        tmp->next = NULL;
        printf("Deleted Item is: %d\n", ptr->info);
        free(ptr);
    }
}

void nDelete(node **start) {
    node *ptr, *tmp;
    int n, count = 1;

    do {
    printf("Enter the position of item to be deleted: ");
    scanf("%d", &n);
    } while (n < 1); // valid node number ko lagi

    ptr = *start;
    while (count < n) {
        count++;
        tmp = ptr;
        ptr = ptr->next;
        if (ptr == NULL) {
            printf("Out of Bound!\n");
            return;
        }
    }
    tmp->next = ptr->next;
    printf("Deleted Item is: %d\n", ptr->info);
    free(ptr);
}

void traverse(node *start) {
    node *i;
    printf("Items in the LIST: \n");
    for (i = start; i != NULL; i = i->next) {
        printf("%d\t", i->info);
    }
    printf("\n");
}

void search(node *start, int x) {
    int count = 0;
    node *ptr;
    ptr = start;
    
    do {
        count++;
        if (ptr->info == x) {
            printf("Number %d is at node %d\n", x, count);
            ptr = NULL;
            return;
        }
        else {
            ptr = ptr->next;
        }
    } while (ptr != NULL);
    printf("The number %d does not exist in the list!\n");
}