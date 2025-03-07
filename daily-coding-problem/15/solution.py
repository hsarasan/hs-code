import random

def pick_a_random_number(N):
    n=1
    for i in range(2,N):
        rand=random.randint(1,i)
        if rand==1 :
           n=i
    return n
        
print(pick_a_random_number(10)) 