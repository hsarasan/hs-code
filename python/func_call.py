def f(*args):
    for v in args:
        print (v)

        
def f2(**kwargs):
    print ("f2")
    for k,v in kwargs.items():
        print(k,"=",v)
    
def __main__():
    f(1,2,3,4,5)
    f2(i=1,s='hari',d=[1,2,3])
    
if __name__ == "__main__":
    __main__()



