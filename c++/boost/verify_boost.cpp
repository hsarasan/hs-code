#include <iostream>
#include <thread>
#include <boost/chrono.hpp>
#include <boost/system/error_code.hpp>

int main() {
    // Boost Chrono Example: Measure elapsed time using Boost Chrono
    boost::chrono::steady_clock::time_point start = boost::chrono::steady_clock::now();
    
    // Simulating some work (sleep for 2 seconds)
    std::this_thread::sleep_for(std::chrono::seconds(2));
    
    boost::chrono::steady_clock::time_point end = boost::chrono::steady_clock::now();
    
    boost::chrono::duration<double> elapsed = end - start;
    std::cout << "Elapsed time: " << elapsed.count() << " seconds" << std::endl;

    // Boost System Example: Using Boost system error code
    boost::system::error_code ec;
    if (ec) {
        std::cout << "Error: " << ec.message() << std::endl;
    } else {
        std::cout << "No error!" << std::endl;
    }

    return 0;
}
