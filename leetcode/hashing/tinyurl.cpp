#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    string char_map="abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    unordered_map<string,string> longurl_shorturl;
    unordered_map<string,string> shorturl_longurl;
    int m_id=0;

    int get_index(char c){
        int offset;
        if (c>='a' && c<='z') return c-'a';
        if (c>='A' && c<='Z'){
            offset=c-'A';
            return 26 + offset;
        }
        offset=c-'0';
        return 52+offset;
    }

    long url_to_id(string url){
        reverse(url.begin(),url.end());
        long id;
        for (char c: url){
            int i=get_index(c);
            id=id*62+i;
        }
        return id;
    }

    string id_to_url(long id){
        string url;
        while(id>0){
            id=id/62;
            int rem=id%62;
            url.push_back(char_map[rem]);            
        }
        std::reverse(url.begin(), url.end());
        return url;
    }

    // Encodes a URL to a shortened URL.
    string encode(string longUrl) {
        if (longurl_shorturl.count(longUrl)>0){
            return longurl_shorturl[longUrl];
        }
        string shortUrl=id_to_url(m_id++);
        longurl_shorturl[longUrl]=shortUrl;
        shorturl_longurl[shortUrl]=longUrl;
        return shortUrl;
    }

    // Decodes a shortened URL to its original URL.
    string decode(string shortUrl) {
        if (shorturl_longurl.count(shortUrl)>0)
            return shorturl_longurl[shortUrl];
        return "";
    }
};

int main(){
    Solution s;
    string longUrl="https://leetcode.com/problems/design-tinyurl";
    string shortUrl=s.encode(longUrl);
    assert(s.decode(shortUrl)==longUrl);
    return 0;
}