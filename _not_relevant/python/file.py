from pathlib import Path

path=Path("inheritance.py") 
print(path.exists())
contents=path.read_text()
lines=[line for line in contents.split("\n") if line.strip() and line is not None]
contents=""
for line in lines:
    contents+=line+"\n"
path=Path("temp.txt")
path.write_text(contents)
