from pathlib import Path

path=Path("inheritance.py") 
print(path.exists())
contents=path.read_text()
lines=[line for line in contents.split("\n") if line.strip()]
print(lines[-2])
