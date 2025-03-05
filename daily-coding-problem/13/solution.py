def find_biggest_substring(s,k):
    start=0
    end=0
    char_set=set()
    max_len=1
    char_set.add(s[0])
    while end<len(s):
        c=s[end]
        char_set.add(c)
        if len(char_set)<k+1:
            max_len=max(max_len,end-start+1)
            print(s[start:end+1])
            end+=1
        else:
            start=start+1
            end=start
            char_set.clear()
            if start<len(s):
                char_set.add(s[start])
    return max_len
    
print(find_biggest_substring("abcba",2))