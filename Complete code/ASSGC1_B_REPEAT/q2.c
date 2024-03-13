#include<stdio.h>
#include<stdlib.h>

struct queue{
    struct TreeNode* node;
    struct queue* next;
};

struct TreeNode{
    int val;
    struct TreeNode* left;
    struct TreeNode* right;
};

struct Result {
    int maxSum;
    int sum;
    int min;
    int max;
    int isBST;
};

struct queue* front = NULL;

struct queue* createNode(struct TreeNode* node){
    struct queue* newnode = (struct queue*)malloc(sizeof(struct queue));
    newnode -> node = node;
    newnode -> next = NULL;
    return newnode;
}

struct TreeNode* createTreeNode(int val) {
    struct TreeNode* newNode = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    newNode->val = val;
    newNode->left = newNode->right = NULL;
    return newNode;
}

struct TreeNode* convertToTree(char exp[], int* index) {
    struct TreeNode* root = NULL;

    if (exp[*index] == '\0' || exp[*index] == ')') {
        (*index)++;
        return NULL;
    }

    
    root = createTreeNode(exp[*index] - '0');

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


int main() {
    char exp[100];
    scanf("%s ", exp);
    int index = 0;
    struct TreeNode* root = convertToTree(exp, &index);

    char choice;
    while (1) {
        scanf(" %c", &choice);

        switch (choice) {
            case 'l':
                LevelOrderTraversal(root);
                printf("\n");
                break;
            case 'r':
                rightView(root);
                printf("\n");
                break;
            case 'm':
                printf("%d\n", MaximumSumBst(root));
                break;
            case 'e':
                exit(0);
        }
    }

    return 0;
}