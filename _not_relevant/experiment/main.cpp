#include <iostream>
#include <vector>
#include <unordered_map>
#include <sstream>
#include <string>

using namespace std;

// Custom hash function for pair<string, string>
struct pair_hash {
    template <typename T1, typename T2>
    size_t operator ()(const pair<T1, T2>& p) const {
        auto h1 = hash<T1>{}(p.first);  // Hash for the first element of the pair
        auto h2 = hash<T2>{}(p.second); // Hash for the second element of the pair
        return h1 ^ (h2 << 1); // Combine the hashes of the two elements
    }
};

// Function to parse a log entry
bool parse_log_entry(const string& line, unordered_map<pair<string, string>, vector<pair<int, int>>, pair_hash>& file_to_commits) {
    istringstream stream(line);
    string word;
    vector<string> parts;

    // Split the line into parts
    while (stream >> word) {
        parts.push_back(word);
    }

    // Check if the log entry is valid (must have at least 4 parts and even number of file-name + opaque-id pairs)
    if (parts.size() < 4 || parts.size() % 2 != 0) {
        return false;
    }

    try {
        int commit_id = stoi(parts[1]);
        int timestamp = stoi(parts[3]);

        // Process the file names and opaque ids
        for (size_t i = 4; i < parts.size(); i += 2) {
            string file_name = parts[i];
            string opaque_id = parts[i + 1];

            // Store the data in the unordered_map
            file_to_commits[{file_name, opaque_id}].push_back({timestamp, commit_id});
        }

    } catch (const invalid_argument&) {
        return false;
    }

    return true;
}

int main() {
    int N;
    cin >> N;
    cin.ignore();  // Ignore the newline after the number

    unordered_map<pair<string, string>, vector<pair<int, int>>, pair_hash> file_to_commits;

    // Read and process commit log entries
    for (int i = 0; i < N; ++i) {
        string line;
        getline(cin, line);

        if (!parse_log_entry(line, file_to_commits)) {
            cerr << "Invalid log entry at line " << i + 1 << endl;
        }
    }

    // Output the stored data for verification
    for (const auto& entry : file_to_commits) {
        const auto& key = entry.first;
        const auto& value = entry.second;

        cout << "File: " << key.first << ", Opaque ID: " << key.second << " -> ";

        for (const auto& commit : value) {
            cout << "(Timestamp: " << commit.first << ", Commit ID: " << commit.second << ") ";
        }
        cout << endl;
    }

    return 0;
}
