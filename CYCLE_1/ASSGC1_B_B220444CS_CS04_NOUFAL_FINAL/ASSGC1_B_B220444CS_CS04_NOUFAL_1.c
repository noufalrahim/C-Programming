#include <stdio.h>
#include <stdlib.h>

struct TreeNode {
    int val;
    struct TreeNode* left;
    struct TreeNode* right;
};

struct queue{
    struct TreeNode* node;
    struct queue* next;
};

struct queue* front = NULL;

struct queue* createNode(struct TreeNode* node){
    struct queue* newnode = (struct queue*)malloc(sizeof(struct queue));
    newnode -> node = node;
    newnode -> next = NULL;
    return newnode;
}

struct TreeNode* createTreeNode(char val) {
    struct TreeNode* newnode = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    newnode->val = val;
    newnode->left = NULL;
    newnode->right = NULL;
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

int search(int in[], int startIndex, int endIndex, int val) {
    int i;
    for (i = startIndex; i <= endIndex; i++) {
        if (in[i] == val)
            return i;
    }
    return -1;
}


struct TreeNode* buildTree(int in[], int pre[], int inStart, int inEnd) {
    static int preIndex = 0;
    if (inStart > inEnd) {
        return NULL;
    }

    struct TreeNode* root = createTreeNode(pre[preIndex++]);

    if (inStart == inEnd) {
        return root;
    }

    int InorderIndex = search(in, inStart, inEnd, root->val);

    root->left = buildTree(in, pre, inStart, InorderIndex - 1);
    root->right = buildTree(in, pre, InorderIndex + 1, inEnd);

    return root;
}

struct TreeNode* constructTree(int in[], int pre[], int inStart, int inEnd){
    if(inStart > inEnd){
        return NULL;
    }
    int preIndex = 0;
    struct TreeNode* root = createTreeNode(pre[preIndex++]);
    if(inStart == inEnd){
        return root;
    }

    int InorderIndex = search(in, inStart, inEnd, root -> val);

    root -> left = constructTree(in, pre, inStart, InorderIndex - 1);
    root -> right = constructTree(in, pre, InorderIndex + 1, inEnd);
    return root;
}



void postOrderTraversal(struct TreeNode* root) {
    if (root != NULL) {
        postOrderTraversal(root->left);
        postOrderTraversal(root->right);
        printf("%d ", root->val);
    }1
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



// int DiameterOfTree(struct TreeNode* root, int* maximum) {
//     if (root == NULL) {
//         return 0;
//     }

//     int leftHeight = DiameterOfTree(root->left, maximum);
//     int rightHeight = DiameterOfTree(root->right, maximum);

//     *maximum = (*maximum > (rightHeight + leftHeight + 1)) ? *maximum : (rightHeight + leftHeight + 1);

//     int total = ((leftHeight > rightHeight) ? leftHeight : rightHeight);
//     return total + 1;
// }

int height(struct TreeNode* root, int *maximum){
  if(root == NULL){
    return 0;
  }
  int leftH = height(root -> left, maximum);
  int rightH = height(root -> right, maximum);
  
  if(*maximum < (leftH + rightH + 1)){
    *maximum = leftH + rightH + 1;
  }
  
  if(leftH > rightH){
    return leftH + 1;
  }
  else{
    return rightH + 1;
  }
}


int DiameterOfTree(struct TreeNode* root){
  if(root == NULL){
    return 0;
  }
  
  int diam = 0;
  height(root, &diam);
  return diam;
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

// int leftLeavesSum(struct TreeNode* root){
//     if(root == NULL){
//         return 0;
//     }
//     int sum = 0;
//     if(isLeftLeafNode(root)){
//         sum = sum + root -> left -> val;
//     } 

//     sum += leftLeavesSum(root -> left);
//     sum += leftLeavesSum(root -> right);

//     return sum; 
// }

int leftLeavesSum(struct TreeNode* root){
    if(root == NULL){
        return 0;
    }
    int sum = 0;

    if(isLeftLeafNode(root)){
        sum += root -> left -> val;
    }++

    sum += leftLeavesSum(root -> left);
    sum += leftLeavesSum(root -> right);
    return sum;
}



int main() {
    int treeLength;
    scanf("%d", &treeLength);

    int in[100];
    int pre[100];

    for (int i = 0; i < treeLength; i++) {
        scanf("%d", &in[i]);
    }
    
    for (int i = 0; i < treeLength; i++) {
        scanf("%d", &pre[i]);
    }

 
    struct TreeNode* root = buildTree(in, pre, 0, treeLength - 1);

    char choice;

    while (1) {
        scanf(" %c", &choice);
        if (choice == 'e') {
            break;
        } else if (choice == 'p') {
            postOrderTraversal(root);
            printf("\n");
        } else if (choice == 'z') {
            zigZagTraversal(root);
            printf("\n");
        } else if (choice == 'm') {
            LevelMax(root);
            printf("\n");
        } else if (choice == 'd') {
            printf("%d\n", DiameterOfTree(root));
        } else if (choice == 's') {
            printf("%d\n", leftLeavesSum(root));
        }
    }
    return 0;
}
