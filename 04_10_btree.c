#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MIN_DEGREE 3  // Minimum degree (t)

// -------------------------------
// B-Tree Node Structure
// -------------------------------
typedef struct BTreeNode {
    int keys[2 * MIN_DEGREE - 1];      // Array of keys
    struct BTreeNode* children[2 * MIN_DEGREE]; // Array of child pointers
    int numKeys;                       // Number of keys
    bool isLeaf;                       // Is true if leaf node
} BTreeNode;

// -------------------------------
// B-Tree Structure
// -------------------------------
typedef struct BTree {
    BTreeNode* root;
} BTree;

// -------------------------------
// Utility: Create a new B-Tree Node
// -------------------------------
BTreeNode* createNode(bool isLeaf) {
    BTreeNode* node = (BTreeNode*)malloc(sizeof(BTreeNode));
    node->isLeaf = isLeaf;
    node->numKeys = 0;
    for (int i = 0; i < 2 * MIN_DEGREE; i++)
        node->children[i] = NULL;
    return node;
}

// -------------------------------
// createTree(): Initialize an empty B-Tree
// -------------------------------
BTree* createTree() {
    BTree* tree = (BTree*)malloc(sizeof(BTree));
    tree->root = createNode(true);
    return tree;
}

// -------------------------------
// searchItem(): Search a key in B-Tree
// -------------------------------
BTreeNode* searchItem(BTreeNode* node, int key) {
    int i = 0;
    while (i < node->numKeys && key > node->keys[i])
        i++;

    if (i < node->numKeys && key == node->keys[i])
        return node;

    if (node->isLeaf)
        return NULL;

    return searchItem(node->children[i], key);
}

// -------------------------------
// splitChild(): Split the full child
// -------------------------------
void splitChild(BTreeNode* parent, int i) {
    BTreeNode* y = parent->children[i];
    BTreeNode* z = createNode(y->isLeaf);
    z->numKeys = MIN_DEGREE - 1;

    for (int j = 0; j < MIN_DEGREE - 1; j++)
        z->keys[j] = y->keys[j + MIN_DEGREE];

    if (!y->isLeaf) {
        for (int j = 0; j < MIN_DEGREE; j++)
            z->children[j] = y->children[j + MIN_DEGREE];
    }

    y->numKeys = MIN_DEGREE - 1;

    for (int j = parent->numKeys; j >= i + 1; j--)
        parent->children[j + 1] = parent->children[j];

    parent->children[i + 1] = z;

    for (int j = parent->numKeys - 1; j >= i; j--)
        parent->keys[j + 1] = parent->keys[j];

    parent->keys[i] = y->keys[MIN_DEGREE - 1];
    parent->numKeys++;
}

// -------------------------------
// insertNonFull(): Insert into non-full node
// -------------------------------
void insertNonFull(BTreeNode* node, int key) {
    int i = node->numKeys - 1;

    if (node->isLeaf) {
        while (i >= 0 && key < node->keys[i]) {
            node->keys[i + 1] = node->keys[i];
            i--;
        }
        node->keys[i + 1] = key;
        node->numKeys++;
    } else {
        while (i >= 0 && key < node->keys[i])
            i--;

        i++;
        if (node->children[i]->numKeys == 2 * MIN_DEGREE - 1) {
            splitChild(node, i);

            if (key > node->keys[i])
                i++;
        }
        insertNonFull(node->children[i], key);
    }
}

// -------------------------------
// insertItem(): Insert a key into the B-Tree
// -------------------------------
void insertItem(BTree* tree, int key) {
    BTreeNode* root = tree->root;

    if (root->numKeys == 2 * MIN_DEGREE - 1) {
        BTreeNode* newRoot = createNode(false);
        newRoot->children[0] = root;
        splitChild(newRoot, 0);
        insertNonFull(newRoot, key);
        tree->root = newRoot;
    } else {
        insertNonFull(root, key);
    }
}

// -------------------------------
// printTree(): Inorder traversal
// -------------------------------
void printTree(BTreeNode* node, int level) {
    if (node != NULL) {
        int i;
        for (i = 0; i < node->numKeys; i++) {
            if (!node->isLeaf)
                printTree(node->children[i], level + 1);
            printf("%*s%d\n", level * 4, "", node->keys[i]);
        }
        if (!node->isLeaf)
            printTree(node->children[i], level + 1);
    }
}

// -------------------------------
// deleteTree(): Free all nodes
// -------------------------------
void deleteTree(BTreeNode* node) {
    if (node) {
        if (!node->isLeaf) {
            for (int i = 0; i <= node->numKeys; i++)
                deleteTree(node->children[i]);
        }
        free(node);
    }
}

// -------------------------------
// MAIN FUNCTION (Test)
// -------------------------------
int main() {
    BTree* tree = createTree();

    // Insert some keys
    int keys[] = {10, 20, 5, 6, 12, 30, 7, 17};
    int n = sizeof(keys) / sizeof(keys[0]);

    for (int i = 0; i < n; i++) {
        insertItem(tree, keys[i]);
    }

    printf("B-Tree (inorder traversal):\n");
    printTree(tree->root, 0);

    // Search
    int searchKey = 6;
    BTreeNode* result = searchItem(tree->root, searchKey);
    printf("\nSearch %d: %s\n", searchKey, result ? "Found" : "Not Found");

    // Cleanup
    deleteTree(tree->root);
    free(tree);

    return 0;
}
