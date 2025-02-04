from queue import PriorityQueue
from collections import defaultdict
from typing import List


class Solution:

    def isPossible(self, nums: List[int]) -> bool:
        length_map=defaultdict(PriorityQueue)
        for num in nums:
            if (length_map[num-1].empty()):
                length_map[num].put(1)
                continue
            shortest_seq=length_map[num-1].get()
            length_map[num].put(shortest_seq+1)
        for key,v in length_map.items():
            if not v.empty():
                top=v.get()
                if (top<3):
                    return False
            
        return True

s=Solution()
ret=s.isPossible([1,2,3,4,5])
print(ret)
ret=s.isPossible([1,2,3,3,4,5])
print(ret)
ret=s.isPossible([1,2,3,3,4,4,5])
print(ret)
ret=s.isPossible([1,2,3,4,4,5])
print(ret)
