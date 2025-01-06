#include <boost/algorithm/string.hpp>
#include <iostream>

int main() {
    std::string str = "Boost Libraries";
    boost::to_upper(str);
    std::cout << str << std::endl;  // Should output "BOOST LIBRARIES"
    return 0;
}