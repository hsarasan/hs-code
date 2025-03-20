Implement the dining philosophers problem using threads, where each philosopher alternates between eating and thinking, using mutexes to ensure no deadlocks.

The key to avoiding deadlock is having a consistent way of locking the forks. By having even philosophers lock the left fork first, and odd philosophers lock the right fork first, we ensure that no cyclic dependency can form. This way, even if all philosophers try to pick up a fork at the same time, one philosopher will always be able to pick up both forks and eat, and no one will be stuck waiting forever.
