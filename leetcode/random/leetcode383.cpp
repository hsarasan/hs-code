class Solution {
    std::unordered_map<char,int> hashmap_mag;
    std::unordered_map<char,int> hashmap_ransomnote;
public:
    bool canConstruct(string ransomNote, string magazine) {
        for (const auto ch: ransomNote){
            hashmap_ransomnote[ch]++;
        }
        for (const auto ch: magazine){
            hashmap_mag[ch]++;
        }
        for ( auto const [k,v]: hashmap_ransomnote){
            if (hashmap_mag.count(k)==0) return false;
            if (hashmap_mag[k]<v ) return false;
        }
        return true;
    }
};