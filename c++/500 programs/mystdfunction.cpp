#include <iostream>
#include <memory>

// Abstract base class with templated call signature
template <typename R, typename... Args>
struct CallableBase {
    virtual R call(Args... args) = 0;
    virtual ~CallableBase() = default;
};

// Wrapper that holds the actual callable
template <typename F, typename R, typename... Args>
struct CallableImpl : CallableBase<R, Args...> {
    F f;
    CallableImpl(F&& func) : f(std::forward<F>(func)) {}
    R call(Args... args) override {
        return f(std::forward<Args>(args)...);
    }
};

// Type-erased callable wrapper
template <typename>
class MyFunction;  // Primary template left undefined

// Specialization for function types
template <typename R, typename... Args>
class MyFunction<R(Args...)> {
    std::unique_ptr<CallableBase<R, Args...>> impl;

public:
    template <typename F>
    MyFunction(F&& f)
        : impl(std::make_unique<CallableImpl<F, R, Args...>>(std::forward<F>(f))) {}

    R operator()(Args... args) {
        return impl->call(std::forward<Args>(args)...);
    }
};

int add(int x, int y) {
    return x + y;
}

int main() {
    MyFunction<int(int, int)> f1 = add;
    MyFunction<int(int, int)> f2 = [](int a, int b) { return a * b; };

    std::cout << f1(3, 4) << "\n";  // Outputs: 7
    std::cout << f2(3, 4) << "\n";  // Outputs: 12
}

