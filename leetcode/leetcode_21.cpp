/*
21. Merge Two Sorted Lists
You are given the heads of two sorted linked lists list1 and list2.

Merge the two lists into one sorted list. The list should be made by splicing together the nodes of the first two lists.

Return the head of the merged linked list.

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
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        if (!list1 && !list2) return nullptr;
        if (!list1) return list2;
        if (!list2) return list1;
        ListNode  * head = new ListNode(-100,list1);
        ListNode * runner = head;
        while (list1 && list2){
            if (list1->val<list2->val){
                runner->next=list1;
                runner=runner->next;
                list1=list1->next;
            }
            else{
                runner->next=list2;
                runner=runner->next;
                list2=list2->next;
            }
        }
        if (list1) runner->next=list1;
        else runner->next=list2;
        ListNode * temp = head;
        head=head->next;
        delete temp;
        return head;
    }
};