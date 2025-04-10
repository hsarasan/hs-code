#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>

using namespace std;

std::string pad_whole_numbers_in_string(const std::string& input, int N) {
    std::ostringstream result;
    size_t i = 0;
    while (i < input.size()) {
        // Skip non-digit characters
        if (!std::isdigit(input[i])) {
            result << input[i];
            ++i;
            continue;
        }

        // Check if it's preceded by '.' or ':'
        if (i > 0 && (input[i - 1] == '.' || input[i - 1] == ':')) {
            // Copy the number as-is
            while (i < input.size() && std::isdigit(input[i])) {
                result << input[i++];
            }
            continue;
        }

        
        size_t start = i;
        while (i < input.size() && std::isdigit(input[i])) {
            ++i;
        }
        std::string number = input.substr(start, i - start);

        // Pad with leading zeros
        std::ostringstream padded;
        padded << std::setw(N) << std::setfill('0') << number;
        result << padded.str();
    }

    return result.str();
}

int main(){
    cout<<pad_whole_numbers_in_string("abcd -1.2 3.2.2 3:4 a..2",3)<<endl;
}