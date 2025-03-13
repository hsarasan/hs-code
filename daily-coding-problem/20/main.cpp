#include <iostream>


using namespace std;

struct Node{
    int value;
    Node * next;
    Node(int value_, Node * next_=nullptr):value(value_),next(next_){}
};

int getLength(Node * n){
    int len=0;
    while(n){
        len++;
        n=n->next;
    }
    return len;
}
void print(Node * n){
    cout<<"Len="<<getLength(n)<<endl;
    while(n){
        cout<<n->value<<"->";
        n=n->next;
    }
    cout<<endl;
    
}


int main(){
    Node * ten= new Node(10);
    Node * eight=new Node(8,ten);
    
    Node * one = new Node(1,eight);
    Node * two = new Node(2,one);
    Node * three= new Node(3,eight);
    Node * four=new Node(7,three);
    Node * five = new Node(5,four);
    
    int m=getLength(two);
    int n=getLength(five);
    
    auto m_ptr=two;
    auto n_ptr=five;
    int diff=abs(m-n);
    if (m>n){
        for (int i=0;i<diff;++i)
            m_ptr=m_ptr->next;
    }
    else if (m<n) {
        for (int i=0;i<diff;++i)
            n_ptr=n_ptr->next;
    }
    while(m_ptr!=n_ptr){
        m_ptr=m_ptr->next;
        n_ptr=n_ptr->next;
    }
    cout<<n_ptr->value<<endl;
    return 0;
}