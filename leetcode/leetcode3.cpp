public:
    int lengthOfLongestSubstring(string s) {
        int start=0;
        int max=1;
        if (s.size()<2) return s.size();
        std::unordered_map<char,int> hashmap;
        while(start<s.size()){
            //std::cout<<"Start="<<start<<std::endl;
            auto i=start;
            hashmap.clear();
            bool done=false;
            while(!done ){
                auto ch=s[i];
                if (!hashmap.count(ch)){
                    hashmap[ch]=i;
                    i++;
                    if(i>=s.size()) {
                        done=true;
                        if (hashmap.size()> max)max=hashmap.size();
                        start=i;
                    }
                }
                else{
                    done=true;
                    //std::cout<<hashmap.size()<<std::endl;
                    start=hashmap[ch]+1;
                    if (hashmap.size()> max)max=hashmap.size();
                }
            }
        }
        return max;
    }
};