class Node:
    def __init__(self,val,left=None,right=None):
        self.value=val
        self.left=left
        self.right=right

def no_of_unival(root):
    if root is None:
        return 0,None
    if root.left is None and root.right is None:
        return 1,root.value
    n1,val1=no_of_unival(root.left)
    n2,val2=no_of_unival(root.right)
    if val1 and val2 and val1==val2:
        if val1==root.value:
            return 1+n1+n2,root.value
        else:
            return n1+n2,None
    return n1+n2,None

    
    
root = Node(0, Node(1), Node(0, Node(1, Node(1), Node(1)), Node(0)))
print(no_of_unival(root))