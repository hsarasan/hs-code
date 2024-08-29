#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>

int main(int argc, char * argv[]) {
		if (argc<2){
			std::cout<<argv[0]<<" <hostname> "<<std::endl;
			exit(1);
		}
    int sock = 0;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    const char* hostname = argv[1];
    std::string message= "GET / HTTP/1.1\r\nHost: " + std::string(hostname)  + "\r\nConnection: close\r\n\r\n";
    const char* request = message.c_str();
    char buffer[4096] = {0};

    // Create socket
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        std::cerr << "Socket creation error" << std::endl;
        return -1;
    }

    // Get server information by hostname
    server = gethostbyname(hostname);
    if (server == nullptr) {
        std::cerr << "No such host: " << hostname << std::endl;
        return -1;
    }

    // Define server address
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(80);  // HTTP port

    // Copy the server's address to the serv_addr structure
    std::memcpy(&serv_addr.sin_addr.s_addr, server->h_addr, server->h_length);

    // Connect to the server
    if (connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        std::cerr << "Connection Failed" << std::endl;
        return -1;
    }

    // Send the HTTP GET request
    send(sock, request, strlen(request), 0);
    std::cout << "HTTP GET request sent" << std::endl;

    // Read the server's response
		int totalbytes=0;
    int bytesRead;
    while ((bytesRead = read(sock, buffer, sizeof(buffer) - 1)) > 0) {
        buffer[bytesRead] = '\0';  // Null-terminate the buffer
        std::cout << buffer;
				totalbytes+=bytesRead;
    }
		std::cout<<"Total bytes read = "<<totalbytes<<std::endl;
	

    // Close the socket
    close(sock);

    return 0;
}

