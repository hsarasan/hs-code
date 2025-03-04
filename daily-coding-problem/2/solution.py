def getProduct(nums):
    n=len(nums)
    down=[1]*n
    up=[1]*n
    for i in range(n-1):
        down[i+1]=down[i]*nums[i]
    for i in range(n-2,-1,-1):
        up[i]=up[i+1]*nums[i+1]
    result=[]
    for i in range(n):
        result.append(down[i]*up[i])
    return result
        
result=getProduct([1,2,3,4,5])
print(result)
result=getProduct([3,2,1])
print(result)