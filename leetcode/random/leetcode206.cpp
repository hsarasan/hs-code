//vector based solution

class Solution {
    
public:
    ListNode* reverseList(ListNode* head) {
        if (head==nullptr) return head;
        if (head->next == nullptr) return head;
        std::vector<ListNode *> v;
        while(head){
            v.push_back(head);
            head=head->next;
        }
        ListNode * prev=nullptr;
        head=v[v.size()-1];
        std::for_each(v.rbegin(), v.rend(), [&](ListNode *n){
            if(prev) prev->next=n;
            n->next=nullptr;
            prev=n;
        }
        );
        return head;;
    }
};

////////////////recursive solution
class Solution {
    ListNode * reverse(ListNode *head){
        auto node=head;
        if (!node) return node;
        if (!node->next) return node;
        if (!node->next->next){
            node->next->next=node;
            node=node->next;
            node->next->next=nullptr;
            return node;  
        }
        auto temp_head=head->next;
        temp_head=reverse(temp_head);
        auto tail=temp_head;
        while(tail->next) tail=tail->next;
        tail->next=head;
        head->next=nullptr;
        head=temp_head;
        return head;
    }
public:
    ListNode* reverseList(ListNode* head) {
        return reverse(head);
    }
};
