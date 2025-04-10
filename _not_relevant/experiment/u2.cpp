#include <iostream>
#include <sstream>
#include <iomanip>
#include <cctype>  

using namespace std;

string process_stream(istream& input, int N) {
    ostringstream result;
    bool processing_number = false;
    bool skip_padding = false;  
    bool was_punctuation = false;  // Tracks if the previous character was '.' or ':'
    string current_number;
    
    for (char ch; input.get(ch); ) {
        if (isdigit(ch)) {
            // Beginning a new number: set skip_padding based on preceding punctuation
            if (!processing_number) {
                processing_number = true;
                skip_padding = was_punctuation;
                current_number.clear();
            }
            current_number.push_back(ch);
            was_punctuation = false;
        } else {
            // If a number was being processed, flush it to the result before handling the character.
            if (processing_number) {
                if (!skip_padding) {
                    ostringstream padded;
                    padded << setw(N) << setfill('0') << current_number;
                    result << padded.str();
                } else {
                    result << current_number;
                }
                processing_number = false;
                skip_padding = false;
                current_number.clear();
            }

            // Set the punctuation flag if the current character is '.' or ':'
            if (ch == '.' || ch == ':') {
                was_punctuation = true;
            } else {
                was_punctuation = false;
            }
            result << ch;
        }
    }
    
    // Flush any number remaining at the end of the stream.
    if (processing_number) {
        if (!skip_padding) {
            ostringstream padded;
            padded << setw(N) << setfill('0') << current_number;
            result << padded.str();
        } else {
            result << current_number;
        }
    }
    return result.str();
}

int main() {
    cout << "Enter pad width: ";
    int N;
    cin >> N;
    if (N <= 0) {
        cerr << "Pad width must be a positive integer." << endl;
        return 1;
    }
    cin.ignore();  // Clear newline left in the input buffer
    cout << "Enter text: ";
    string processed_text = process_stream(cin, N);
    cout << "Processed text: " << processed_text << '\n';
    return 0;
}
