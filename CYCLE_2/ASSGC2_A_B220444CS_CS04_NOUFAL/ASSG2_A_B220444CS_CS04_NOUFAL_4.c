#include<stdio.h>
#include<stdlib.h>

struct TreeNode{
    int val;
    char color;
    struct TreeNode* left;
    struct TreeNode* right;
};

struct TreeNode* createTreeNode(int val, int color) {
    struct TreeNode* newNode = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    newNode->val = val;
    newNode->color = color;
    newNode->left = newNode->right = NULL;
    return newNode;
}


struct TreeNode* convertToTree(char exp[], int* index) {
   

    if (exp[*index] == '\0' || exp[*index] == ')') {
        (*index)++;
        return NULL;
    }
    

    int data = 0;
    int color = 1;
    while(exp[*index] >= '0' && exp[*index] <= '9'){
      data = data * 10 + (exp[*index] - '0');
      (*index)++;
      if(exp[*index] == 'R'){
        color = 1;
      }
      else{
        color = 0;
      }
      (*index)++;
    }
    
    struct TreeNode* root = createTreeNode(data, color);

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


void inorder(struct TreeNode* root){
    if(root == NULL){
        return;
    }
    inorder(root -> left);
    printf("%d ", root -> val);
    inorder(root -> right);
}
int isRedBlackTreeUtil(struct TreeNode* root, int blackCount, int currentBlackCount) {
    if (root == NULL) {
        if (blackCount == -1) {
            blackCount = currentBlackCount;
        } else if (blackCount != currentBlackCount) {
            return 0;
        }
        return 1;
    }

    if (root->color == 1 && (
        (root->left != NULL && root->left->color == 1) ||
        (root->right != NULL && root->right->color == 1))) {
        return 0;
    }

    return isRedBlackTreeUtil(root->left, blackCount, (root->color == 0) ? currentBlackCount + 1 : currentBlackCount) &&
           isRedBlackTreeUtil(root->right, blackCount, (root->color == 0) ? currentBlackCount + 1 : currentBlackCount);
}

int isRedBlackTree(struct TreeNode* root) {
    return isRedBlackTreeUtil(root, -1, 0);
}

int main(){
    char exp[100];
    scanf("%s", exp);
    int index = 0;
    struct TreeNode* root = convertToTree(exp, &index);
    printf("%d", isRedBlackTree(root));
    return 0;
}