/*
Given the root of a binary tree, invert the tree, and return its root.
*/

class Solution {
    void inverter(TreeNode *root){
        if(!root) return;
        if (!root->left && !root->right) return;
        std::swap(root->left, root->right);
        if (root->left) inverter(root->left);
        if (root->right) inverter(root->right);
    
    }
public:
    TreeNode* invertTree(TreeNode* root) {
        inverter(root);
        return root;    
    }
};