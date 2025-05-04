#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <cstring>
#include <sstream>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include "kafka_producer.h"

#define PORT 9000
#define BUFFER_SIZE 1024

// Helper to split string by delimiter
std::vector<std::string> split(const std::string& s, char delimiter) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(s);
    while (std::getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

int main() {
    // Create TCP socket
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("Socket creation failed");
        return 1;
    }

    sockaddr_in serv_addr{};
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    // Connect to Python server
    if (connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("Connection failed");
        return 1;
    }

    std::cout << "Connected to server on port " << PORT << "...\n";

    char buffer[BUFFER_SIZE];
		KafkaProducer kfq("localhost:9092","us-equities");

		ulong seq_no{0};
    while (true) {
        memset(buffer, 0, BUFFER_SIZE);
        ssize_t n = recv(sock, buffer, BUFFER_SIZE - 1, 0);
        if (n <= 0) {
            std::cerr << "Disconnected or error.\n";
            break;
        }

        std::string message(buffer, n);
        std::vector<std::string> tokens = split(message, ',');

        if (tokens.size() >= 6 && tokens[1] == "BID" && tokens[3] == "ASK") {
            std::string formatted = std::to_string(seq_no++)+","+tokens[0] + "," + tokens[2] + "," + tokens[4];
            std::cout << formatted << std::endl;
						kfq.send(formatted);
        } else {
            std::cerr << "Invalid message format: " << message << std::endl;
        }
    }

    close(sock);
    return 0;
}

