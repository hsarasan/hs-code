/*
543. Diameter of Binary Tree

Given the root of a binary tree, return the length of the diameter of the tree.
The diameter of a binary tree is the length of the longest path between any two nodes in a tree. 
This path may or may not pass through the root.
The length of a path between two nodes is represented by the number of edges between them. 
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
    int max_left_most_slant=0;
    int max_right_most_slant;
    void traverse(TreeNode * node, int slant){
        if (!node) return;
        if (slant<0){
            max_left_most_slant=min(max_left_most_slant,slant);
        }
        else{
            max_right_most_slant=max(max_right_most_slant,slant);
        }
        traverse(node->left,slant-1);
        traverse(node->right,slant+1);
    }
public:
    int diameterOfBinaryTree(TreeNode* root) {
       traverse(root,0);
       return max_right_most_slant-max_left_most_slant; 
    }
};