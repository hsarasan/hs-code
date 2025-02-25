This is a websocket server and client using boost asio
- The server listens on the port and responds with 4 messages to every client message
- The client send a message and accepts the response
- does it a few times and then close
- each client session is handled in a new thread at the server
