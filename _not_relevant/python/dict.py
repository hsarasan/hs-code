def loop(*args):
    for arg in args:
        print(arg)
    for key in args[0].keys():
        print (key, end=" ")
    print()
    for value in args[0].values():
        print(value, end=" ")
    print()
    for key,value in args[0].items():
        print(key+','+value, end=" ")
    print()
def __main__():
    dict={}
    dict['uk']='London'
    dict['us']='Washington'
    dict['fr']='Paris'
    dict['in']='New Delhi'
    loop(dict)
    del dict['uk']
    loop(dict)
    
if __name__ == "__main__":
    __main__()



