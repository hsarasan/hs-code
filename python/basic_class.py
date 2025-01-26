
class Foo:
    def __init__(self, arg=5):
        print ("Foo")
        self.x = arg

    def __add__(self, other):
        return Foo(self.x + other.x)
        
    def __str__(self):
        return str(self.x)
    
    def __del__(self):
        print("deleting Foo")
        del self.x

def memcheck(*args):
    if (id(args[0]) == id(args[1])):
        print ("same")
    else:
        print ("different")

f = Foo()
f2 = Foo()
memcheck(f,f2)
print("after addition")
f3 = f+f2
memcheck(f,f2)
