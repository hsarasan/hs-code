/*
203. Remove Linked List Elements
Given the head of a linked list and an integer val, 
remove all the nodes of the linked list that has Node.val == val, and return the new head.
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
    ListNode* removeElements(ListNode* head, int val) {
        ListNode * sentinel_head = new ListNode(0,head);
        ListNode * prev = sentinel_head;
        while (head){
            if (head->val==val){
                prev->next=head->next;
                delete head;
                head=prev->next;
            }
            else{
                head=head->next;
                prev=prev->next;
            }
        }
        head=sentinel_head->next;
        delete sentinel_head;
        return head;
    }
};