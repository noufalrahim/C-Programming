#include<stdio.h>
#include<stdlib.h>

struct TreeNode {
    char val;
    struct TreeNode* left;
    struct TreeNode* right;
};

struct TreeNode* createNode(char val) {
    struct TreeNode* newnode = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    newnode->val = val;
    newnode->left = NULL;
    newnode->right = NULL;
    return newnode;
}

struct TreeNode* convertToTree(char exp[], int* index) {
    struct TreeNode* root = NULL;

    if (exp[*index] == '\0' || exp[*index] == ')') {
        (*index)++;
        return NULL;
    }

    root = createNode(exp[*index]);

    (*index)++;

    if (exp[*index] == '(') {
        (*index)++;
        root->left = convertToTree(exp, index);
    }

    if (exp[*index] == '(') {
        (*index)++;
        root->right = convertToTree(exp, index);
    }

    (*index)++;

    return root;
}

void printRangeValues(struct TreeNode* root, char k1, char k2) {
    if (root == NULL) {
        return;
    }

    if (root->val > k1) {
        printRangeValues(root->left, k1, k2);
    }

    if (root->val >= k1 && root->val <= k2) {
        printf("%c ", root->val);
    }

    if (root->val < k2) {
        printRangeValues(root->right, k1, k2);
    }
}

int printAncestors(struct TreeNode* root, char k) {
    if (root == NULL) {
        return 0;
    }
    if (root->val == k) {
        printf("%c ", root->val);
        return 1;
    }
    if (printAncestors(root->left, k) || printAncestors(root->right, k)) {
        printf("%c ", root->val);
        return 1;
    }
    return 0;
}

int main() {
    char exp[1000];
    scanf("%s", exp);
    int index = 0;
    struct TreeNode* root = convertToTree(exp, &index);

    char choice;

    while (1) {
        scanf(" %c", &choice);
        if (choice == 'e') {
            break;
        } else if (choice == 'p') {
            char num1, num2;
            scanf(" %c %c", &num1, &num2);
            printRangeValues(root, num1, num2);
            printf("\n");
        } else if (choice == 'a') {
            char num1;
            scanf(" %c", &num1);
            printAncestors(root, num1);
            printf("\n");
        }
    }

    return 0;
}
