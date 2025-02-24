Pipeline (PUSH-PULL)

    Use case: Distributing workload among multiple workers
    How it works:
        PUSH sockets send tasks downstream.
        PULL sockets receive tasks.
        This pattern enables load balancing.

Example: Parallel processing of market data in an HFT system.
