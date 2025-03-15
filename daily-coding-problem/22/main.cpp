#include <iostream>
#include <string>
#include <vector>
#include <iterator>
#include <algorithm>

using namespace std;

vector<string> result;

bool backtrack(vector<string>& dictionary, string  sentence, vector<string> words){
    //cout<<"Sentence = "<<sentence<<endl;
    if (sentence.length()==0) {
        result=words;
        return true;   
    }
    for (const auto & word: dictionary){
        int pos=sentence.find(word);
        if (word.size()>sentence.size()) continue;
        if (pos==0){
            words.push_back(word);
            auto str=sentence.substr(word.length());
            if(!backtrack(dictionary,str,words)){
                words.pop_back();
            }
        }
    }
    return false;
}


vector<string> splitSentence(vector<string>& dictionary, string & sentence){
    
    backtrack(dictionary,sentence,{});
    return result;
}

int main(){
    vector<string> dictionary{"quick", "brown", "the", "fox"};
    string sentence="thequickbrownfox";
    auto words=splitSentence(dictionary,sentence);
    cout<<words.size()<<endl;

    result.clear();
    dictionary={"bed","bath","and","beyond","bedbath"};
    sentence="bedbathandbeyond";
    words=splitSentence(dictionary,sentence);
    cout<<words.size()<<endl;
    copy(words.begin(), words.end(), ostream_iterator<string>(cout," "));
    return 0;
}