#include <iostream>
#include <memory>

using namespace std;

template <typename T, typename... Args>
unique_ptr<T> my_make_unique(Args&&... args){
    return unique_ptr<T>(new T(std::forward<Args>(args)...));
}


struct Point {
    int x, y;
    Point(int a, int b) : x(a), y(b) {}
};

int main() {
    auto p = my_make_unique<Point>(3, 4);
}
