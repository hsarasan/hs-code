#include <coroutine>
#include <optional>
#include <iostream>

using namespace std;

template<typename T>
struct generator {
    struct promise_type {
        std::optional<T> current_value;

        generator get_return_object() {
            return generator{
                std::coroutine_handle<promise_type>::from_promise(*this)};
        }
        std::suspend_always initial_suspend() noexcept { return {}; }
        std::suspend_always final_suspend() noexcept { return {}; }
        std::suspend_always yield_value(T value) noexcept {
            current_value = std::move(value);
            return {};
        }
        void return_void() noexcept {}
        void unhandled_exception() { std::terminate(); }
    };

    using handle_type = std::coroutine_handle<promise_type>;
    handle_type coro;

    explicit generator(handle_type h) : coro(h) {}
    generator(const generator&) = delete;
    generator(generator&& other) noexcept : coro(other.coro) {
        other.coro = nullptr;
    }
    ~generator() {
        if (coro) coro.destroy();
    }

    struct iterator {
        handle_type coro;
        bool done;

        iterator(handle_type h, bool is_done) : coro(h), done(is_done) {}

        iterator& operator++() {
            coro.resume();
            done = coro.done();
            return *this;
        }

        T operator*() const {
            return *coro.promise().current_value;
        }

        bool operator!=(std::default_sentinel_t) const {
            return !done;
        }
    };

    iterator begin() {
        coro.resume();
        return iterator{coro, coro.done()};
    }
    std::default_sentinel_t end() { return {}; }
};

// Sequential number coroutine
generator<int> seq_generator(int start = 0) {
    int current = start;
    while (true) {
        cout<<"Entering "<<endl;
        co_yield current++;
        cout<<"Returning "<<endl;
    }
}

int main() {
    auto seq = seq_generator(100);
    int count = 0;
    for (auto n : seq) {
        std::cout << n << "\n";
        cout<<"============="<<endl;
        if (++count >= 10) break; // limit output
    }
}
