Executive Profile
==========================================
Senior C++ Systems Engineer specializing in ultra-low latency electronic trading platforms, quantitative infrastructure, and performance-critical distributed systems. Expert in architecting deterministic, low-jitter software using modern C++, Linux internals, advanced concurrency, and hardware-aware programming. Proactively bridges the gap between deep systems engineering and market microstructure to deliver high-performance execution, risk, and trading workflows

Technical Expertise
===========================
- Languages: C++ (C++17/20/23), Rust, Python.
- Low-Latency & Systems: Lock-Free/Wait-Free Concurrency, Memory Management (Custom Allocators, Cache-Alignment), Cache-Conscious Data Structures, SIMD, Template Metaprogramming.
- Linux & Infrastructure: Linux Performance Engineering, Core Pinning, Thread Affinity, Huge Pages, Low-Latency Kernel Tuning, eBPF.
- Networking & Protocols: TCP/IP, UDP Multicast, Socket Programming, FIX/FAST, ITCH/OUCH market data protocols.
- Domain Knowledge: Market Microstructure, Smart Order Routing (SOR), Electronic Execution, Equities & Derivatives Pricing, Real-time Risk Analytics.
- Tools & Frameworks: Google Test, Catch2, Boost, GDB, Valgrind, Perf, Google Benchmark.

Core Professional Competencies
=================================
- Ultra-Low Latency Trading Systems: Architecture and development of deterministic market data feed handlers and order execution gateways.
- Distributed Systems & Analytics: Engineering highly available, fault-tolerant distributed caches and real-time risk management platforms.
- Quantitative Software Engineering: Implementing high-throughput mathematical models and derivatives pricing libraries with minimal computational overhead.
- Technical Leadership: Steering architectural direction for multi-year engineering initiatives, defining coding standards, and raising engineering bars through rigorous code reviews and mentorship.

Selected Open-Source Engineering Portfolio
=========================================================

Ultra-Low Latency C++ Trading Engine | [GitHub URL]:
=====================================================
- Architected a deterministic, lock-free matching and execution engine utilizing C++20 and strict cache-aligned memory layouts to eliminate cache misses.
- Implemented optimized order book state management achieving sub-microsecond end-to-end processing latency under high-throughput scenarios.
- Utilized template metaprogramming to parse market data protocols at compile-time, minimizing runtime overhead.

High-Throughput Distributed Cache | [GitHub URL]:
======================================================
- Developed a high-performance, distributed key-value cache in C++ tailored for Linux environments, featuring custom memory allocators to prevent heap fragmentation.
- Implemented a zero-copy network layer using optimized UDP multicast and TCP socket rings, achieving deterministic data replication across nodes.
- Integrated strict concurrency primitives to ensure thread-safe data access with minimal lock contention under heavy write loads.

High-Performance Derivatives Pricing Library | [GitHub URL]
================================================================
- Designed and built a multi-threaded quantitative finance library in Rust, focusing on safety and predictable performance.
- Implemented Black-Scholes and Monte Carlo simulation models optimized for SIMD hardware lanes to maximize parallel mathematical throughput.
- Leveraged Rust’s strict memory safety and concurrency models to build a highly parallelized risk evaluation engine without data races.
