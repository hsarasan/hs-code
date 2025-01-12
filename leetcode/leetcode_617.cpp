/*
617. Merge Two Binary Trees
You are given two binary trees root1 and root2.
Imagine that when you put one of them to cover the other, some nodes of the two trees are overlapped while the others are not. You need to merge the two trees into a new binary tree. The merge rule is that if two nodes overlap, then sum node values up as the new value of the merged node. 
Otherwise, the NOT null node will be used as the node of the new tree.
Return the merged tree.
*/

class Solution {

    TreeNode * traverse(TreeNode* l, TreeNode * r){
        if (!l && !r) {
            return nullptr;
        }
        if (!l && r){
            return r;
        }
        if (!r && l){
            return l;
        }

        TreeNode * node = new TreeNode(l->val+r->val);
        node->left=traverse(l->left, r->left);
        node->right=traverse(l->right, r->right);
        return node;
    }

public:
    TreeNode* mergeTrees(TreeNode* root1, TreeNode* root2) {
        TreeNode * root;
        if (!root1 && !root) return nullptr;
        if (!root1) return root2;
        if (!root2) return root1;
        root=traverse(root1,root2);
        return root;
    }
};