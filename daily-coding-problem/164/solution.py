
def find_duplicate(arr):
    seen=set()
    for i in arr:
        if i in seen:
            print(i)
            return
        seen.add(i)
    return -1
    
find_duplicate([1,2,3,4,4])

