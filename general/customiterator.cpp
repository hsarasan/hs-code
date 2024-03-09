#include <iostream>
#include <iterator>
#include <algorithm>

/*
    Implementation of a sample iterator for a LinkedList based LinkedList

*/

class LinkedList
{
    struct Node
    {
        int value;
        Node *next;
        Node(int value) : value(value), next(nullptr) {}
    };
    Node *head;
    int size{0};

public:
    void push(int value_)
    {
        Node *newNode = new Node(value_);
        if (size > 0)
        {
            newNode->next = head;
            head = newNode;
        }
        else
        {
            head = newNode;
        }
        size++;
    }
    int pop()
    {
        if (size > 0)
        {
            int ret = head->value;
            head = head->next;
            size--;
            return ret;
        }
        return -1;
    }
    struct Iterator
    {
        using iterator_category = std::forward_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = int;
        using pointer = int *;
        using reference = int &;

        Iterator() { m_ptr=nullptr; n_ptr=nullptr;}
        Iterator(Node* ptr){
            n_ptr=ptr;
            m_ptr=&n_ptr->value;
        }
        reference operator*() const { return *m_ptr; }
        pointer operator->() { return m_ptr; }
        Iterator &operator++()
        {
            n_ptr=n_ptr->next;
            m_ptr=&n_ptr->value;
            return *this;
        }
        Iterator operator++(int)
        {
            Iterator tmp = *this;
            n_ptr=n_ptr->next;
            m_ptr=&n_ptr->value;
            return tmp;
        }

        friend bool operator==(const Iterator &a, const Iterator &b) { return a.m_ptr == b.m_ptr; };
        friend bool operator!=(const Iterator &a, const Iterator &b) { return a.m_ptr != b.m_ptr; };

    private:
        pointer m_ptr;
        Node * n_ptr;
    };

    Iterator begin() { return Iterator(head);}
    Iterator end()   { return Iterator(nullptr); }
};

int main()
{
    LinkedList st;
    st.push(12);
    st.push(21);
    st.push(13);
    LinkedList::Iterator it;
    for (const auto x: st){
        std::cout<<x<<std::endl;
    } 
    std::copy(st.begin(), st.end(), std::ostream_iterator<int>(std::cout,","));
    std::cout<<std::endl;
    std::for_each(st.begin(), st.end(), [](int &x) {x++;});
    std::copy(st.begin(), st.end(), std::ostream_iterator<int>(std::cout,","));
    std::cout<<std::endl;
    return 0;
}