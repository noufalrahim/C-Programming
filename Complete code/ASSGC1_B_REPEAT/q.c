#include <stdio.h>
#include <stdlib.h>
struct queue{
    struct TreeNode* node;
    struct queue* next;
};

struct TreeNode{
    int val;
    struct TreeNode* left;
    struct TreeNode* right;
};

struct queue* front = NULL;

struct queue* createNode(struct TreeNode* node){
    struct queue* newnode = (struct queue*)malloc(sizeof(struct queue));
    newnode -> node = node;
    newnode -> next = NULL;
    return newnode;
}

struct queue* push(struct TreeNode* node){
    struct queue* q = createNode(node);
    struct queue* temp = front;
    if(temp == NULL){
        front = q;
        return front;
    }
    while (temp -> next != NULL)
    {
        temp = temp -> next;
    }
    temp -> next = q;
    return front;
}

struct TreeNode* pop(){
    struct queue* temp = front;
    if(front == NULL){
        return NULL;
    }
    struct queue* newFront = front -> next;
    front = newFront;
    return temp -> node;
}

int isEmpty(){
    if(front == NULL){
        return 1;
    }
    return 0;
}

int totalNodes() {
    int count = 0;
    struct queue* temp = front;
    while (temp != NULL) {
        count++;
        temp = temp->next;
    }
    return count;
}
void LevelOrderTraversal(struct TreeNode* root){
    front = push(root);
    while(!isEmpty()){
        int count = totalNodes();
        int *arr = (int *)malloc(count * sizeof(int));
        for(int i=0; i<count; i++){
            struct TreeNode* currentNode = pop();
            arr[i] = currentNode -> val;
            if(currentNode -> left != NULL){
                push(currentNode -> left);
            }
            if(currentNode -> right != NULL){
                push(currentNode -> right);
            }
        }

        for(int i=0; i<count; i++){
            printf("%d ", arr[i]);
        }
    }

    front = NULL;
}

void zigZagTraversal(struct TreeNode* root){
    front = push(root);
    int leftToRight = 1;
    while (!isEmpty())
    {
        int count = totalNodes();
        int *arr = (int *)malloc(count * sizeof(int));
        for(int i=0; i<count; i++){
            struct TreeNode* currentNode = pop();
            int index = leftToRight ? i : count - i - 1;
            arr[index] = currentNode -> val;
            if(currentNode -> left != NULL){
                push(currentNode -> left);
            }
            if(currentNode -> right != NULL){
                push(currentNode -> right);
            }

        }

        for(int i=0; i<count; i++){
            printf("%d ", arr[i]);
        }

        free(arr);
        leftToRight = 1 - leftToRight;
    }
    
    front = NULL;
}

int rightView(struct TreeNode* root){
    front = push(root);
    while(!isEmpty()){
        int count = totalNodes();
        int *arr = (int *)malloc(count * sizeof(int));
        for(int i=0; i<count; i++){
            struct TreeNode* currentNode = pop();
            arr[i] = currentNode -> val;
            if(currentNode -> left != NULL){
                push(currentNode -> left);
            }
            if(currentNode -> right != NULL){
                push(currentNode -> right);
            }
        }
        printf("%d ", arr[count - 1]);
    }

    front = NULL;
}


int DiameterOfTree(struct TreeNode* root, int maximum){
    if(root == NULL){
        return 0;
    }

    int leftHeight = DiameterOfTree(root -> left, maximum);
    int rightHeight = DiameterOfTree(root -> right, maximum);

    maximum = maximum > (rightHeight + leftHeight) ? maximum : (rightHeight + leftHeight);

    return 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
}



int isLeftLeafNode(struct TreeNode* root){
    if(root == NULL){
        return 0;
    }
    if(root -> left != NULL && root -> left -> left == NULL && root -> left -> right == NULL){
        return 1;
    }
    return 0;

}

int leftLeavesSum(struct TreeNode* root){
    if(root == NULL){
        return 0;
    }
    int sum = 0;
    if(isLeftLeafNode(root)){
        sum = sum + root -> left -> val;
    }

    sum += leftLeavesSum(root -> left);
    sum += leftLeavesSum(root -> right);

    return sum; 
}

void LevelMax(struct TreeNode* root){
    front = push(root);
    while (!isEmpty())
    {
        int count = totalNodes();
        int *arr = (int *)malloc(count*sizeof(int));
        int max = 0;
        for(int i=0; i<count; i++){
            struct TreeNode* currentNode = pop();
            if(currentNode -> val > max){
                max = currentNode -> val;
            }

            if(currentNode -> left != NULL){
                push(currentNode -> left);
            }
            if(currentNode -> right != NULL){
                push(currentNode -> right);
            }

        }

        printf("%d ", max);
    }

    front = NULL;
    
}

struct Result {
    int maxSum;
    int sum;
    int min;
    int max;
    int isBST;
};

struct Result maxSumBST(struct TreeNode* root) {
    if (root == NULL) {
        struct Result result = {0, 0, 1000, -1000, 1};
        return result;
    }

    struct Result left = maxSumBST(root->left);
    struct Result right = maxSumBST(root->right);

    if (left.isBST && right.isBST && root->val > left.max && root->val < right.min) {
        int sum = left.sum + right.sum + root->val;
        int minVal = (root->left != NULL) ? left.min : root->val;
        int maxVal = (root->right != NULL) ? right.max : root->val;

        struct Result result = {sum, sum, minVal, maxVal, 1};
        return result;
    } else {
        int maxSum = (left.maxSum > right.maxSum) ? left.maxSum : right.maxSum;
        struct Result result = {maxSum, 0, 0, 0, 0};
        return result;
    }
}


int MaximumSumBst(struct TreeNode* root) {
    struct Result result = maxSumBST(root);
    return result.maxSum;
}




int main() {
    struct TreeNode* root = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    root->val = 4;
    
    root->left = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    root->left->val = 2;
    root->left->left = NULL;
    root->left->right = NULL;

    root->right = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    root->right->val = 5;
    root->right->left = NULL;
    root->right->right = NULL;

    root->left->left = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    root->left->left->val = 1;
    root->left->left->left = NULL;
    root->left->left->right = NULL;

    root->left->right = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    root->left->right->val = 3;
    root->left->right->left = NULL;
    root->left->right->right = NULL;

    int maximum = 0;
    zigZagTraversal(root);
    printf("\n");
    LevelOrderTraversal(root);
    printf("\n");
    rightView(root);
    printf("\n");
    printf("%d ", leftLeavesSum(root));
    printf("\n");
    LevelMax(root);
    printf("\n");
    printf("%d ", MaximumSumBst(root));
    printf("\n");
    printf("%d ",DiameterOfTree(root, maximum));

    free(root->left->left);
    free(root->left->right);
    free(root->left);
    free(root->right);
    free(root);

    return 0;
}