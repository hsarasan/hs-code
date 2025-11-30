#include <cassert>
#include <utility>
#include <cstddef>


template <typename T, int Capacity = 10>
class Stack{

   public:
      Stack() = default;
	  ~Stack() = default;
	  Stack(const Stack&) = default;
      Stack& operator=(const Stack&) = default;
      Stack(Stack&&) noexcept = default;
      Stack& operator= (Stack&&) noexcept = default;
     
      void push(const T &elem) {
        assert(!full() && "Pushing to full stack");
        elems[++top_index] = elem;
      }
      void push(T&& elem) noexcept{
        assert(!full() && "Pushing to full stack");
        elems[++top_index] = std::move(elem);
      } 
      void pop()noexcept{
        assert(!empty() && "Popping empty stack");
        --top_index;
      }
      const T& top() const noexcept{
        assert(!empty() && "top of empty stack");
        return elems[top_index];
      }
      size_t size() const noexcept{
        return top_index + 1;
      }
			
      bool empty() const noexcept{
        return top_index == -1;
      }

      bool full() const noexcept{
        return top_index == Capacity - 1;
      }
   private:
      T elems[Capacity];
      int top_index{-1};
};

int main(){
    Stack<int> s;
    s.push(1);
    s.push(2);
    s.push(3);
    assert(s.size() == 3);
    assert(s.top() == 3);
    s.pop();
}