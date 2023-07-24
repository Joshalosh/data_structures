#include <stdio.h>
#include <stdlib.h>

#define MAX 3
#define MIN 2

struct Tree_Node {
    int        val[MAX + 1];
    int        count;
    Tree_Node *link[MAX + 1];
};

Tree_Node *root;

// Create a node
Tree_Node *CreateNode(int val, Tree_Node *child) {
    Tree_Node *new_node;
    new_node          = (Tree_Node *)malloc(sizeof(Tree_Node));
    new_node->val[1]  = val;
    new_node->count   = 1;
    new_node->link[0] = root;
    new_node->link[1] = child;

    return new_node;
}

// Insert a node
void InsertNode(int val, int pos, Tree_Node *node, Tree_Node *child) {
    int j = node->count;
    while (j > pos) {
        node->val[j + 1] = node->val[j];
        node->link[j + 1] = node->link[j];
        j--;
    }
    node->val[j + 1]  = val;
    node->link[j + 1] = child;
    node->count++;
}

// Split node
void SplitNode(int val, int *pval, int pos, Tree_Node *node, 
               Tree_Node *child, Tree_Node **new_node) {
    int median;
    int j;

    if (pos > MIN) {
        median = MIN + 1;
    } else {
        median = MIN;
    }

    *new_node = (Tree_Node *)malloc(sizeof(Tree_Node));
    j = median + 1;
    while (j <= MAX) {
        (*new_node)->val[j - median]  = node->val[j];
        (*new_node)->link[j - median] = node->link[j];
        j++;
    }
    node->count = median;
    (*new_node)->count = MAX - median;

    if (pos <= MIN) {
        InsertNode(val, pos, node, child);
    } else {
        InsertNode(val, pos - median, *new_node, child);
    }
    *pval = node->val[node->count];
    (*new_node)->link[0] = node->link[node->count];
    node->count--;
}

// Set the value
int SetValue(int val, int *pval, Tree_Node *node, Tree_Node **child) {
    int pos;
    if (!node) {
        *pval  = val;
        *child = NULL;
        return 1;
    }

    if (val < node->val[1]) {
        pos = 0;
    } else {
        for (pos = node->count;
             (val < node->val[pos] && pos > 1);
             pos--)
            ;
        if (val == node->val[pos]) {
            printf("Duplicates are not permitted\n");
            return 0;
        }
    }
    if (SetValue(val, pval, node->link[pos], child)) {
        if (node->count < MAX) {
            InsertNode(*pval, pos, node, *child);
        } else {
            SplitNode(*pval, pval, pos, node, *child, child);
            return 1;
        }
    }
    return 0;
}

// Insert the value 
void Insert(int val) {
    int flag;
    int i;
    Tree_Node *child;

    flag = SetValue(val, &i, root, &child);
    if (flag) {
        root = CreateNode(i, child);
    }
}

// Search node 
void Search(int val, int *pos, Tree_Node *my_node) {
    if (!my_node) {
        return;
    }

    if (val < my_node->val[1]) {
        *pos = 0;
    } else {
        for (*pos = my_node->count;
             (val < my_node->val[*pos] && *pos > 1);
             (*pos)--)
            ;
        if (val == my_node->val[*pos]) {
            printf("%d is found", val);
            return;
        }
    }
    Search(val, pos, my_node->link[*pos]);

    return;
}

// Traverse then nodes
void Traversal(Tree_Node *my_node) {
    int i;
    if (my_node) {
        for (i = 0; i < my_node->count; i++) {
            Traversal(my_node->link[i]);
            printf("%d ", my_node->val[i + 1]);
        }
        Traversal(my_node->link[i]);
    }
}

int main() {
    int val;
    int ch;

    Insert(8);
    Insert(9);
    Insert(10);
    Insert(11);
    Insert(15);
    Insert(16);
    Insert(17);
    Insert(18);
    Insert(20);
    Insert(23);

    Traversal(root);

    printf("\n");
    Search(11, &ch, root);
}

