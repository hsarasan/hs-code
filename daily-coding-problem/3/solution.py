class Node:
    def __init__(self, val, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right
        
def serialize(node):
    result=''
    if node is None:
        result+='#,'
        return result
    
    result+=node.val
    result+=','
    result+=serialize(node.left)
    result+=serialize(node.right)
    return result

def deserialize_util(tokens, index):
    """Helper function for recursive deserialization."""
    if index[0] >= len(tokens) or tokens[index[0]] == "#":
        index[0] += 1  # Move past the '#'
        return None

    node = Node(tokens[index[0]])
    index[0] += 1  # Move to the next token
    node.left = deserialize_util(tokens, index)
    node.right = deserialize_util(tokens, index)
    return node

def deserialize(serialzed_string):
    serialzed_string=serialzed_string[:-1]
    tokens=serialzed_string.split(",")
    print(tokens)
    return deserialize_util(tokens,[0])


node = Node('root', Node('left', Node('left.left')), Node('right'))
assert deserialize(serialize(node)).left.left.val == 'left.left'