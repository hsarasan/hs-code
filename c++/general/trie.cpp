#include <iostream>
#include <unordered_map>
#include <vector>
#include <memory>
#include <queue>
#include <ranges>
#include <algorithm>

enum NodeType
{
    Leaf,
    NonLeaf
};
struct Node
{
    NodeType type;
    std::unordered_map<char, std::unique_ptr<Node>> m;
    std::string completeWord;
    Node(NodeType t) : type(t)
    {
    }
    void addCompletedWord(const std::string s)
    {
        if (type == NodeType::Leaf)
        {
            completeWord = s;
        }
    }
    void print()
    {
        std::cout << "Type=" << type;
        if (type == NodeType::Leaf)
        {
            std::cout << " Completed Word=" << completeWord << std::endl;
        }
        else
        {
            for (const auto &[k, v] : m)
            {
                std::cout << " " << k << " ";
            }
        }
        std::cout << std::endl;
    }
};

class Trie
{
    std::unique_ptr<Node> root;
    void addWordHelper(Node *n, const std::string &s, int pos)
    {
        char Character = s[pos];
        if (pos == s.length() - 1)
        {
            n->m[Character] = std::make_unique<Node>(NodeType::Leaf);
            n->m[Character]->addCompletedWord(s);
        }
        else
        {
            if (n->m.count(Character) == 0)
            {
                n->m[Character] = std::make_unique<Node>(NodeType::NonLeaf);
            }
            addWordHelper(n->m[Character].get(), s, ++pos);
        }
    }
    void searchNode(Node *n, std::vector<std::string> &fullWords)
    {
        std::queue<Node *> Q;
        if (n)
        {
            if (n->type == NodeType::NonLeaf)
            {
                for (const auto &[k, v] : n->m)
                {
                    Q.push(v.get());
                }
            }
            else
            {
                fullWords.push_back(n->completeWord);
            }
        }
        while (!Q.empty())
        {
            auto n_next = Q.front();
            Q.pop();
            searchNode(n_next, fullWords);
        }
    }
    void printNode(Node *n)
    {
        std::queue<Node *> Q;
        if (n)
        {
            n->print();
            for (const auto &[k, v] : n->m)
            {
                Q.push(v.get());
            }
        }
        while (!Q.empty())
        {
            auto n = Q.front();
            printNode(n);
            Q.pop();
        }
    }

public:
    Trie()
    {
        root = std::make_unique<Node>(NodeType::NonLeaf);
    }
    void addWord(const std::string &s)
    {
        char Character = s[0];
        if (root->m.count(Character) == 0)
        {
            root->m[Character] = std::make_unique<Node>(NodeType::NonLeaf);
        }
        addWordHelper(root->m[Character].get(), s, 1);
    }
    std::vector<std::string> search(std::string input)
    {

        std::vector<std::string> v;
        auto node = root.get();
        for (const auto ch : input)
        {
            node = node->m[ch].get();
            if (!node)
                return v;
        }
        searchNode(node, v);
        std::ranges::copy(v, std::ostream_iterator<std::string>(std::cout, " "));
        std::cout << std::endl;
        return v;
    }
    void printTrie()
    {
        printNode(root.get());
    }
};

int main()
{
    Trie trie;
    trie.addWord("abc");
    trie.addWord("abd");
    trie.addWord("fgh");
    trie.printTrie();
    trie.search("ab");
    trie.search("f");
    trie.search("abc");
    trie.search("abcde");
}