import example  # This is the .so module compiled from example.cpp

# Create a Pet object
dog = example.Pet("Buddy", 5)

# Call C++ methods from Python
print(dog.info())  # Buddy is 5 years old.

dog.setName("Charlie")
dog.setAge(6)

print("Name:", dog.getName())  # Charlie
print("Age:", dog.getAge())    # 6
print(dog.info())              # Charlie is 6 years old.

