    Use case: Asynchronous request-reply with multiple clients
    How it works:
        DEALER is a non-blocking version of REQ (can send multiple requests).
        ROUTER is a non-blocking version of REP (routes messages to specific clients).
        WORKER (if present, ROUTER forwards to worker). Worker will send response to Dealer via Router

DEALER->ROUTER->WORKER->ROUTER->DEALER
        
        Used to implement load-balanced RPC servers.

Example: High-performance trading gateways handling multiple clients.
