#include <iostream>

using namespace std;

struct Node{
    int val;
    uintptr_t addr;
    Node(int val_, uintptr_t prev, uintptr_t next){
        val=val_;
        addr=prev^next;
    }
    uintptr_t getNext(uintptr_t v){
        return addr^v;
    }
};

struct LinkedList{
    Node * head{nullptr};
    Node * tail{nullptr};

    void add(int value) {
        if (!head) {
            head = new Node(value, reinterpret_cast<uintptr_t>(nullptr), reinterpret_cast<uintptr_t>(nullptr));
            tail = head;
        } else {
            auto n = new Node(value, reinterpret_cast<uintptr_t>(tail), reinterpret_cast<uintptr_t>(nullptr));
            tail->addr ^= reinterpret_cast<uintptr_t>(n);  // Update tail's XOR with the new node's address
            tail = n;  // Move tail to the new node
        }
    }
    void print() {
        Node* n = head;
        uintptr_t prev = reinterpret_cast<uintptr_t>(nullptr);  // No previous node for the head
        while (n) {
            cout << n->val << " ";
            uintptr_t next = n->getNext(prev);  // Get the next node
            prev = reinterpret_cast<uintptr_t>(n);
            n = reinterpret_cast<Node*>(next);  // Move to the next node
        }
    }
    Node * get(int index){
        Node* n = head;
        uintptr_t prev = reinterpret_cast<uintptr_t>(nullptr);  // No previous node for the head
        int i=1;
        while(i<index){
            uintptr_t next = n->getNext(prev);  // Get the next node
            prev = reinterpret_cast<uintptr_t>(n);
            n = reinterpret_cast<Node*>(next);  // Move to the next node
            i++;
        }
        return n;
    }
    
};

int main(){
    LinkedList l;
    l.add(1);
    l.add(2);
    l.add(3);
    l.print();
    auto n=l.get(2);
    cout<<n->val<<endl;
}