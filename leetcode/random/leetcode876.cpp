class Solution {
public:
    ListNode* middleNode(ListNode* head) {
        auto fast = head;
        auto slow = head;
        while (fast!=nullptr && fast->next!=nullptr){
            fast=fast->next;
            slow=slow->next;
            if (fast==nullptr) return slow;
            fast=fast->next;
        }
        return slow;
    }
};
