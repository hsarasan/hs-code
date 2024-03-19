class Solution {
public:
    bool hasCycle(ListNode *head) {
        auto fast=head;
        auto slow=head;
        if (!head || !head->next) return false;
        while( fast && fast->next){
            slow=slow->next;
            fast=fast->next;
            if (fast && fast->next!=nullptr){
                fast=fast->next;
            }
            else{
                return false;
            }
            if (fast==slow) return true;;
        }
        
        return false;
    }
};