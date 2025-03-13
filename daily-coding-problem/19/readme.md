A builder is looking to build a row of N houses that can be of K different colors. He has a goal of minimizing cost while ensuring that no two neighboring houses are of the same color.

Given an N by K matrix where the nth row and kth column represents the cost to build the nth house with kth color, return the minimum cost which achieves this goal.


costs = [
    [17, 2, 17],  # Cost of painting house 0 with color 0, 1, and 2
    [16, 16, 5],  # Cost of painting house 1 with color 0, 1, and 2
    [14, 3, 19]   # Cost of painting house 2 with color 0, 1, and 2
]

min_cost=10