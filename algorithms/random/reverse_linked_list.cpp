#include <iostream>
#include <vector>

using namespace std;
struct Node{
    int value;
    Node * next;
    Node(int v){
        value=v;
        next=nullptr;
    }
};

Node * createLinkedList(const vector<int> &vec){
    if (vec.size()==0) return nullptr;
    Node * head{nullptr};
    Node * tail{nullptr};
    for (const auto  value: vec){
        auto ptr = new Node(value);
        if (!head) head=ptr;
        if (tail) tail->next=ptr;
        tail = ptr;
    }
    return head;
}

/*
Logic to reverse :
1->2->3->4->5->null;
1->null; 2->3->4->5->null;
2->1->null; 3->4->5->null;
3->2->1->null; 4->5->null;
4->3->2->1->null; 5->null;
5->4->3->2->1->null;
*/
Node * reverseLinkedList(Node* head){
    Node * current_head  = head;
    Node * reversed_head = nullptr;
    while(current_head){
        auto temp = current_head;
        current_head = current_head->next;
        temp->next = reversed_head;
        reversed_head = temp;
        
    }
    return reversed_head;
}

void printLinkedList(Node * head){
    while(head){
        cout<<head->value<<",";
        head=head->next;
    }
    cout<<endl;
}

int main(){
    auto ptr = createLinkedList({1,2,3,4,5});
    printLinkedList(ptr);
    ptr=reverseLinkedList(ptr);
    printLinkedList(ptr);

    ptr = createLinkedList({});
    printLinkedList(ptr);
    ptr=reverseLinkedList(ptr);
    printLinkedList(ptr);

    ptr = createLinkedList({4});
    printLinkedList(ptr);
    ptr=reverseLinkedList(ptr);
    printLinkedList(ptr);
    return 0;
}