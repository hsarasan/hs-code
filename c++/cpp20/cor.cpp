#include <coroutine>
#include <iostream>
#include <string>

// Generator for traffic light states
struct TrafficLightGenerator {
    struct promise_type;
    using handle_type = std::coroutine_handle<promise_type>;

    struct promise_type {
        std::string current;

        auto get_return_object() {
            return TrafficLightGenerator{handle_type::from_promise(*this)};
        }
        std::suspend_always initial_suspend() { return {}; }
        std::suspend_always final_suspend() noexcept { return {}; }

        std::suspend_always yield_value(std::string value) {
            current = value;
            return {};
        }

        void return_void() {}
        void unhandled_exception() { std::exit(1); }
    };

    handle_type coro;

    explicit TrafficLightGenerator(handle_type h) : coro(h) {}
    ~TrafficLightGenerator() { if (coro) coro.destroy(); }

    std::string next() {
        coro.resume();
        if (coro.done()) return "";
        return coro.promise().current;
    }

    bool done() const {
        return coro.done();
    }
};

// Coroutine acting as a state machine
TrafficLightGenerator traffic_light() {
    while (true) {
        co_yield "RED";
        co_yield "GREEN";
        co_yield "YELLOW";
    }
}

int main() {
    auto light = traffic_light();
    for (int i = 0; i < 6; ++i) {
        std::cout << "Light is: " << light.next() << "\n";
    }
}

