/*
112. Path Sum
Solved
Easy
Topics
Companies
Given the root of a binary tree and an integer targetSum, 
return true if the tree has a root-to-leaf path such that adding up all the values along the path equals targetSum.
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
    bool isLeafNode(TreeNode * root){
        return !root->left && !root->right;
    }
    bool found{false};
    void traverse(TreeNode* node, int targetSum, int sumSoFar){
        if (!node || found) return ;
        sumSoFar=sumSoFar+node->val;
        if (isLeafNode(node)){
            if (sumSoFar==targetSum){
                found=true;
            }
        }
        else{
            traverse(node->left,targetSum,sumSoFar);
            traverse(node->right,targetSum,sumSoFar);
        }
    }
public:
    bool hasPathSum(TreeNode* root, int targetSum) {
        traverse(root,targetSum,0);   
        return found;   
    }
};