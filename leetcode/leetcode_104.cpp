/*
104. Maximum Depth of Binary Tree
Given the root of a binary tree, return its maximum depth.

A binary tree's maximum depth is the number of nodes along the longest path 
from the root node down to the farthest leaf node.
*/

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
    int max_depth=0;
    bool isLeafNode(TreeNode * node){
        return !node->left && !node->right;
    }
    void traverse(TreeNode * node, int depth){
        if (!node) return ;
        if (isLeafNode(node)){
            max_depth=max(max_depth,depth);
        }
        else{
            traverse(node->left, depth+1);
            traverse(node->right, depth+1);
        }
    }
public:
    int maxDepth(TreeNode* root) {
        if (!root){
            return 0;
        }
        traverse(root,1);
        return max_depth;
    }
    
};