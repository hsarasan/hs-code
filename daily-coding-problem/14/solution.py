import random
n=0
inside_circle=0
for i in range(100000):
    x=random.uniform(-10,10) #use uniform to generate floating point instead of integers
    y=random.uniform(-10,10)
    if x*x+y*y<=100:
        inside_circle+=1
    n+=1
print(4*inside_circle/n)