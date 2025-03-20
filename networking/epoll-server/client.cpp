#include <iostream>
#include <sys/epoll.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <cstring>
#include <chrono>
#include <thread>

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 8080
#define MAX_EVENTS 5

// Function to set a socket to non-blocking mode
void set_nonblocking(int sock) {
    int flags = fcntl(sock, F_GETFL, 0);
    fcntl(sock, F_SETFL, flags | O_NONBLOCK);
}

int main() {
    int sock_fd, epoll_fd;
    struct sockaddr_in server_addr;

    // Create socket
    sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (sock_fd < 0) {
        perror("Socket creation failed");
        return 1;
    }

    // Set socket to non-blocking mode
    set_nonblocking(sock_fd);

    // Server details
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    inet_pton(AF_INET, SERVER_IP, &server_addr.sin_addr);

    // Initiate connection (non-blocking)
    if (connect(sock_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        if (errno != EINPROGRESS) {
            perror("Connection failed");
            close(sock_fd);
            return 1;
        }
    }

    // Create epoll instance
    epoll_fd = epoll_create1(0);
    if (epoll_fd == -1) {
        perror("epoll_create1 failed");
        close(sock_fd);
        return 1;
    }

    // Add socket to epoll
    struct epoll_event event;
    event.events = EPOLLIN | EPOLLOUT | EPOLLET;  // Monitor for read & write
    event.data.fd = sock_fd;
    epoll_ctl(epoll_fd, EPOLL_CTL_ADD, sock_fd, &event);

    std::cout << "Client connected to server at " << SERVER_IP << ":" << SERVER_PORT << std::endl;

    char buffer[1024];
    int message_count = 1;

    while (true) {
        struct epoll_event events[MAX_EVENTS];
        int num_events = epoll_wait(epoll_fd, events, MAX_EVENTS, 1000); // Timeout: 1000ms

        for (int i = 0; i < num_events; ++i) {
            int fd = events[i].data.fd;

            if (events[i].events & EPOLLOUT) {  // Ready to send
                std::string msg = "Message " + std::to_string(message_count);
                send(fd, msg.c_str(), msg.size(), 0);
                std::cout << "Sent: " << msg << std::endl;
                message_count++;
            }

            if (events[i].events & EPOLLIN) {  // Ready to receive
                int bytes_received = recv(fd, buffer, sizeof(buffer) - 1, 0);
                if (bytes_received > 0) {
                    buffer[bytes_received] = '\0';
                    std::cout << "Received: " << buffer << std::endl;
                } else {
                    std::cout << "Server closed connection." << std::endl;
                    close(fd);
                    close(epoll_fd);
                    return 0;
                }
            }
        }

        // Sleep for 1 second before sending the next message
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    close(sock_fd);
    close(epoll_fd);
    return 0;
}

