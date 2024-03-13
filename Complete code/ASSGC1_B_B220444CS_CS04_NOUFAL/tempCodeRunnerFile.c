int DiameterOfTree(struct TreeNode* root, int maximum){
    if(root == NULL){
        return 0;
    }

    int leftHeight = DiameterOfTree(root -> left, maximum);
    int rightHeight = DiameterOfTree(root -> right, maximum);

    maximum = maximum > (rightHeight + leftHeight) ? maximum : (rightHeight + leftHeight);

    return 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
}
