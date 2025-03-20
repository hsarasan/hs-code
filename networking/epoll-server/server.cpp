#include <iostream>
#include <sys/epoll.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <vector>
#include <string>

#define MAX_EVENTS 10
#define PORT 8080

// Function to set a socket to non-blocking mode
void set_nonblocking(int sock) {
    int flags = fcntl(sock, F_GETFL, 0);
    fcntl(sock, F_SETFL, flags | O_NONBLOCK);
}

int main() {
    int server_fd, new_socket, epoll_fd;
    struct sockaddr_in address;
    socklen_t addr_len = sizeof(address);

    // Create socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        perror("Socket failed");
        return 1;
    }

    // Set socket options
    int opt = 1;
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    // Bind the socket
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);
    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        return 1;
    }

    // Set the socket to listen
    if (listen(server_fd, SOMAXCONN) < 0) {
        perror("Listen failed");
        return 1;
    }

    // Set socket to non-blocking mode
    set_nonblocking(server_fd);

    // Create epoll instance
    epoll_fd = epoll_create1(0);
    if (epoll_fd == -1) {
        perror("epoll_create1 failed");
        return 1;
    }

    // Register server socket with epoll
    struct epoll_event event;
    event.events = EPOLLIN;  // Ready to read
    event.data.fd = server_fd;
    epoll_ctl(epoll_fd, EPOLL_CTL_ADD, server_fd, &event);

    std::vector<epoll_event> events(MAX_EVENTS);

    std::cout << "Server listening on port " << PORT << std::endl;

    while (true) {
        // Wait for events
        int num_events = epoll_wait(epoll_fd, events.data(), MAX_EVENTS, -1);
        if (num_events == -1) {
            perror("epoll_wait failed");
            break;
        }

        for (int i = 0; i < num_events; ++i) {
            int fd = events[i].data.fd;

            if (fd == server_fd) {  // New connection
                new_socket = accept(server_fd, (struct sockaddr*)&address, &addr_len);
                if (new_socket >= 0) {
                    set_nonblocking(new_socket);

                    struct epoll_event client_event;
                    client_event.events = EPOLLIN | EPOLLET;  // Edge-triggered
                    client_event.data.fd = new_socket;
                    epoll_ctl(epoll_fd, EPOLL_CTL_ADD, new_socket, &client_event);

                    std::cout << "New connection accepted: FD " << new_socket << std::endl;
                }
            } else {  // Data available on client socket
                char buffer[1024] = {0};
                int bytes_read = read(fd, buffer, sizeof(buffer));
                if (bytes_read > 0) {
                    std::cout << "Received from FD " << fd << ": " << buffer << std::endl;
										std::string resp("Ack");
										write(fd,resp.c_str(),resp.size());
                } else {
                    std::cout << "Closing connection: FD " << fd << std::endl;
                    close(fd);
                    epoll_ctl(epoll_fd, EPOLL_CTL_DEL, fd, nullptr);
                }
            }
        }
    }

    close(server_fd);
    close(epoll_fd);
    return 0;
}

