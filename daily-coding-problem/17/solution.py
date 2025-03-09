class Node:
    def __init__(self,value,left=None,right=None):
        self.value=value
        self.children=[]


def create_tree(file_str):
    root=None
    level_map=dict()
    names=file_str.split("\n")
    for name in names:
        n=len(name)
        name=name.lstrip('\t')
        level=n-len(name)
        print(name,level)
        if level==0:
            root=Node(name)
            node=root
        else:
            node=Node(name)
        level_map[level]=node
        if level>0:
            level_map[level-1].children.append(node)
    return root

def traverse(root,parent_name):
    max_len=0
    if root is None:
        return
    node_name=parent_name+"/"+root.value
    max_len=max(max_len,len(node_name))
    print(node_name,len(node_name))
    for child in root.children:
        ret=traverse(child,node_name)
        max_len=max(max_len,ret)
    return max_len
    
    
root=create_tree("dir\n\tsubdir1\n\t\tfile1.ext\n\t\tsubsubdir1\n\tsubdir2\n\t\tsubsubdir2\n\t\t\tfile2.ext")
print(root)
max_len=traverse(root,"")
print(max_len)

