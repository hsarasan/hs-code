class A:
    def __init__(self):
        print('A.__init__')
    def func(self):
        print('A.func')

class B(A):
    def __init__(self):
        print('B.__init__')
        super().__init__()
    def func(self):
        print('B.func')

class C(A):
    def __init__(self):
        print('C.__init__')
        super().__init__()
    def func(self):
        print('C.func')

class D(B, C):
    def __init__(self):
        print('D.__init__')
        super().__init__()

        
D().func()
print(D.mro())
d = D()
d.func()