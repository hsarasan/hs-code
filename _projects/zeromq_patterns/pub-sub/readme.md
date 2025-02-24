    Use case: Broadcasting messages to multiple subscribers
    How it works:
        The PUB (publisher) sends messages to multiple SUB (subscribers).
        Subscribers receive only messages they have subscribed to (filtered by topics).
        This pattern is asynchronous and allows one-to-many communication.

Example: Real-time market data distribution in trading systems.

Programs:

  publisher & subscriber - sends and subscribes to topic=news
  newspublisher & newssubscriber - sends and subscribes to topic=news
