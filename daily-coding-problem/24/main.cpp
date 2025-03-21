#include <iostream>

using namespace std;

struct TreeNode{
    int value;
    bool locked;
    TreeNode * left;
    TreeNode * right;
    TreeNode * parent;
    TreeNode(int value_, bool locked_=false,TreeNode * left_=nullptr, TreeNode* right_=nullptr, TreeNode * parent_=nullptr):
                value(value_),locked(locked_),left(left_),right(right_),parent(parent_){}

};

TreeNode * createTree(){
    auto one = new TreeNode(1);
    auto two = new TreeNode(2);
    auto three = new TreeNode(3);
    auto four = new TreeNode(4);
    auto five = new TreeNode(5);
    auto six = new TreeNode(6);
    auto seven = new TreeNode(7);
    one->left=two; one->right=three; 
    two->left=four; two->right=five; two->parent=one;
    three->left=six; three->right=seven; three->parent=one;
    four->parent=two; 
    five->parent=two;
    six->parent=three;
    seven->parent=three;
    return one;
}

void traverse(TreeNode * root){
    if (!root) return;
    cout<<"Value="<<root->value<<" ";
    cout<<"Locked="<<root->locked<<" ";
    if (root->parent) cout<<"Parent="<<root->parent->value;
    cout<<endl;
    traverse(root->left);
    traverse(root->right);
}

bool isParentLocked(TreeNode * node){
    if (!node) return false;
    auto parent=node->parent;
    while(parent ){
        if (parent->locked==true) return true;
        parent=parent->parent;
        
    }
    return false;
}

bool isChildrenLocked(TreeNode *node){
    if (!node) return false;
    if (node->left && node->left->locked) return true;
    if (node->right && node->right->locked) return true;
    if (isChildrenLocked(node->left)) return true;
    return isChildrenLocked(node->right);
}
bool isNodeParentAndChildrenLocked(TreeNode * node){
    if(!node) return false;
    bool ret=isParentLocked(node);
    if (ret) return true;
    return isChildrenLocked(node);
}

bool lock(TreeNode * node){
    if (!node) return false ;
    if (isNodeParentAndChildrenLocked(node)) return false;
    node->locked=true;
    return true;
}

bool unlock(TreeNode * node){
    if (!node) return false ;
    if (isNodeParentAndChildrenLocked(node)) return false;
    node->locked=false;
    return true;
}

int main(){
    auto root=createTree();
    traverse(root);
    cout<<lock(root->left)<<endl;
    traverse(root);
    cout<<lock(root)<<endl;
    traverse(root);
    cout<<unlock(root->left)<<endl;
    traverse(root);
    cout<<lock(root)<<endl;
    traverse(root);
    return 0;
}