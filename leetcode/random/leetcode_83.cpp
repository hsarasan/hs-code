/*
83. Remove Duplicates from Sorted List
Given the head of a sorted linked list, 
delete all duplicates such that each element appears only once. Return the linked list sorted as well.
*/

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        if(!head) return nullptr;
        ListNode * original_head = head;
        ListNode * prev = head;
        head=head->next;

        while(head){
            if (head->val==prev->val){
                ListNode * temp = head;
                head=head->next;
                prev->next=head;
                delete temp;
            }
            else{
                prev=prev->next;
                head=head->next;
            }
        }
        return original_head;
    }
};