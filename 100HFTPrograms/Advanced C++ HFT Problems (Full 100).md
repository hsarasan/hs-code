Advanced C++ HFT Problems (Full 100)

This document contains 100 high-difficulty C++ program prompts suitable for hedge fund/HFT interview preparation. Each problem includes the key C++ feature focus and an optional hint. Difficulty: 8-9/10, estimated time per problem: ~1 hour.

---

1. Implement a lock-free ring buffer using std::atomic for multi-threaded producer-consumer. (Concurrency, atomics, memory ordering) Hint: Use circular buffer with atomic head/tail, avoid locks
2. Create a compile-time factorial calculator using consteval and templates. (TMP, consteval) Hint: Recursive template or consteval function
3. Implement a custom memory pool allocator for a vector-like container. (Memory management, RAII, alignment) Hint: Preallocate blocks, manage free list
4. Write a class hierarchy using multiple inheritance, inspect the vtable layout. (Object model, virtual inheritance) Hint: Use sizeof, pointer casts, typeid
5. Design a thread-safe singleton using std::call_once. (Concurrency, RAII) Hint: Lazy initialization, atomic flag or call_once
6. Implement a small object cache to reduce dynamic allocations. (Memory optimization, cache alignment) Hint: Use fixed-size blocks with free list
7. Write a variadic template sum function. (Templates, variadic parameters) Hint: Recursive template unpacking
8. Implement a perfect-forwarding wrapper. (Rvalue/lvalue references, forwarding) Hint: Use std::forward correctly
9. Create a custom hash function for unordered_map. (STL, hash customization) Hint: Override operator() and manage collisions
10. Write a RAII wrapper for file handles. (Resource management, exception safety) Hint: Implement destructor that closes the file
11. Implement a minimal coroutine-based generator for Fibonacci numbers. (Coroutines, lazy evaluation) Hint: Use co_yield for each Fibonacci value
12. Design a lock-free counter using std::atomic with memory order guarantees. (Concurrency, atomics) Hint: Use fetch_add with memory order semantics
13. Implement a type trait that detects if a type has a member function serialize(). (TMP, SFINAE) Hint: Use decltype and std::void_t
14. Benchmark vector, deque, and list for random insertions and deletions. (STL containers, performance analysis) Hint: Measure time using chrono
15. Implement a compile-time matrix multiplication library using template metaprogramming. (TMP, constexpr) Hint: Use nested template recursion
16. Create a smart pointer type with reference counting and cycle detection. (RAII, smart pointers) Hint: Combine shared_ptr and weak_ptr
17. Write a multi-threaded merge sort that splits work across threads efficiently. (Concurrency, sorting) Hint: Use std::thread for subarrays and join
18. Implement a placement new allocator with proper object lifetime management. (Memory management, placement new) Hint: Construct objects in preallocated memory
19. Create a custom optional type supporting copy/move and constexpr operations. (Templates, value semantics) Hint: Handle engaged/disengaged state safely
20. Design a cache-aligned struct for fast numerical computations. (Low-level optimization, cache alignment) Hint: Use alignas specifier
21. Implement a type-erased function wrapper (like std::function). (Type erasure, templates) Hint: Store callable objects in a polymorphic wrapper
22. Write a deadlock detection simulation with multiple threads acquiring locks in random order. (Concurrency, thread safety) Hint: Track lock order and detect cycles
23. Implement bit_cast usage to safely reinterpret a float as an integer type. (Low-level casting, std::bit_cast) Hint: Avoid undefined behavior with proper alignment
24. Design a compile-time factorial table stored in a constexpr array. (TMP, constexpr) Hint: Use consteval or recursive template initialization
25. Implement a thread-safe logging system using mutexes and minimal contention. (Concurrency, logging) Hint: Use std::mutex or std::scoped_lock carefully
26. Write a copy-on-write vector supporting concurrent read access. (Concurrency, copy-on-write semantics) Hint: Share immutable storage until modification
27. Implement a stack allocator that supports multiple nested frames for temporary objects. (Custom allocator, memory management) Hint: Use a contiguous block with frame pointers
28. Create a variadic template product function that multiplies all arguments at compile time. (TMP, variadic templates) Hint: Recursive template folding
29. Implement strong exception safety for a swap-based container class. (Exception safety, RAII) Hint: Use copy-and-swap idiom
30. Write a lock-free linked list supporting insert/delete in multi-threaded context. (Concurrency, lock-free structures) Hint: Use std::atomic pointers and compare_exchange
31. Create a compile-time prime checker using TMP. (TMP, constexpr) Hint: Use recursive template division checks
32. Implement lazy evaluation with templates and consteval in a numeric sequence generator. (TMP, lazy evaluation) Hint: Evaluate only when requested
33. Write a custom memory-aligned allocator and benchmark against std::allocator. (Memory management, alignment) Hint: Use alignas and manual allocation
34. Implement a coroutine-based pipeline where multiple stages process data asynchronously. (Coroutines, concurrency) Hint: Chain co_yield stages
35. Design a move-only wrapper type and store it inside STL containers. (Move semantics, containers) Hint: Delete copy constructor, implement move constructor
36. Implement std::span like view over an array and ensure bounds safety. (Views, ranges) Hint: Store pointer and size, enforce bounds in access
37. Write a deadlock-safe multi-resource locking mechanism using std::scoped_lock. (Concurrency, RAII) Hint: Lock multiple mutexes in one call
38. Implement a low-latency order book simulator with concurrent reads/writes. (HFT, lock-free structures) Hint: Use cache-aligned structures, atomic updates
39. Create a constexpr Fibonacci sequence generator using templates. (TMP, constexpr) Hint: Use recursion or template specialization
40. Implement a custom expected type for error handling without exceptions. (Templates, error handling) Hint: Store value or error variant
41. Write a thread pool that executes tasks with minimal latency. (Concurrency, threads) Hint: Use worker threads with task queue
42. Implement a compile-time factorial using recursion and template specialization. (TMP, constexpr) Hint: Recursive specialization until base case
43. Write a lock-free stack supporting multiple producers and consumers. (Concurrency, lock-free) Hint: Use std::atomic and compare_exchange
44. Create a constexpr power function for integers at compile-time. (TMP, constexpr) Hint: Recursive multiplication
45. Implement a minimal coroutine-based producer-consumer system. (Coroutines, concurrency) Hint: Use co_yield and co_await
46. Write a memory-leak detector using RAII and overridden new/delete. (Memory management, debugging) Hint: Track allocations in static registry
47. Create a compile-time string length calculator using templates. (TMP, constexpr) Hint: Use recursion on character array
48. Implement a multi-threaded circular buffer with minimal copying. (Concurrency, lock-free) Hint: Use atomic indices
49. Write a copy/move-safe resource handle for GPU or OS resources. (RAII, move semantics) Hint: Release resources in destructor, support move
50. Implement a custom type trait is_iterable that detects iterable types. (TMP, SFINAE) Hint: Check for begin() and end()
Advanced C++ HFT Problems (Full 100, Part 2)

51. Create a lock-free queue for integer streams and measure throughput. (Concurrency, lock-free) Hint: Use circular buffer with atomic head/tail
52. Implement a placement-new vector that grows without reallocating all elements. (Memory management, placement new) Hint: Preallocate blocks and construct in-place
53. Write a template meta-function all_same<Ts...> to check if all types are identical. (TMP, variadic templates) Hint: Compare each type with first type recursively
54. Design a cache-friendly structure of arrays for particle simulation. (Low-level optimization, memory layout) Hint: Store each field in contiguous arrays
55. Implement perfect forwarding in a chain of function adapters. (Templates, forwarding) Hint: Use std::forward in each wrapper
56. Write a thread-safe double-buffer system for low-latency data exchange. (Concurrency, low latency) Hint: Swap active/inactive buffers atomically
57. Implement a compile-time factorial using consteval lambda. (TMP, consteval, lambdas) Hint: Recursive lambda evaluated at compile time
58. Create a custom iterator for a container that supports reverse traversal. (Iterators, templates) Hint: Implement operator++ and operator--
59. Write a lock-free priority queue using atomic operations. (Concurrency, lock-free) Hint: Use atomic compare-exchange on nodes
60. Implement exception-safe swap for a custom string class. (Exception safety, RAII) Hint: Use temporary and move assignment
61. Create a template-based serialization system for POD types. (Templates, I/O) Hint: Use reinterpret_cast carefully and handle endianness
62. Implement thread-safe singleton with lazy initialization using atomics. (Concurrency, RAII) Hint: Use double-checked locking pattern
63. Write a memory-aligned structure for SIMD computations and vector math. (Low-level optimization, alignment) Hint: Use alignas(32) for AVX operations
64. Implement a type-erased polymorphic object container. (Type erasure, polymorphism) Hint: Use base class pointer to store derived objects
65. Write a lock-free hash map for integer keys. (Concurrency, lock-free) Hint: Use atomic bucket pointers and CAS operations
66. Implement a constexpr factorial lookup table generator. (TMP, constexpr) Hint: Fill array at compile time
67. Create a compile-time detection of member type value_type. (TMP, SFINAE) Hint: Use decltype with std::void_t
68. Implement a multi-threaded mergeable heap. (Concurrency, data structures) Hint: Merge sub-heaps in parallel
69. Write a custom allocator for std::vector with memory reuse. (Memory management, STL) Hint: Preallocate blocks, override allocate/deallocate
70. Create a thread-safe circular log buffer. (Concurrency, logging) Hint: Swap buffer atomically, handle wraparound
71. Implement a compile-time prime sieve using TMP. (TMP, constexpr) Hint: Use recursive template elimination of multiples
72. Write a lock-free ring buffer for fixed-size objects. (Concurrency, lock-free) Hint: Use atomic head/tail indices
73. Implement a move-only optional type with correct destructor semantics. (Move semantics, templates) Hint: Delete copy constructor, implement move and destructor
74. Create a template-based factorial calculator with partial specialization. (TMP, partial specialization) Hint: Specialize base case, recurse otherwise
75. Implement coroutine-based lazy range generator for numbers divisible by 3. (Coroutines, lazy evaluation) Hint: Use co_yield in a loop
76. Write a custom exception hierarchy with polymorphic catch. (Exception handling, polymorphism) Hint: Derive exceptions from a common base
77. Implement strongly typed enum class operations using templates. (Enums, templates) Hint: Overload operators for enum class
78. Create cache-optimized 2D matrix multiplication template. (Low-level optimization, templates) Hint: Use block multiplication and alignas
79. Write a multi-threaded reader-writer lock using std::atomic. (Concurrency, atomic operations) Hint: Implement lock counts and writer flag
80. Implement compile-time type-safe arithmetic using TMP. (TMP, type safety) Hint: Define operations only for compatible types
81. Create a memory pool for small object allocation with alignment. (Memory management, alignment) Hint: Manage free list with aligned blocks
82. Implement std::function-like callable wrapper supporting lambdas and function pointers. (Type erasure, templates) Hint: Use base wrapper with virtual call
83. Write a lock-free set for integers with atomic compare-exchange. (Concurrency, lock-free) Hint: Use linked nodes with CAS
84. Implement a template-based numeric range generator. (TMP, ranges) Hint: Generate compile-time array of numbers
85. Create a thread-safe stack with minimal locking. (Concurrency, lock minimization) Hint: Use atomic top pointer and CAS
86. Write a compile-time Fibonacci generator with consteval. (TMP, consteval) Hint: Recursive consteval function
87. Implement a coroutine pipeline for image processing simulation. (Coroutines, data flow) Hint: Chain co_yield stages per operation
88. Create a custom smart pointer with debug logging. (RAII, smart pointers) Hint: Log allocation/deallocation in constructor/destructor
89. Implement a lock-free multi-producer queue with hazard pointers. (Concurrency, lock-free) Hint: Track safe memory reclamation
90. Write compile-time string concatenation using TMP. (TMP, constexpr) Hint: Use recursive template to join char arrays
91. Implement low-latency order book with cache alignment. (HFT, low-latency, alignment) Hint: Align arrays of orders, avoid false sharing
92. Create a type trait is_callable<T> to detect callable types. (TMP, SFINAE) Hint: Use decltype with operator()
93. Implement a thread-safe priority queue using condition variables. (Concurrency, threads) Hint: Protect heap with mutex and CV
94. Write a placement-new based circular vector. (Memory management, placement new) Hint: Construct in preallocated contiguous block
95. Implement a coroutine-based producer-consumer integer stream. (Coroutines, concurrency) Hint: Use co_yield for produced values
96. Create a compile-time factorial map using TMP array. (TMP, constexpr) Hint: Fill array recursively at compile-time
97. Write a lock-free singly-linked list supporting safe concurrent insert/delete. (Concurrency, lock-free) Hint: Use CAS on node pointers
98. Implement a custom vector that avoids unnecessary copies using move semantics. (Move semantics, containers) Hint: Move elements during resize instead of copy
99. Create a compile-time type introspection system using std::is_same, decltype, and TMP. (TMP, type traits) Hint: Detect member types, functions, and properties
100. Implement a minimal HFT-style order book simulator with concurrent order insertions and matching. (Concurrency, HFT, lock-free) Hint: Use atomic operations, cache-aligned data structures
