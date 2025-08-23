#include <iostream>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <coroutine>
#include <optional>

using namespace std;

mutex m;
condition_variable cv;
queue<int> q;

enum class State { Start, Play, Pause, Vol, Stop };

// Coroutine-based generator
template<typename T>
struct Generator {
    struct promise_type {
        std::optional<T> current_value;

        Generator get_return_object() {
            return Generator{
                std::coroutine_handle<promise_type>::from_promise(*this)
            };
        }

        std::suspend_always initial_suspend() { return {}; }
        std::suspend_always final_suspend() noexcept { return {}; }
        std::suspend_always yield_value(T value) {
            current_value = value;
            return {};
        }

        void return_void() {}
        void unhandled_exception() { std::terminate(); }
    };

    using handle_type = std::coroutine_handle<promise_type>;
    handle_type h;

    Generator(handle_type h) : h(h) {}
    ~Generator() { if (h) h.destroy(); }

    std::optional<T> next() {
        if (!h.done()) {
            h.resume();
            return h.promise().current_value;
        }
        return std::nullopt;
    }
};

// Coroutine-based state machine that reacts to input
// it coyields the next state to transition to
Generator<State> stateMachine(queue<int>& q, mutex& m, condition_variable& cv) {
    co_yield State::Start;

    while (true) {
        unique_lock<mutex> ul(m);
        cv.wait(ul, [&]() { return !q.empty(); });

        int choice = q.front();
        q.pop();

        if (choice == 1) co_yield State::Play;
        else if (choice == 2) co_yield State::Pause;
        else if (choice==3) co_yield State::Vol;
        else if (choice == 0) {
            co_yield State::Stop;
            break;
        } else {
            cout << "Invalid choice!\n";
        }
    }
}

// Thread to read user input
void interface() {
    bool done = false;
    while (!done) {
        cout << "Enter input (1/play 2/pause 3/increase volume 0/stop): ";
        int choice;
        cin >> choice;

        {
            lock_guard<mutex> lg(m);
            q.push(choice);
        }
        cv.notify_one();
        done = (choice == 0);
    }
}

// Thread to process state machine
void process() {
    auto sm = stateMachine(q, m, cv);
    State current_state = State::Start;
    while (auto s = sm.next()) {
        switch (*s) {
            case State::Start: cout << "State: Start\n"; current_state=State::Start; break;
            case State::Play:  cout << "State: Play\n";  current_state=State::Play; break;
            case State::Pause: cout << "State: Pause\n"; current_state=State::Pause; break;
            case State::Stop:  cout << "State: Stop\n";  break;
            case State::Vol: 
                {
                    if (current_state!=State::Play) {
                        cout<<"NO OP"<<endl;
                        break; 
                    }
                    cout<<"Increased Vol "<<endl;
                    break;
                }
        }

        if (*s == State::Stop) break;
    }
}

int main() {
    jthread ui(interface);
    jthread processor(process);
    return 0;
}
