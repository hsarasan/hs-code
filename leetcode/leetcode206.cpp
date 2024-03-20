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
