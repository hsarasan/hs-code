#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <sstream>
#include <string>
#include <algorithm>

using namespace std;

// Custom hash function for pair<string, string>
template <typename T1, typename T2>
struct hash<pair<T1, T2>> {
    size_t operator()(const pair<T1, T2>& p) const noexcept {
        auto h1 = hash<T1>{}(p.first);
        auto h2 = hash<T2>{}(p.second);
        return h1 ^ (h2 << 1);  // Combine the hash values
    }
};

// Define a struct to store commit log entries
struct CommitEntry {
    int id;
    int timestamp;
    unordered_map<string, string> files;
};

// Function to parse a log entry
CommitEntry* parse_log_entry(const string& line) {
    istringstream stream(line);
    string word;
    vector<string> parts;

    while (stream >> word) {
        parts.push_back(word);
    }

    if (parts.size() < 4 || parts.size() % 2 != 0) {
        return nullptr;
    }

    CommitEntry* entry = new CommitEntry();
    try {
        entry->id = stoi(parts[1]);
        entry->timestamp = stoi(parts[3]);
        for (size_t i = 4; i < parts.size(); i += 2) {
            entry->files[parts[i]] = parts[i + 1];
        }
    } catch (const invalid_argument&) {
        delete entry;
        return nullptr;
    }

    return entry;
}

// Function to process the log entries and detect ambiguity
bool check_for_ambiguity(const unordered_map<int, CommitEntry*>& commit_to_files, 
                         const unordered_map<pair<string, string>, vector<int>>& file_to_commits) {
    
    for (const auto& pair : file_to_commits) {
        const auto& commits = pair.second;
        if (commits.size() > 1) {
            for (size_t i = 0; i < commits.size(); ++i) {
                for (size_t j = i + 1; j < commits.size(); ++j) {
                    CommitEntry* commit_i = commit_to_files.at(commits[i]);
                    CommitEntry* commit_j = commit_to_files.at(commits[j]);
                    unordered_set<string> common_files;
                    for (const auto& file_i : commit_i->files) {
                        if (commit_j->files.find(file_i.first) != commit_j->files.end()) {
                            common_files.insert(file_i.first);
                        }
                    }
                    for (const auto& file : common_files) {
                        if (file != "id" && file != "timestamp" && commit_i->files[file] != commit_j->files[file]) {
                            return false; // Ambiguity found
                        }
                    }
                }
            }
        }
    }
    return false; // No ambiguity found
}

// Function to process the queries and find matching commits
vector<int> process_query(const string& query, 
                          const unordered_map<pair<string, string>, vector<int>>& file_to_commits,
                          const unordered_map<int, CommitEntry*>& commit_to_files) {
    istringstream qstream(query);
    string start_ts_str, end_ts_str, file_path, opaque_id;
    qstream >> start_ts_str >> end_ts_str >> file_path >> opaque_id;

    int start_ts = stoi(start_ts_str);
    int end_ts = stoi(end_ts_str);

    vector<int> result;
    auto file_key = make_pair(file_path, opaque_id);

    if (file_to_commits.find(file_key) != file_to_commits.end()) {
        for (int commit_id : file_to_commits.at(file_key)) {
            CommitEntry* commit = commit_to_files.at(commit_id);
            if (start_ts <= commit->timestamp && commit->timestamp <= end_ts) {
                result.push_back(commit_id);
            }
        }
    }

    sort(result.begin(), result.end());
    return result;
}

// Function to read input data and return log entries
void read_input(int& N, vector<CommitEntry*>& log_entries, 
                unordered_map<int, CommitEntry*>& commit_to_files, 
                unordered_map<pair<string, string>, vector<int>>& file_to_commits) {
    cin >> N;
    cin.ignore(); // Ignore the newline after the number

    // Read and process commit log entries
    for (int i = 0; i < N; ++i) {
        string line;
        getline(cin, line);
        CommitEntry* entry = parse_log_entry(line);
        if (entry) {
            log_entries.push_back(entry);
            commit_to_files[entry->id] = entry;
            for (const auto& file : entry->files) {
                file_to_commits[{file.first, file.second}].push_back(entry->id);
            }
        }
    }
}

// Function to handle user queries
void handle_queries(int R, const unordered_map<pair<string, string>, vector<int>>& file_to_commits,
                    const unordered_map<int, CommitEntry*>& commit_to_files) {
    for (int i = 0; i < R; ++i) {
        string query;
        getline(cin, query);

        vector<int> result = process_query(query, file_to_commits, commit_to_files);

        if (!result.empty()) {
            for (int commit_id : result) {
                cout << commit_id << " ";
            }
            cout << endl;
        } else {
            cout << "No commits found." << endl;
        }
    }
}

// Main function to run the program
int main() {
    int N;
    vector<CommitEntry*> log_entries;
    unordered_map<int, CommitEntry*> commit_to_files;
    unordered_map<pair<string, string>, vector<int>> file_to_commits;

    read_input(N, log_entries, commit_to_files, file_to_commits);

    // Check for ambiguity
    if (check_for_ambiguity(commit_to_files, file_to_commits)) {
        cout << "AMBIGUOUS INPUT!" << endl;
        return 0;
    }

    int R;
    cin >> R;
    cin.ignore(); // Ignore the newline after the number

    handle_queries(R, file_to_commits, commit_to_files);

    // Clean up allocated memory
    for (auto entry : log_entries) {
        delete entry;
    }

    return 0;
}
