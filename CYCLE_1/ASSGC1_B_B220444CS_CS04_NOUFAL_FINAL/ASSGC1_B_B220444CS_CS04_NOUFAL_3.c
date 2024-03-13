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
   

    if (exp[*index] == '\0' || exp[*index] == ')') {
        (*index)++;
        return NULL;
    }
    

    int data = 0;
    
    while(exp[*index] >= '0' && exp[*index] <= '9'){
      data = data * 10 + (exp[*index] - '0');
      (*index)++;
    }
    
    struct TreeNode* root = createNode(data);

    if (exp[*index] == '(') {
        (*index)++;
        root->left = convertToTree(exp, index);
    }

    if (exp[*index] == '(') {
        (*index)++;
        root->right = convertToTree(exp, index);
    }
    
    if (exp[*index] == ')') {
        (*index)++;
    }


    return root;
}

void printRangeValues(struct TreeNode* root, int k1, int k2) {
    if (root == NULL) {
        return;
    }

    if (root->val > k1) {
        printRangeValues(root->left, k1, k2);
    }

    if (root->val >= k1 && root->val <= k2) {
        printf("%d ", root->val);
    }

    if (root->val < k2) {
        printRangeValues(root->right, k1, k2);
    }
}

int printAncestors(struct TreeNode* root, int k) {
    if (root == NULL) {
        return 0;
    }
    if (root->val == k) {
        printf("%d ", root->val);
        return 1;
    }
    if (printAncestors(root->left, k) || printAncestors(root->right, k)) {
        printf("%d ", root->val);
        return 1;
    }
    return 0;
}

void postOrderTraversal(struct TreeNode* root) {
    if (root != NULL) {
        postOrderTraversal(root->left);
        postOrderTraversal(root->right);
        printf("%d ", root->val);
    }
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
            int num1, num2;
            scanf(" %d %d", &num1, &num2);
            printRangeValues(root, num1, num2);
            printf("\n");
        } else if (choice == 'a') {
            int num1;
            scanf(" %d", &num1);
            printAncestors(root, num1);
            printf("\n");
        }
        
    }

    return 0;
}
