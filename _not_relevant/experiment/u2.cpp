#include <iostream>
#include <sstream>
#include <cctype>
#include <iomanip>

std::string process_stream(std::istream& input, int N) {
    std::ostringstream result;
    char ch;
    bool in_number = false;
    std::string current_number;
    bool after_dot_or_colon = false;

    while (input.get(ch)) {
        // Check if it's a digit, and we are not following a '.' or ':'
        if (std::isdigit(ch)) {
            if (!in_number) {
                in_number = true;
                current_number.clear();
            }
            current_number += ch;  // Add digit to current number
            after_dot_or_colon = false;  // Reset flag for numbers after '.' or ':'
        }
        else {
            // If we were processing a number and it's not after '.' or ':', pad it
            if (in_number && !after_dot_or_colon) {
                std::ostringstream padded;
                padded << std::setw(N) << std::setfill('0') << current_number;
                result << padded.str();
                in_number = false;  // Reset the number flag
            }

            // Check if it's a '.' or ':' to mark numbers after it as exempt from padding
            if (ch == '.' || ch == ':') {
                after_dot_or_colon = true;
            }

            // Directly append non-number characters
            result << ch;
        }
    }

    // If the stream ends with a number, pad it
    if (in_number && !after_dot_or_colon) {
        std::ostringstream padded;
        padded << std::setw(N) << std::setfill('0') << current_number;
        result << padded.str();
    }

    return result.str();
}

int main() {
    std::cout<<"Enter pad width : ";
    int N;
    std::cin>>N;
    std::cout << "Enter text : ";
    std::string padded_text = process_stream(std::cin, N);  
    std::cout << "Processed text: " << padded_text << '\n';
}
