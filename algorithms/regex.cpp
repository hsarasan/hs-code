#include <iostream>
#include <string>

// Function to check if the input string matches the given pattern
bool isMatch(const std::string& text, const std::string& pattern) {
    // Base case: if the pattern is empty, the text must also be empty for a match
    if (pattern.empty()) {
        return text.empty();
    }

    // Check if the first character of the text matches the first character of the pattern
    bool first_match = (!text.empty() && (pattern[0] == text[0] || pattern[0] == '.'));

    // If the pattern contains '*', we need to handle zero or more of the previous element
    if (pattern.length() >= 2 && pattern[1] == '*') {
        // Two options:
        // 1. We skip the "x*" part of the pattern (move past '*') and see if the rest matches.
        // 2. If the first character matches, we advance in the text and try matching again (consume one character).
        return (isMatch(text, pattern.substr(2)) ||
                (first_match && isMatch(text.substr(1), pattern)));
    } else {
        // If there's no '*', proceed to the next character
        return first_match && isMatch(text.substr(1), pattern.substr(1));
    }
}

int main() {
    // Example usage
    std::string text = "abc123xyz";
    std::string pattern = "a.*xyz";  // Match: starts with 'a', any characters, ends with 'xyz'

    if (isMatch(text, pattern)) {
        std::cout << "The string matches the pattern!" << std::endl;
    } else {
        std::cout << "The string does not match the pattern." << std::endl;
    }

    return 0;
}
