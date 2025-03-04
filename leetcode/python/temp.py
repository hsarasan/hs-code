import sys

class Tree:
    def __init__(self):
        print(' from ctor')
        self.value=0
    
    def set(self,**kwargs):
        for key,value in kwargs.items():
            print(key,"=",value)
            setattr(self,key,value)
    
    def get(self,arg):
        return getattr(self,arg,None)

    
        
tr=Tree()
tr.set(value=10)
print(tr.get("value"))