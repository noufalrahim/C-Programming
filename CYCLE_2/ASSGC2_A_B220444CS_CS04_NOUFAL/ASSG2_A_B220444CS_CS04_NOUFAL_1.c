#include<stdio.h>
#include<stdlib.h>

struct TreeNode{
    int val;
    int height;
    struct TreeNode* left;
    struct TreeNode* right;
};

struct TreeNode* createNode(int val){
    struct TreeNode* newNode = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    newNode->val = val;
    newNode->height = 1;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

int heightOfNode(struct TreeNode* root){
    if(root == NULL){
        return 0;
    }

    int height = 0;
    int left = heightOfNode(root->left);
    int right = heightOfNode(root->right);

    if(left > right){
        height = left + 1;
    }
    else{
        height = right + 1;
    }

    return height;
}

int BalanceFactor(struct TreeNode* root){
    if(root == NULL){
        return 0;
    }
    int lheight = root -> left == NULL ? 0 : root -> left -> height;
    int rheight = root -> right == NULL ? 0 : root -> right -> height;

    return (lheight - rheight);
}

struct TreeNode* LLRotation(struct TreeNode* root){
    struct TreeNode* temp = root -> left;
    root -> left = temp -> right;
    temp -> right = root;
    root -> height = heightOfNode(root);
    temp -> height = heightOfNode(temp);
    return temp;
}

struct TreeNode* RRRotation(struct TreeNode* root){
    struct TreeNode* temp = root -> right;
    root -> right = temp -> left;
    temp -> left = root;
    root -> height = heightOfNode(root);
    temp -> height = heightOfNode(temp);
    return temp;
}

struct TreeNode* LRRotation(struct TreeNode* root){
    root -> left = RRRotation(root -> left);
    return LLRotation(root);
}

struct TreeNode* RLRotation(struct TreeNode* root){
    root -> right = LLRotation(root -> right);
    return RRRotation(root);
}

int isPresent(struct TreeNode* root, int val){
    if(root == NULL){
        return 0;
    }

    if(root -> val == val){
        return 1;
    }
    if(root -> val > val){
        return isPresent(root -> left, val);
    }
    else{
        return isPresent(root -> right, val);
    }
}

void printRootToNode(struct TreeNode* root, int val){
    if(root == NULL){
        return;
    }

    if(isPresent(root, val)){
        printf("%d ", root -> val);
        if(root -> val > val){
            printRootToNode(root -> left, val);
        }
        else{
            printRootToNode(root -> right, val);
        }
    }
    else{
        printf("Node not present in the tree\n");
    }
}

void AVLPreorder(struct TreeNode* root){
    if(root != NULL){
        printf("%d ", root -> val);
        AVLPreorder(root -> left);
        AVLPreorder(root -> right);
    }
}



struct TreeNode* insertIntoAVL(struct TreeNode* root, int val){
    if(root == NULL){
        return createNode(val);
    }

    if(root -> val > val){
        root -> left = insertIntoAVL(root->left, val);
    }

    else{
        root -> right = insertIntoAVL(root->right, val);
    }

    root -> height = heightOfNode(root);
    if(BalanceFactor(root) == 2 && BalanceFactor(root -> left) == 1){
        return LLRotation(root);
    }
    else if(BalanceFactor(root) == 2 && BalanceFactor(root -> left) == -1){
        return LRRotation(root);
    }
    else if(BalanceFactor(root) == -2 && BalanceFactor(root -> right) == -1){
        return RRRotation(root);
    }
    else if(BalanceFactor(root) == -2 && BalanceFactor(root -> right) == 1){
        return RLRotation(root);
    }
    
    return root;

}


int main() {
    struct TreeNode* root = NULL;

    char choice;
    while (1) {
        scanf(" %c", &choice);
        if (choice == 'e')
            break;

        switch (choice) {
            case 'i': {
                int key;
                scanf("%d", &key);
                root = insertIntoAVL(root, key);
                break;
            }
            case 'p': {
                AVLPreorder(root);
                break;
            }
            case 'x': {
                int key;
                scanf("%d", &key);
                printRootToNode(root, key);
                break;
            }
        }
    }

    return 0;
}
