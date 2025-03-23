Introduction
=====================

This is a simple distributed KV system with REST API and WAL persistance mechanims . 

Architecture
====================
Each instance of the KV store keeps the key values in memory.

If the key is not found in the instance, it is forwarded to the peer

TechStack - C++ with boost beast.

Rest API
==========================
Sample GET -   127.0.0.1:9000/get/city
Same POST - 127.0.0.1:9000/set
  {
  "key": "username",
  "value": "Alice"
}
Sample PUT - 127.0.0.1:9000/update/city
{
  "value": "Oxford"
}
Sample DELETE - 127.0.0.1:9000/delete/username


Benchmarking
=========================

The benchmarking was done using wrk

user@71collinsdrive:~/hs-code/_projects/distributed-kv/bench-test$ cat get.output 
Running 30s test @ http://localhost:9000/get/username
  8 threads and 100 connections
  Thread Stats   Avg      Stdev     Max   +/- Stdev
    Latency     4.89ms    1.11ms  18.67ms   87.95%
    Req/Sec     2.39k   300.85     2.75k    86.75%
  570740 requests in 30.01s, 47.90MB read
  Socket errors: connect 0, read 570736, write 0, timeout 0
Requests/sec:  19020.02
Transfer/sec:      1.60MB

user@71collinsdrive:~/hs-code/_projects/distributed-kv/bench-test$ cat post.output 
Running 30s test @ http://localhost:9000/set
  8 threads and 100 connections
  Thread Stats   Avg      Stdev     Max   +/- Stdev
    Latency    12.36ms    9.42ms 112.33ms   65.45%
    Req/Sec     1.01k   264.60     2.22k    81.17%
  242221 requests in 30.01s, 19.87MB read
  Socket errors: connect 0, read 242218, write 0, timeout 0
Requests/sec:   8070.82
Transfer/sec:    677.82KB








