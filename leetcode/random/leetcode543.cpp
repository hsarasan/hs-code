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
