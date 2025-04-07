#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <sstream>
#include <utility>
#include <unordered_set>

using namespace std;

// Custom hash function for pair<string, string>
struct pair_hash {
    template <typename T1, typename T2>
    std::size_t operator ()(const std::pair<T1, T2>& p) const {
        auto h1 = std::hash<T1>{}(p.first);
        auto h2 = std::hash<T2>{}(p.second);
        // Combine the two hash values using XOR and shifting
        return h1 ^ (h2 << 1);
    }
};

// Struct to represent a commit entry
struct CommitEntry {
    int id;
    int timestamp;
    unordered_map<string, string> file_info;  // file -> opaque_id
};

// Alias for file_to_commits using pair<string, string> as key
using FileToCommits = unordered_map<pair<string, string>, vector<pair<int, int>>, pair_hash>;

bool parse_log_entry(const string &line, CommitEntry &entry) {
    stringstream ss(line);
    string part;
    ss >> part;  // id
    if (part != "id") return false;
    
    ss >> entry.id;
    ss >> part;  // timestamp
    if (part != "timestamp") return false;
    
    ss >> entry.timestamp;

    // Read file -> opaque_id pairs
    string file, opaque_id;
    while (ss >> file >> opaque_id) {
        entry.file_info[file] = opaque_id;
    }
    return true;
}

void read_and_parse(int N, vector<string> &input_lines, FileToCommits &file_to_commits) {
    for (int i = 0; i < N; i++) {
        CommitEntry entry;
        if (parse_log_entry(input_lines[i], entry)) {
            for (const auto &file_info : entry.file_info) {
                file_to_commits[{file_info.first, file_info.second}].push_back({entry.timestamp, entry.id});
            }
        } else {
            cout << "Error parsing line: " << input_lines[i] << endl;
        }
    }

    // Print the contents of file_to_commits
    cout << "File to Commits Mapping:" << endl;
    for (const auto &entry : file_to_commits) {
        const auto &file_path_opaque = entry.first;
        cout << file_path_opaque.first << " " << file_path_opaque.second << " -> ";
        for (const auto &commit : entry.second) {
            cout << "(" << commit.first << ", " << commit.second << ") ";
        }
        cout << endl;
    }
}

int main() {
    int N;
    cin >> N;
    cin.ignore();  // Ignore the newline after the number of commits

    vector<string> input_lines(N);
    for (int i = 0; i < N; ++i) {
        getline(cin, input_lines[i]);
    }

    FileToCommits file_to_commits;
    read_and_parse(N, input_lines, file_to_commits);

    return 0;
}
