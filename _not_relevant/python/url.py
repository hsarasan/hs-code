import urllib.request

try:    
    uflile = urllib.request.urlopen("http://www.google.com")    
    content=uflile.read().decode('utf-8')
    print(content)
except:
    print("Error in accessing the URL")