#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include<utility>
#include <algorithm>
#include <sstream>
#include <unordered_set>

using namespace std;

struct pair_hash{
    template <typename T1, typename T2>
    size_t operator() (const std::pair<T1,T2> &p) const{
        auto h1 = std::hash<T1>{}(p.first);
        auto h2 = std::hash<T2>{}(p.second);
        return h1^(h2<<1);
    }
};

struct CommitEntry{
    int commit_id;
    int timestamp;
    unordered_map<string,string> file_info;
};

using FileInfoToCommits=unordered_map< pair<string,string> , vector<pair<int,int>>, pair_hash >;

bool parse_log_entry(const string & line, CommitEntry & ce){
    stringstream ss(line);
    string part;
    ss>>part;
    if (part!="id") return false;
    ss>>ce.commit_id;
    ss>>part;
    if (part!="timestamp") return false;
    ss>>ce.timestamp;
    string file,repo_id;
    while (ss>>file >> repo_id){
        ce.file_info[file]=repo_id;
    }
    return true;
}

void read_and_parse(int N, vector<string>& input_lines, FileInfoToCommits &f2c){
    for (int i=0;i<N;++i){
        CommitEntry ce;
        bool ret=parse_log_entry(input_lines[i],ce);
        if (ret){
            for (const auto & file_info: ce.file_info){
                f2c[{file_info.first,file_info.second}].push_back({ce.timestamp,ce.commit_id });
            }
        }
        else{
            cout<<"Error parsing lines "<<endl;
        }
    }
    for (const auto & ce: f2c){
        const auto & file_path = ce.first;
        cout<<"File Path " << " "<<file_path.first<<" "<<file_path.second<<" => ";
        for (const auto & cm: ce.second){
            cout<<"("<<cm.first<<" "<<cm.second<<") ";
        }
        cout<<endl;
    }
}

void process_queries(int R, vector<string> queries, const FileInfoToCommits &f2c){
    for (int i=0; i<R; ++i){
        stringstream ss(queries[i]);
        int start_ts, end_ts;
        string file_path, repo_id;
        ss>>start_ts>>end_ts>>file_path>>repo_id;
        cout<<"Query "<<i<<"=> ";
        vector<pair<int,int>> result;

        if (f2c.find({file_path,repo_id})!=f2c.end()){
            const auto & commits=f2c.at({file_path,repo_id});
            for (const auto& commit: commits){
                if (start_ts<=commit.first && commit.first<=end_ts){
                    result.push_back(commit);
                }
            }
            if (!result.empty()){
                cout<<"Commit IDs ";
                for (const auto & commit: result){
                    cout<<commit.second<<" ";
                }
                cout<<endl;
            }
            else{
                cout<<"No commits found "<<endl;
            }
        }
        else{
            cout<<"NO commits forund "<<endl;
        }

    }


}

int main(){
    int N;
    cin>>N;
    cin.ignore();
    vector<string> input_lines(N);
    for (int i=0;i<N;++i){
        getline(cin,input_lines[i]);
    }
    FileInfoToCommits f2c;
    read_and_parse(N, input_lines, f2c);

    int R;
    cin>>R;
    cin.ignore();

    vector<string> queries(R);
    for (int i=0;i<R;++i){
        getline(cin,queries[i]);
    }
    process_queries(R,queries,f2c);

    return 0;
}