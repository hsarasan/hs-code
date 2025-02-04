class MyQueue {
    std::stack<int> St1;
    std::stack<int> St2;
public:
    MyQueue() {
        
    }
    
    void push(int x) {
        while (!St1.empty()){
            St2.push(St1.top());
            St1.pop();
        }
        St1.push(x);
        while (!St2.empty()){
            St1.push(St2.top());
            St2.pop();
        }
    }
    
    int pop() {
        auto x = St1.top();
        St1.pop();
        return x;
    }
    
    int peek() {
        return St1.top();
    }
    
    bool empty() {
        return St1.empty();
    }
};