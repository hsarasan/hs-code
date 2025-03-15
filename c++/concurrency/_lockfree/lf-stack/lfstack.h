#ifndef _LFSTACK_H
#define _LFSTACK_H

#include <thread>
#include <atomic>
#include <optional>

namespace HS{

template <typename T>
class LFStack{
    private:
        struct Node{
            T value;
            Node * next;
            Node(T _val, Node* _next=nullptr):value(_val),next(_next){}
        };
        std::atomic<Node*> head{nullptr};

    public:
        void push(const T& obj){
            Node * node = new Node(obj);
            node->next=head.load(std::memory_order_acquire);
            while(!head.compare_exchange_weak(node->next,node,
                    std::memory_order_release,std::memory_order_relaxed)){}
        }
        std::optional<T> pop(){
            Node * old_head = head.load(std::memory_order_acquire);
            if (old_head==nullptr){
                return std::nullopt;
            }
            while(!head.compare_exchange_weak(old_head,old_head->next,
                                            std::memory_order_release,std::memory_order_relaxed)){}
            T obj=old_head->value;
            delete old_head;
            return obj;
        }
        ~LFStack() {
            // Cleanup remaining nodes during stack destruction (in case of stack object destruction)
            while (head.load() != nullptr) {
                Node* old_head = head.load();
                if (head.compare_exchange_weak(old_head, old_head->next,
                                               std::memory_order_release, std::memory_order_relaxed)) {
                    delete old_head; // Safely deallocate nodes
                }
            }
        }

};

};
#endif