class Solution {

    void traverse(TreeNode * node, int & level , bool & result){
        if (!node || !result) return;
        level++;
        int r_level=level;
        int l_level=level;
        
        if (node->left) traverse(node->left,l_level,result);
        if (node->right) traverse(node->right,r_level,result);
        result = result & (std::abs(l_level-r_level)<=1);
        level=std::max(l_level, r_level);
    }
public:
    bool isBalanced(TreeNode* root) {
        int level=0;
        bool result{true};
        traverse(root,level, result);
        return result;
    }
};