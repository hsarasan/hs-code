# List comprehension is a concise way to create lists. 
# It consists of brackets containing an expression followed by a for clause, 
# then zero or more for or if clauses. 
# The expressions can be anything, meaning you can put in all kinds of objects in lists.
# step 1 cubes = []
# step 2 cubes=[i**3]
# step 3 cubes=[i**3 for i in range(1,5)]



cubes=[i**3 for i in range(1,15)]
print(cubes[2:5])
