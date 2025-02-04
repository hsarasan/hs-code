/*
111. Minimum Depth of Binary Tree
Given a binary tree, find its minimum depth.

The minimum depth is the number of nodes along the shortest path from the root node down to the nearest leaf node.

Note: A leaf is a node with no children.
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
    int min_depth=INT_MAX;
    void traverse(TreeNode * node, int level){
        if (!node) return ;
        if (!node->left && !node->right){
            min_depth=min(min_depth,level);
            return;
        }
        traverse(node->left,level+1);
        traverse(node->right,level+1);
    }
public:
    int minDepth(TreeNode* root) {
        if (!root) return 0;
        traverse(root,1);
        return min_depth;
    }
};