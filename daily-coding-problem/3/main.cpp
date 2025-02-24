#include <string>
#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>
#include <iterator>

using namespace std;

struct TreeNode{
    string str;
    TreeNode * left;
    TreeNode * right;
    TreeNode(const string x): str(x), left(NULL), right(NULL) {}
    TreeNode(const string x, TreeNode * l, TreeNode * r): str(x), left(l), right(r) {}  
};

string serialize(TreeNode * root){
    if (!root) return "$$";
    return root->str + "," + serialize(root->left) + "," + serialize(root->right);
}

TreeNode* deserializeHelper(vector<string>& nodes, int& index) {
    if (index >= nodes.size() || nodes[index] == "$$") {
        index++;  // Move past the null marker
        return nullptr;
    }

    TreeNode* root = new TreeNode(nodes[index++]);
    root->left = deserializeHelper(nodes, index);
    root->right = deserializeHelper(nodes, index);
    return root;
}

// Deserialize from a vector of strings
TreeNode* deserialize(vector<string> nodes) {
    int index = 0;
    return deserializeHelper(nodes, index);
}

TreeNode * deserialize(string  data){
    vector<string> nodes;
    string node;
    size_t pos=0;
    while (pos != string::npos){
        auto pos2=data.find(",",pos);
        string node;

        if (pos2!=string::npos){
            node=data.substr(pos,pos2-pos);
            pos=pos2+1;
        }
        else{
            node=data.substr(pos);
            pos=pos2;
        }
        nodes.push_back(node);
    }
    return deserialize(nodes);
}

int main(){
    TreeNode * root = new TreeNode("root",new TreeNode("left",new TreeNode("left.left"),nullptr),new TreeNode("right"));
    cout<<serialize(root)<<endl;
    auto root2 = deserialize(serialize(root));
    cout<<serialize(root2)<<endl;
    assert(serialize(root)==serialize(root2));
}