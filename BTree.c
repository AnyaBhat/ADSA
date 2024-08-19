#include <stdio.h>
#include <stdlib.h>

#define T 2  // Minimum degree (defines the range for number of keys)

// A BTree node
typedef struct BTreeNode {
    int *keys;         // An array of keys
    struct BTreeNode **children; // An array of child pointers
    int numKeys;       // Current number of keys
    int leaf;          // 1 if leaf node, 0 otherwise
} BTreeNode;

// Function prototypes
BTreeNode* createNode(int t, int leaf);
void traverse(BTreeNode *node);
BTreeNode* search(BTreeNode *node, int key);
void insert(BTreeNode **root, int key);
void splitChild(BTreeNode *parent, int index, BTreeNode *fullChild);
void insertNonFull(BTreeNode *node, int key);

// Create a new B-Tree node
BTreeNode* createNode(int t, int leaf) {
    BTreeNode *newNode = (BTreeNode *)malloc(sizeof(BTreeNode));
    newNode->keys = (int *)malloc((2 * t - 1) * sizeof(int));
    newNode->children = (BTreeNode **)malloc(2 * t * sizeof(BTreeNode *));
    newNode->numKeys = 0;
    newNode->leaf = leaf;
    return newNode;
}

// Traverse the B-Tree
void traverse(BTreeNode *node) {
    int i;
    for (i = 0; i < node->numKeys; i++) {
        if (!node->leaf) {
            traverse(node->children[i]);
        }
        printf("%d ", node->keys[i]);
    }
    if (!node->leaf) {
        traverse(node->children[i]);
    }
}

// Search for a key in the B-Tree
BTreeNode* search(BTreeNode *node, int key) {
    int i = 0;
    while (i < node->numKeys && key > node->keys[i]) {
        i++;
    }
    if (i < node->numKeys && node->keys[i] == key) {
        return node;
    }
    if (node->leaf) {
        return NULL;
    }
    return search(node->children[i], key);
}

// Split the child of a node
void splitChild(BTreeNode *parent, int index, BTreeNode *fullChild) {
    int t = T;
    BTreeNode *newChild = createNode(t, fullChild->leaf);
    parent->children[index + 1] = newChild;
    parent->keys[index] = fullChild->keys[t - 1];
    newChild->numKeys = t - 1;
    fullChild->numKeys = t - 1;

    for (int j = 0; j < t - 1; j++) {
        newChild->keys[j] = fullChild->keys[j + t];
    }
    if (!fullChild->leaf) {
        for (int j = 0; j < t; j++) {
            newChild->children[j] = fullChild->children[j + t];
        }
    }
}

// Insert a key into the B-Tree
void insert(BTreeNode **root, int key) {
    BTreeNode *r = *root;
    if (r->numKeys == 2 * T - 1) {
        BTreeNode *newRoot = createNode(T, 0);
        *root = newRoot;
        newRoot->children[0] = r;
        splitChild(newRoot, 0, r);
        insertNonFull(newRoot, key);
    } else {
        insertNonFull(r, key);
    }
}

// Insert a key into a non-full node
void insertNonFull(BTreeNode *node, int key) {
    int i = node->numKeys - 1;
    if (node->leaf) {
        while (i >= 0 && key < node->keys[i]) {
            node->keys[i + 1] = node->keys[i];
            i--;
        }
        node->keys[i + 1] = key;
        node->numKeys++;
    } else {
        while (i >= 0 && key < node->keys[i]) {
            i--;
        }
        i++;
        if (node->children[i]->numKeys == 2 * T - 1) {
            splitChild(node, i, node->children[i]);
            if (key > node->keys[i]) {
                i++;
            }
        }
        insertNonFull(node->children[i], key);
    }
}

// Main function to demonstrate the B-Tree
int main() {
    BTreeNode *root = createNode(T, 1);
    int numKeys;

    // Get number of elements from user
    printf("Enter the number of elements to insert: ");
    scanf("%d", &numKeys);

    // Allocate memory for the keys
    int *keys = (int *)malloc(numKeys * sizeof(int));
    
    // Get elements from user
    printf("Enter the elements:\n");
    for (int i = 0; i < numKeys; i++) {
        scanf("%d", &keys[i]);
        insert(&root, keys[i]);
    }

    // Traverse the B-Tree
    printf("Traversal of B-Tree:\n");
    traverse(root);
    printf("\n");

    // Search for a key
    int keyToSearch;
    printf("Enter an element to search:");
    scanf("%d",&keyToSearch);
    BTreeNode *result = search(root, keyToSearch);
    if (result != NULL) {
        printf("Searching  for key %d..... Found\n", keyToSearch);
    } else {
        printf("Searching for key %d ...... Not Found\n", keyToSearch);
    }

    // Free allocated memory (not shown here)
    // You should add code to free the memory allocated for nodes

    return 0;
}

