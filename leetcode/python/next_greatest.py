import sys

def next_greatest(nums):
    stack=[nums[0]]
    n=len(nums)
    result=[0]*n
    for i in range (0,n):
        num=nums[i]
        while( len(stack)>0 and nums[stack[0]]<=num):
            result[stack.pop()]=num
        stack.append(num)
    return result


nums=[1,2,5,2,3,6]
nums=next_greatest(nums)
print(nums)