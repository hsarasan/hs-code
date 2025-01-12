/*
226. Invert Binary Tree
Given the root of a binary tree, invert the tree, and return its root.
*/
class Solution {

public:
    TreeNode* invertTree(TreeNode* root) {
        if (!root) return nullptr;
        if (!root->left && !root->right) 
            return root;
        root->left=invertTree(root->left);
        root->right=invertTree(root->right);
        swap(root->left, root->right);
        return root; 
    }
};