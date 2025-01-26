from random import randint
from collections import Counter

dice=[randint(1,6) for i in range(1,100)]
c=Counter(dice)
leader=c.most_common(1)
print(leader[0][0])
    