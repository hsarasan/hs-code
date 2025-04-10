#include <iostream>
#include <sstream>
#include <cctype>
#include <iomanip>

using namespace std;

string process_stream(istream& input, int N) {
    ostringstream result;
    char ch;
    bool processing_number = false;
    string current_number;
    bool after_dot_or_colon = false;

    while (input.get(ch)) {
        // Check if it's a digit, without following a '.' or ':'
        if (isdigit(ch)) {
            if (!processing_number) {
                processing_number = true;
                current_number.clear();
            }
            current_number += ch;  
            after_dot_or_colon = false;  
        }
        else {
           
            if (processing_number && !after_dot_or_colon) {
                ostringstream padded;
                padded << setw(N) << setfill('0') << current_number;
                result << padded.str();
                processing_number = false;  // Reset the number flag
            }

            if (ch == '.' || ch == ':') {
                after_dot_or_colon = true;
            }

            result << ch;
        }
    }

    // If the stream ends with a number, pad it
    if (processing_number && !after_dot_or_colon) {
        ostringstream padded;
        padded << setw(N) << setfill('0') << current_number;
        result << padded.str();
    }

    return result.str();
}

int main() {
    cout<<"Enter pad width : ";
    int N;
    cin>>N;
    cin.ignore();
    cout << "Enter text : ";
    string padded_text = process_stream(cin, N);  
    cout << "Processed text: " << padded_text << '\n';
}
