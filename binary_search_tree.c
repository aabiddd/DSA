// BST
#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define max(a, b) (((a) > (b)) ? a : b)

// representation of each node in a binary search tree
typedef struct node {
    int info;
    struct node* left;
    struct node* right;
} node;

// pointer d-type pointing to a node
typedef node* nodeptr;

// function prototypes
nodeptr get_node(nodeptr*, int);
void free_node(nodeptr); // frees a single node
void free_tree(nodeptr*); // frees a whole tree
nodeptr search(nodeptr, int);
nodeptr tree_min(nodeptr);
nodeptr tree_max(nodeptr);
nodeptr insert(nodeptr*, int);
nodeptr del(nodeptr*, int);
int count_nodes(nodeptr);
int tree_height(nodeptr);
void preorder(nodeptr);
void inorder(nodeptr);
void postorder(nodeptr);

void main() {
    nodeptr tmp, root = NULL;
    int mode, x;

    do {
        printf("\nModes:\n");
        printf("1.  Insert a key.\n");
        printf("2.  Delete a key.\n");
        printf("3.  Search a key.\n");
        printf("4.  Print nodes in preorder.\n");
        printf("5.  Print nodes in inorder.\n");
        printf("6.  Print nodes in postorder.\n");
        printf("7.  Number of nodes in the tree.\n");
        printf("8.  Minimum value in the tree.\n");
        printf("9.  Maximum value in the tree.\n");
        printf("10. Height of the tree.\n");
        printf("11. Exit the program.\n\n");

        printf("Enter mode: ");
        scanf("%d", &mode);

        switch (mode) {
            case 1: // insert
            printf("Enter the key to insert: ");
            scanf("%d", &x);
            if (search(root, x) == NULL)
                root = insert(&root, x);
            else
                printf("Key %d is already present in the tree!\n", x);
            break;

            case 2: // delete
            printf("Enter the key to be deleted: ");
            scanf("%d", &x);
            if (search(root, x) != NULL)
                root = del(&root, x);
            else
                printf("Key %d is not present in the tree!\n", x);
            break;

            case 3: // search
            printf("Enter the key to be searched: ");
            scanf("%d", &x);
            tmp = search(root, x);
            if (tmp == NULL)
                printf("Key %d is not present in the tree!\n", x);
            else
                printf("Key %d FOUND!\n", tmp->info);
            break;

            case 4: // preorder
            printf("Preorder Traversal: \n");
            preorder(root);
            printf("\n");
            break;

            case 5: // inorder
            printf("Inorder Traversal: \n");
            inorder(root);
            printf("\n");
            break;

            case 6: // postorder
            printf("Postorder Traversal: \n");
            postorder(root);
            printf("\n");
            break;

            case 7: // total no. of nodes
            printf("Total number of nodes currently in the tree: %d\n", count_nodes(root));
            break;

            case 8: // min. value
            printf("Minimum value present in the tree: %d\n", tree_min(root)->info);
            break;

            case 9: // max. value
            printf("Maximum value present in the tree: %d\n", tree_max(root)->info);
            break;

            case 10: // height of tree
            printf("Height of the tree: %d\n", tree_height(root));
            break;

            case 11: // exit
            printf("Exitting program...\n");
            free(&root);
            exit(0);

            default:
                printf("Invalid Operation!\n");
        }
    } while (TRUE);
}

// function definitions
nodeptr get_node(nodeptr *root, int x) {
    // takes tree as a parameter so that it can free the tree it is working on, if in any case memory for new node is unavailable
    nodeptr n = malloc(sizeof(node));
    if (n == NULL) {
        printf("MEMORY UNAVAILABLE!\n");
        free_tree(root);
        exit(5);
    }

    n->info = x;
    // no child elements of new node
    n->left = NULL;
    n->right = NULL;

    return n;
}

void free_node(nodeptr n) {
    free(n);
}

void free_tree(nodeptr* root) {
    if (*root == NULL)
        return;

    // first free the left and right subtrees
    free_tree(&(*root)->left);
    free_tree(&(*root)->right);
    // free the current node
    free_node(*root);
    // setting the root pointer to NULL after freeing the node
    *root = NULL;
}

nodeptr search(nodeptr root, int key) { // O(H) not O(logn)
    if (root == NULL) // tree is empty
        return root; // NULL
    else {
        if (key < root->info)
            return search(root->left, key);
        else if(key > root->info)
            return search(root->right, key);
        else
            return root; // base case: info of tree(root) node is equal to the key
    }
}

nodeptr tree_min(nodeptr root) {
    nodeptr tmp;
    tmp = root;

    if ((tmp == NULL) || (tmp->left == NULL))
        return tmp; // will return NULL if tree is empty and root node if no left subtree is present
    else {
        while (tmp->left != NULL) {
            tmp = tmp->left;
        }
        return tmp; // bottom left of BST is min. value
    }
}

nodeptr tree_max(nodeptr root) {
    nodeptr tmp;
    tmp = root;

    if ((tmp == NULL) || (tmp->right == NULL))
        return tmp; // NULL if empty tree, root node if no right subtree is present
    else {
        while (tmp->right != NULL) {
            tmp = tmp->right;
        }
        return tmp; // bottom right of BST is max. value
    }
}

nodeptr insert(nodeptr* root, int key) {
    // assuming that key parameter is not already present in the tree (code for checking that is applied in main())
    if (*root == NULL) {
        *root = get_node(root, key);
        return (*root);
    }
    else if (key < (*root)->info) {
        (*root)->left = insert(&(*root)->left, key);
    }
    else if (key > (*root)->info) {
        (*root)->right = insert(&(*root)->right, key);
    }
    return (*root);
}

nodeptr del(nodeptr* root, int key) {
    // 3 cases for deletion: leaf node, one child, two children
    // given that the key is present in the tree (searching is done in main())
    // two children case ma replace it with inorder successor i.e. leftmost node of right subtree
    // or inorder predecessor i.e. rightmost node of left subtree
    if (key < (*root)->info) {
        (*root)->left = del(&(*root)->left, key);
    }
    else if (key > (*root)->info) {
        (*root)->right = del(&(*root)->right, key);
    }
    else { // root->info == key
        // case 1: leaf node
        if (((*root)->left == NULL) && ((*root)->right == NULL)) {
            free_node(*root);
            return NULL;
        }

        // case 2: one chlid node
        else if ((*root)->left == NULL) {
            // return right
            nodeptr tmp = *root;
            *root = (*root)->right;
            free_node(tmp);
        }
        else if ((*root)->right == NULL) {
            // return left
            nodeptr tmp = *root;
            *root = (*root)->left;
            free_node(tmp);
        }

        // case 3: two chlidren
        else {
            int leftCount = count_nodes((*root)->left);
            int rightCount = count_nodes((*root)->right);

            if (leftCount > rightCount) { // inorder predecessor
                nodeptr predecessor = tree_max((*root)->left); // rightmost node of left subtree
                (*root)->info = predecessor->info;
                // we wont directly free the predecessor node since it might contain left subtree(1child)
                // nodeptr leftChild = (*root)->left;
                (*root)->left = del(&((*root)->left), predecessor->info);
            }
            else { // inorder sucessor
                nodeptr successor = tree_min((*root)->right); // leftmost node of right subtree
                (*root)->info = successor->info;
                // nodeptr rightChild = (*root)->right;
                (*root)->right = del(&((*root)->right), successor->info);
            }
        }
    }
    return (*root);
}

int count_nodes(nodeptr root) {
    if (root == NULL)
        return 0; // base case
    // counts no. of nodes at left subroot, right subtree and 1 as itself
    return (count_nodes(root->left) + count_nodes(root->right) + 1);
}

int tree_height(nodeptr root) {
    if (root == NULL)
        return 0; // base case

    int left_height = tree_height(root->left); // height of left subtree
    int right_height = tree_height(root->right); // height of right subtree
    int node_height = max(left_height, right_height) + 1; // max height between left and right + 1 => height of node

    return node_height;
}

void preorder(nodeptr root) {
    // root node, left subtree, right subtree
    if (root != NULL) {
        printf("%d\t", root->info);
        preorder(root->left);
        preorder(root->right);
    }
}

void inorder(nodeptr root) {
    // left subtree, root node, right subtree
    if (root != NULL) {
        inorder(root->left);
        printf("%d\t", root->info);
        inorder(root->right);
    }
}

void postorder(nodeptr root) {
    // left subtree, right subtree, root node
    if (root != NULL) {
        postorder(root->left);
        postorder(root->right);
        printf("%d\t", root->info);
    }
}
