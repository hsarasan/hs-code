    Use case: Asynchronous request-reply with multiple clients
    How it works:
        DEALER is a non-blocking version of REQ (can send multiple requests).
        ROUTER is a non-blocking version of REP (routes messages to specific clients).
        Used to implement load-balanced RPC servers.

Example: High-performance trading gateways handling multiple clients.
