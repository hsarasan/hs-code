/*
637. Average of Levels in Binary Tree
Given the root of a binary tree, return the average value of the nodes on each level in the form of an array. 
Answers within 10-5 of the actual answer will be accepted.

*/

class Solution {
    vector<int> level_count;
    vector<int> level_sum;
    void traverse(TreeNode * node, int level){
        if (!node) return;
        if (level_sum.size()<level){
            level_sum.push_back(node->val);
            level_count.push_back(1);
        }
        else{
            level_sum[level-1]+=node->val;
            level_count[level-1]++;
        }
        traverse(node->left,level+1);
        traverse(node->right,level+1);
    }
public:
    vector<double> averageOfLevels(TreeNode* root) {
        traverse(root,1);
        vector<double> result(level_count.size(),0);
        for ( int i=0;i<level_count.size();++i){
            result[i]=(double)level_sum[i]/level_count[i];
        }
        return result;
    }
};