/*
257. Binary Tree Paths
Given the root of a binary tree, return all root-to-leaf paths in any order.
A leaf is a node with no children.
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
    vector<string> result;
    bool isLeafNode(TreeNode * node){
        return !node->left && !node->right;
    }
    void traverse(TreeNode * node, string path){
        if (!node) return;
        if (path==""){
            path=to_string(node->val);
        }
        else{
            path=path+"->"+to_string(node->val);
        }
        if (isLeafNode(node)){
            result.push_back(path);
        }
        else{
            traverse(node->left,path);
            traverse(node->right,path);
        }
    }
public:
    vector<string> binaryTreePaths(TreeNode* root) {
        if (!root) return {};
        traverse(root,"");
        return result;
    }
};