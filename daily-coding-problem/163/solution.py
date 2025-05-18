def get_value(a,b,oper):
    if oper=='*':
        return a*b
    elif oper=='+':
        return a+b
    elif oper=='-':
        return a-b
    else:
        return a/b

def evaluate(arr):
    stack=[]
    for value in arr:
        if isinstance(value,int):
            stack.append(value)
        else:
            b=stack.pop()
            a=stack.pop()
            c=int(get_value(a,b,value))
            stack.append(c)
    return int(stack.pop())


print(evaluate([15, 7, 1, 1, '+', '-', '/', 3, '*', 2, 1, 1, '+', '+', '-']))
