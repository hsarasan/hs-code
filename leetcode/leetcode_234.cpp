/*
234. Palindrome Linked List
Given the head of a singly linked list, return true if it is a 
palindrome or false otherwise.

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
    ListNode * split(ListNode * head){
        ListNode * fast = head;
        ListNode * slow = head;
        while (fast){
            
            fast=fast->next;
            if (!fast){
                ListNode * prev=slow;
                slow=slow->next;
                prev->next=nullptr;
                break;
            }
            else{
                fast=fast->next;
                if (!fast){
                    ListNode * prev = slow;
                    slow=slow->next;
                    prev->next=nullptr;
                    break;
                }
                slow=slow->next;
            }
        }
        return slow;
    }
    void print(ListNode * head){
        while(head){
            cout<<head->val<<" ";
            head=head->next;
        }
        cout<<endl;
    }
    ListNode * reverse(ListNode * head){
        if (!head) return nullptr;
        ListNode * new_head=head;
        head=head->next;
        new_head->next=nullptr;
        while(head){
            ListNode * temp = new_head;
            new_head = head;
            head=head->next;
            new_head->next=temp;
        }
        return new_head;
    }

    bool isSame(ListNode * head1 , ListNode * head2){
        if (!head1 || !head2) return true;
        while (head1&&head2){
            if (head1->val!=head2->val) return false;
            head1=head1->next;
            head2=head2->next;
        }
        return true;
    }

public:
    bool isPalindrome(ListNode* head) {
        ListNode * middle = split(head);
        middle=reverse(middle);
        return isSame(head,middle);      
    }
};