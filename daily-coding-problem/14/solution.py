import random
n=0
inside_circle=0
for i in range(100000):
    x=random.uniform(-1,1) #use uniform to generate floating point instead of integers
    y=random.uniform(-1,1)
    if x*x+y*y<=1:
        inside_circle+=1
    n+=1
print(4*inside_circle/n)