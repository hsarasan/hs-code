#include <iostream>
#include <unordered_map>
#include <functional>
#include <any>

using namespace std;


struct C {
    std::unordered_map<int, std::function<void(std::any)>> m;

    template <typename T>
    void subscribe(int x, std::function<void(T)> &&f) {
        auto convert_to_any_func = [fx = std::move(f),x](std::any a) {
            try {
                fx(std::any_cast<T>(a));
            } catch (const std::bad_any_cast &e) {
                std::cerr << "Bad any_cast in subscriber for key " << x << ": " << e.what() << std::endl;
            }
        };
        m[x] = std::move(convert_to_any_func);
    }

    void publish(int x, std::any a) const {
        auto it = m.find(x);
        if (it != m.end()) {
            it->second(a);
        } else {
            std::cerr << "No subscriber for key " << x << std::endl;
        }
    }
};

int main() {
    C c;

    c.subscribe<int>(1, [](int x) { std::cout << "Received int: " << x << '\n'; });
    c.subscribe<float>(2, [](float f) { std::cout << "Received float: " << f << '\n'; });

    c.publish(1, 42);
    c.publish(2, 3.14f);
    c.publish(3, 99);  // no subscriber
}
