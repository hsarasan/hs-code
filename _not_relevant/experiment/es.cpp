#include <iostream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <memory>

using namespace std;

// Custom hash function for std::pair<string, string>
namespace std {
    template <>
    struct hash<pair<string, string>> {
        size_t operator()(const pair<string, string>& p) const {
            return hash<string>()(p.first) ^ (hash<string>()(p.second) << 1); // Combine hashes
        }
    };
}

struct LogEntry {
    int id;
    int timestamp;
    unordered_map<string, string> attributes;
};

unique_ptr<LogEntry> parse_log_entry(const string& line) {
    istringstream iss(line);
    vector<string> parts;
    string word;
    
    while (iss >> word) {
        parts.push_back(word);
    }
    
    if (parts.size() < 4 || parts.size() % 2 != 0) {
        return nullptr;
    }
    
    try {
        auto entry = make_unique<LogEntry>();
        entry->id = stoi(parts[1]);
        entry->timestamp = stoi(parts[3]);
        
        for (size_t i = 4; i < parts.size(); i += 2) {
            entry->attributes[parts[i]] = parts[i + 1];
        }
        
        return entry;
    } catch (...) {
        return nullptr;
    }
}

int main() {
    int N;
    cin >> N;
    cin.ignore(); // Clear the leftover newline from the input buffer
    
    vector<unique_ptr<LogEntry>> log_entries;
    unordered_map<int, unique_ptr<LogEntry>> commit_to_files;
    unordered_map<pair<string, string>, vector<int>> file_to_commits;
    bool ambiguous = false;
    
    for (int i = 0; i < N; ++i) {
        string line;
        getline(cin, line);
        if (line.empty()) {
            continue;  // Skip empty lines (if any)
        }
        auto entry = parse_log_entry(line);
        if (entry) {
            log_entries.push_back(move(entry));
            commit_to_files[log_entries.back()->id] = move(log_entries.back());
            
            for (const auto& kv : commit_to_files[log_entries.back()->id]->attributes) {
                file_to_commits[{kv.first, kv.second}].push_back(log_entries.back()->id);
            }
        }
    }
    
    // Check for ambiguity
    for (const auto& file_entry : file_to_commits) {
        const auto& commits = file_entry.second;
        if (commits.size() > 1) {
            for (size_t i = 0; i < commits.size() && !ambiguous; ++i) {
                for (size_t j = i + 1; j < commits.size(); ++j) {
                    const auto& commit_i = commit_to_files[commits[i]];
                    const auto& commit_j = commit_to_files[commits[j]];
                    
                    unordered_set<string> common_files;
                    for (const auto& attr : commit_i->attributes) {
                        if (commit_j->attributes.count(attr.first) && commit_j->attributes.at(attr.first) != attr.second) {
                            ambiguous = true;
                            break;
                        }
                    }
                    if (ambiguous) break;
                }
            }
        }
        if (ambiguous) break;
    }
    
    if (ambiguous) {
        cout << "AMBIGUOUS INPUT!" << endl;
        return 0;
    }
    
    int R;
    cin >> R;
    cin.ignore();  // Clear the leftover newline from the input buffer after reading R
    
    for (int i = 0; i < R; ++i) {
        string query;
        getline(cin, query);
        
        if (query.empty()) {
            continue; // Skip empty queries if any
        }
        
        istringstream iss(query);
        int start_ts, end_ts;
        string file_path, opaque_id;
        
        iss >> start_ts >> end_ts >> file_path >> opaque_id;
        
        vector<pair<int, int>> result;
        
        if (file_to_commits.count({file_path, opaque_id})) {
            for (int commit_id : file_to_commits[{file_path, opaque_id}]) {
                const auto& commit = commit_to_files[commit_id];
                if (commit->timestamp >= start_ts && commit->timestamp <= end_ts) {
                    result.emplace_back(commit->timestamp, commit_id);
                }
            }
        }
        
        sort(result.begin(), result.end());
        
        for (size_t j = 0; j < result.size(); ++j) {
            if (j > 0) cout << " ";
            cout << result[j].second;
        }
        cout << endl;
    }
    
    return 0;
}
