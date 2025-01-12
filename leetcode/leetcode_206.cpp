/*
206. Reverse Linked List
Given the head of a singly linked list, reverse the list, and return the reversed list.
*/
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        if (!head) return nullptr;
        ListNode * newhead = head;
        head=head->next;
        newhead->next=nullptr;
        while(head){
            ListNode * temp = newhead;
            newhead=head;
            head=head->next;
            newhead->next=temp;
        }
        return newhead;
        
    }
};