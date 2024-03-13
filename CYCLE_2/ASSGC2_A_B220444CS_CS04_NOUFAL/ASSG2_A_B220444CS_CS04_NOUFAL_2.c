#include <stdio.h>
#include <stdlib.h>

struct AVLNode {
    int key;
    int value;
    int height;
    struct AVLNode* left;
    struct AVLNode* right;
};

int max(int a, int b) {
    return (a > b) ? a : b;
}

int height(struct AVLNode* node) {
    if (node == NULL)
        return 0;
    return node->height;
}

struct AVLNode* createNode(int key, int value) {
    struct AVLNode* newNode = (struct AVLNode*)malloc(sizeof(struct AVLNode));
    newNode->key = key;
    newNode->value = value;
    newNode->height = 1;
    newNode->left = newNode->right = NULL;
    return newNode;
}

struct AVLNode* leftRotate(struct AVLNode* y) {
    struct AVLNode* x = y->right;
    struct AVLNode* T2 = x->left;

    x->left = y;
    y->right = T2;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

struct AVLNode* rightRotate(struct AVLNode* x) {
    struct AVLNode* y = x->left;
    struct AVLNode* T2 = y->right;

    y->right = x;
    x->left = T2;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

int getBalance(struct AVLNode* node) {
    if (node == NULL)
        return 0;
    return height(node->left) - height(node->right);
}

struct AVLNode* insert(struct AVLNode* root, int key, int value) {
    if (root == NULL)
        return createNode(key, value);

    if (key < root->key)
        root->left = insert(root->left, key, value);
    else if (key > root->key)
        root->right = insert(root->right, key, value);
    else {
        root->value = value;
        return root;
    }

    root->height = 1 + max(height(root->left), height(root->right));

    int balance = getBalance(root);

    if (balance > 1 && key < root->left->key)
        return rightRotate(root);

    if (balance < -1 && key > root->right->key)
        return leftRotate(root);

    if (balance > 1 && key > root->left->key) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    if (balance < -1 && key < root->right->key) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

void lowerbound(struct AVLNode* root, int key) {
    if (root == NULL) {
        printf("-1\n");
        return;
    }

    if (root->key == key) {
        printf("%d %d\n", root->key, root->value);
        return;
    } else if (root->key > key) {
        lowerbound(root->left, key);
    } else {
        lowerbound(root->right, key);
    }
}

void find(struct AVLNode* root, int key) {
    if (root == NULL) {
        printf("-1\n");
        return;
    }

    if (root->key == key) {
        printf("%d %d\n", root->key, root->value);
        return;
    } else if (root->key > key) {
        find(root->left, key);
    } else {
        find(root->right, key);
    }
}

int size(struct AVLNode* root) {
    if (root == NULL)
        return 0;
    return size(root->left) + size(root->right) + 1;
}

int empty(struct AVLNode* root) {
    return (root == NULL) ? 1 : 0;
}

void printElements(struct AVLNode* root) {
    if (root == NULL) {
        printf("-1\n");
        return;
    }

    printElements(root->left);
    printf("%d ", root->key);
    printElements(root->right);
}

int main() {
    struct AVLNode* root = NULL;

    char choice;
    while (1) {
        scanf(" %c", &choice);

        if (choice == 't')
            break;

        switch (choice) {
            case 'i': {
                int key, value;
                scanf("%d %d", &key, &value);
                root = insert(root, key, value);
                break;
            }
            case 'l': {
                int key;
                scanf("%d", &key);
                lowerbound(root, key);
                break;
            }
            case 'f': {
                int key;
                scanf("%d", &key);
                find(root, key);
                break;
            }
            case 's':
                printf("%d\n", size(root));
                break;
            case 'e':
                printf("%d\n", empty(root));
                break;
            case 'p':
                printElements(root);
                printf("\n");
                break;
        }
    }

    return 0;
}
