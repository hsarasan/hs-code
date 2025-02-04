class Solution {
    
    void findMaxDepth(TreeNode * node, int &depth){
        if(!node) return;
        depth++;
        int l_depth{0};
        int r_depth{0};
        if (node->left) findMaxDepth(node->left, l_depth);
        if (node->right) findMaxDepth(node->right, r_depth);
        depth=depth+std::max(l_depth, r_depth);
        
    }
public:
    int maxDepth(TreeNode* root) {
        int depth{0};
        findMaxDepth(root,depth);
        return depth;
    }
};
