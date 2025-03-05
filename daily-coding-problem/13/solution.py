def find_biggest_substring(s,k):
    start=0
    char_set=set()
    max_len=1
    for end in range(len(s)):
        char_set.add(s[end])
        while len(char_set)>k:
            char_set.remove(s[start])
            start+=1
        max_len=max(max_len,end-start+1)
    return max_len
    
print(find_biggest_substring("abcba",2))