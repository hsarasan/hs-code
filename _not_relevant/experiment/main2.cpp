#include <iostream>
#include <vector>
#include <unordered_map>
#include <sstream>
#include <string>
#include <set>
#include <algorithm>

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
bool parse_log_entry(const string& line, unordered_map<pair<string, string>, vector<pair<int, int>>, pair_hash>& file_to_commits, unordered_map<int, vector<pair<string, string>>>& commit_to_files) {
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
            commit_to_files[commit_id].push_back({file_name, opaque_id});
        }

    } catch (const invalid_argument&) {
        return false;
    }

    return true;
}

// Function to check for ambiguity
bool check_ambiguity(const unordered_map<pair<string, string>, vector<pair<int, int>>, pair_hash>& file_to_commits, const unordered_map<int, vector<pair<string, string>>>& commit_to_files) {
    for (const auto& file_commits : file_to_commits) {
        const auto& file_path = file_commits.first;
        const auto& commits = file_commits.second;

        if (commits.size() > 1) {
            for (size_t i = 0; i < commits.size(); ++i) {
                for (size_t j = i + 1; j < commits.size(); ++j) {
                    const auto& commit_i = commits[i];
                    const auto& commit_j = commits[j];

                    // Compare commits for ambiguity (timestamp, file_name, opaque_id)
                    if (commit_i.first != commit_j.first) {
                        return false;
                    }
                }
            }
        }
    }

    return false;
}

// Function to process the query
void process_query(const string& query, const unordered_map<pair<string, string>, vector<pair<int, int>>, pair_hash>& file_to_commits) {
    istringstream query_stream(query);
    int start_ts, end_ts;
    string file_name, opaque_id;
    query_stream >> start_ts >> end_ts >> file_name >> opaque_id;

    // Check if the file_name + opaque_id exists in the map
    auto key = make_pair(file_name, opaque_id);
    if (file_to_commits.find(key) != file_to_commits.end()) {
        const auto& commits = file_to_commits.at(key);

        vector<int> result;
        // Find commits within the timestamp range
        for (const auto& commit : commits) {
            if (commit.first >= start_ts && commit.first <= end_ts) {
                result.push_back(commit.second); // Add commit ID to the result
            }
        }

        // If result is empty, no commits match the query
        if (!result.empty()) {
            // Output the commit IDs in sorted order
            sort(result.begin(), result.end());
            for (const int commit_id : result) {
                cout << commit_id << " ";
            }
            cout << endl;
        } else {
            cout << "No commits found for the query!" << endl;
        }
    } else {
        cout << "No data found for the file and opaque ID!" << endl;
    }
}

int main() {
    int N;
    cin >> N;
    cin.ignore();  // Ignore the newline after the number

    unordered_map<pair<string, string>, vector<pair<int, int>>, pair_hash> file_to_commits;
    unordered_map<int, vector<pair<string, string>>> commit_to_files;

    // Read and process commit log entries
    for (int i = 0; i < N; ++i) {
        string line;
        getline(cin, line);

        if (!parse_log_entry(line, file_to_commits, commit_to_files)) {
            cerr << "Invalid log entry at line " << i + 1 << endl;
        }
    }

    // Check for ambiguity
    if (check_ambiguity(file_to_commits, commit_to_files)) {
        cout << "AMBIGUOUS INPUT!" << endl;
        return 0;
    }

    // Read the number of queries
    int Q;
    cin >> Q;
    cin.ignore();  // Ignore the newline after the number

    // Process each query
    for (int i = 0; i < Q; ++i) {
        string query;
        getline(cin, query);

        process_query(query, file_to_commits);
    }

    return 0;
}
