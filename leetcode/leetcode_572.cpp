/*
572. Subtree of Another Tree

Given the roots of two binary trees root and subRoot, 
return true if there is a subtree of root with the same structure and node values of subRoot and false otherwise.
A subtree of a binary tree tree is a tree that consists of a node in tree and all of this node's descendants. 
The tree tree could also be considered as a subtree of itself.
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
    bool found{false};
    bool areTreesEqual(TreeNode * r1 , TreeNode * r2){
        if (!r1 && !r2) return true;
        if (!r1 && r2) return false;
        if (!r2 && r1) return false;
        if (r1->val!=r2->val) return false;
        return areTreesEqual(r1->left,r2->left) && 
               areTreesEqual(r1->right, r2->right); 
    }
    void traverse(TreeNode * root, TreeNode * subRoot){
        if (!root) return;
        if (root->val==subRoot->val) {
            if (areTreesEqual(root,subRoot))
            {
                found=true;
                return;
            }
        }
        if (found) return;
        traverse(root->left, subRoot);
        traverse(root->right, subRoot);
        
    }
public:
    bool isSubtree(TreeNode* root, TreeNode* subRoot) {
        traverse(root,subRoot);
        return found;
    }
};