#include <iostream>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <coroutine>
#include <optional>

using namespace std;

// Thread-safe event queue
template<typename T>
class EventQueue {
    queue<T> q;
    mutex m;
    condition_variable cv;
public:
    void push(T value) {
        {
            lock_guard<mutex> lg(m);
            q.push(value);
        }
        cv.notify_one();
    }

    T wait_and_pop() {
        unique_lock<mutex> ul(m);
        cv.wait(ul, [&]{ return !q.empty(); });
        T value = q.front();
        q.pop();
        return value;
    }
};

// States
enum class State { Start, Play, Pause, Vol, Stop };

// Coroutine generator
template<typename T>
struct Generator {
    struct promise_type {
        optional<T> current_value;

        Generator get_return_object() {
            return Generator{coroutine_handle<promise_type>::from_promise(*this)};
        }
        suspend_always initial_suspend() { return {}; }
        suspend_always final_suspend() noexcept { return {}; }
        suspend_always yield_value(T value) {
            current_value = value;
            return {};
        }
        void return_void() {}
        void unhandled_exception() { terminate(); }
    };

    using handle_type = coroutine_handle<promise_type>;
    handle_type h;

    Generator(handle_type h) : h(h) {}
    ~Generator() { if (h) h.destroy(); }

    optional<T> next() {
        if (!h.done()) {
            h.resume();
            return h.promise().current_value;
        }
        return nullopt;
    }
};

// Event-driven state machine
Generator<State> stateMachine(EventQueue<int>& events) {
    State current = State::Start;
    co_yield current;

    while (true) {
        int choice = events.wait_and_pop();

        switch (choice) {
            case 1: current = State::Play; break;
            case 2: current = State::Pause; break;
            case 3: 
                if (current == State::Play) {
                    cout << "Increased Vol\n";
                    continue; // don't yield new state, just log
                } else {
                    cout << "NO OP\n";
                    continue;
                }
            case 0: current = State::Stop; break;
            default: 
                cout << "Invalid choice!\n";
                continue;
        }

        co_yield current;

        if (current == State::Stop)
            break;
    }
}

// Input thread
void interface(EventQueue<int>& events) {
    while (true) {
        cout << "Enter input (1/play 2/pause 3/vol 0/stop): ";
        int choice;
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input!\n";
            continue;
        }
        events.push(choice);
        if (choice == 0) break;
    }
}

// Processing thread
void processor(EventQueue<int>& events) {
    auto sm = stateMachine(events);
    while (auto s = sm.next()) {
        switch (*s) {
            case State::Start: cout << "State: Start\n"; break;
            case State::Play:  cout << "State: Play\n"; break;
            case State::Pause: cout << "State: Pause\n"; break;
            case State::Stop:  cout << "State: Stop\n"; break;
            case State::Vol:   break; // handled inline
        }

        if (*s == State::Stop) break;
    }
}

int main() {
    EventQueue<int> events;
    jthread t1(interface, ref(events));
    jthread t2(processor, ref(events));
    return 0;
}
