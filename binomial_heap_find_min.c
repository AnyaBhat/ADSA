#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Define the binomial tree node structure
struct node {
    int n;
    int degree;
    struct node* parent;
    struct node* child;
    struct node* sibling;
};

// Function prototypes
struct node* MAKE_bin_HEAP();
void bin_LINK(struct node*, struct node*);
struct node* CREATE_NODE(int);
struct node* bin_HEAP_UNION(struct node*, struct node*);
struct node* bin_HEAP_INSERT(struct node*, struct node*);
struct node* bin_HEAP_MERGE(struct node*, struct node*);
void DISPLAY_HEAP(struct node*);
int FIND_MIN_KEY(struct node*);

// Create an empty binomial heap
struct node* MAKE_bin_HEAP() {
    return NULL;
}

// Link two binomial trees
void bin_LINK(struct node* y, struct node* z) {
    y->parent = z;
    y->sibling = z->child;
    z->child = y;
    z->degree = z->degree + 1;
}

// Create a new node with given key
struct node* CREATE_NODE(int k) {
    struct node* p = (struct node*) malloc(sizeof(struct node));
    p->n = k;
    p->degree = 0;
    p->parent = NULL;
    p->child = NULL;
    p->sibling = NULL;
    return p;
}

// Merge two binomial heaps
struct node* bin_HEAP_MERGE(struct node* H1, struct node* H2) {
    struct node* H = MAKE_bin_HEAP();
    struct node *y = H1, *z = H2;
    struct node *prev_x = NULL, *next_x;

    if (y != NULL) {
        if (z != NULL && y->degree <= z->degree)
            H = y;
        else
            H = z;
    } else
        H = z;

    while (y != NULL && z != NULL) {
        if (y->degree < z->degree) {
            y = y->sibling;
        } else if (y->degree == z->degree) {
            next_x = y->sibling;
            y->sibling = z;
            y = next_x;
        } else {
            next_x = z->sibling;
            z->sibling = y;
            z = next_x;
        }
    }

    return H;
}

// Union of two binomial heaps
struct node* bin_HEAP_UNION(struct node* H1, struct node* H2) {
    struct node* H = bin_HEAP_MERGE(H1, H2);
    struct node *prev_x = NULL, *next_x = H, *x = H;

    if (H == NULL) return H;

    next_x = x->sibling;
    while (next_x != NULL) {
        if ((x->degree != next_x->degree) || (next_x->sibling != NULL && next_x->sibling->degree == x->degree)) {
            prev_x = x;
            x = next_x;
        } else {
            if (x->n <= next_x->n) {
                x->sibling = next_x->sibling;
                bin_LINK(next_x, x);
            } else {
                if (prev_x == NULL) H = next_x;
                else prev_x->sibling = next_x;
                bin_LINK(x, next_x);
                x = next_x;
            }
        }
        next_x = x->sibling;
    }
    return H;
}

// Insert a new node into the binomial heap
struct node* bin_HEAP_INSERT(struct node* H, struct node* x) {
    struct node* H1 = MAKE_bin_HEAP();
    x->parent = NULL;
    x->child = NULL;
    x->sibling = NULL;
    x->degree = 0;
    H1 = x;
    H = bin_HEAP_UNION(H, H1);
    return H;
}

// Helper function to collect nodes by levels
void collect_levels(struct node* H, int* levels, int* level_counts, int level) {
    if (H == NULL) return;

    struct node* current = H;
    while (current != NULL) {
        level_counts[level]++;
        levels[level * 100 + level_counts[level] - 1] = current->n; // Store nodes in the level array
        collect_levels(current->child, levels, level_counts, level + 1);
        current = current->sibling;
    }
}

// Display the binomial heap with levels
void DISPLAY_HEAP(struct node* H) {
    if (H == NULL) {
        printf("\nHEAP EMPTY");
        return;
    }

    // Array to hold node values by levels
    int levels[1000] = {0}; // Assume a maximum of 100 levels and 10 nodes per level
    int level_counts[100] = {0}; // Number of nodes at each level

    // Collect nodes by levels
    collect_levels(H, levels, level_counts, 0);

    // Display the levels
    printf("\nHEAP LEVELS:\n");
    int current_level = 0;
    while (level_counts[current_level] > 0) {
        printf("Level %d: ", current_level);
        for (int i = 0; i < level_counts[current_level]; i++) {
            printf("%d ", levels[current_level * 100 + i]);
        }
        printf("\n");
        current_level++;
    }
}

// Find the minimum key in the binomial heap
int FIND_MIN_KEY(struct node* H) {
    if (H == NULL) {
        printf("Heap is empty.\n");
        return -1; // Indicates that the heap is empty
    }

    int min = H->n;
    struct node* current = H;

    while (current != NULL) {
        if (current->n < min) {
            min = current->n;
        }
        current = current->sibling;
    }
    return min;
}

// Amortized cost analysis methods
void accounting_method(int n) {
    // Each insertion operation takes O(1) time amortized
    double amortized_cost = 1.0; // Each insertion is constant time
    double total_cost = n * amortized_cost;
    printf("Accounting Method Analysis:\n");
    printf("For %d insertions, total amortized cost is %.2f units.\n", n, total_cost);
}

void aggregate_method(int n) {
    // Total cost of n insertions is O(n log n)
    // Amortized cost per insertion: O(log n)
    double total_cost = n * log2(n);
    double amortized_cost = log2(n);
    printf("Aggregate Method Analysis:\n");
    printf("For %d insertions, total cost is approximately O(%d log %d) = %.2f units.\n", n, n, n, total_cost);
    printf("Amortized cost per insertion is approximately O(log %d) = %.2f units.\n", n, amortized_cost);
}

void potential_method(int n) {
    // Amortized cost per insertion is O(1)
    double amortized_cost = 1.0; // Each insertion is constant time
    double total_cost = n * amortized_cost;
    printf("Potential Method Analysis:\n");
    printf("For %d insertions, total amortized cost is %.2f units.\n", n, total_cost);
}

// Main function to test the heap operations
int main() {
    struct node* H = MAKE_bin_HEAP();
    int n, m;
    struct node* p;

    printf("Enter the number of elements: ");
    scanf("%d", &n);

    printf("Enter the elements:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &m);
        p = CREATE_NODE(m);
        H = bin_HEAP_INSERT(H, p);
    }

    printf("\nCurrent state of the heap:\n");
    DISPLAY_HEAP(H);

    int min_key = FIND_MIN_KEY(H);
    if (min_key != -1) {
        printf("Minimum key in the heap: %d\n", min_key);
    }

    // Amortized cost analysis
    accounting_method(n);
    aggregate_method(n);
    potential_method(n);

    return 0;
}


/*
$ gcc -o b_e_min.out binomial_extract_min.c -lm
$ ./b_e_min.out
Enter the number of elements: 10
Enter the elements:
30 21 11 27 17 8 19 41 58 18

Current state of the heap:

HEAP LEVELS:
Level 0: 18 8 
Level 1: 58 11 19 17 
Level 2: 21 27 41 
Level 3: 30 
Minimum key in the heap: 8
Accounting Method Analysis:
For 10 insertions, total amortized cost is 10.00 units.
Aggregate Method Analysis:
For 10 insertions, total cost is approximately O(10 log 10) = 33.22 units.
Amortized cost per insertion is approximately O(log 10) = 3.32 units.
Potential Method Analysis:
For 10 insertions, total amortized cost is 10.00 units.

*/
