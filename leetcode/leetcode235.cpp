/*
Given a binary search tree (BST), find the lowest common ancestor (LCA) node of two given nodes in the BST.

According to the definition of LCA on Wikipedia: “The lowest common ancestor is defined between two nodes p and q as the lowest node in T that has both p and q as descendants (where we allow a node to be a descendant of itself).”
*/


class Solution {
    std::queue<TreeNode *> pQ;
    std::queue<TreeNode *> qQ;
public:
    void traverse(TreeNode  * n, int target, std::queue<TreeNode *> &Q){
        if (!n) return;
        Q.push(n);
        if (n->val==target) return;
        if ( n->val > target){
            traverse(n->left, target, Q);
        }
        else {
            traverse(n->right, target, Q);
        }

    }
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        traverse(root,p->val, pQ);
        traverse(root,q->val, qQ);
        auto lca=root;
        while( !pQ.empty() && !qQ.empty() && pQ.front() == qQ.front() ){
            lca=pQ.front();
            pQ.pop();
            qQ.pop();
        }
        return lca;
    }
};