#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <iostream>
#include <string>
#include <thread>
#include <chrono>

void error(const char *msg)
{
    perror(msg);
    exit(0);
}

int main(int argc, char *argv[])
{
    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;

    char buffer[256];
    if (argc < 3) {
       fprintf(stderr,"usage %s hostname port\n", argv[0]);
       exit(0);
    }
    portno = atoi(argv[2]);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) 
        error("ERROR opening socket");
    server = gethostbyname(argv[1]);
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }

    serv_addr.sin_family = AF_INET;
    memcpy((char *)&serv_addr.sin_addr.s_addr, (char *)server->h_addr, server->h_length);
    serv_addr.sin_port = htons(portno);


    if (connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) 
        error("ERROR connecting");

    bool done{false};
    int count{0};
    while(!done){
			int pid=getpid();
    	std::string buf = "from client "+ std::to_string(pid) + " =>" + std::to_string(count);
	    buffer[buf.size()]=0;	
			strcpy(buffer, buf.c_str());
    	n = write(sockfd, buffer, buf.size());
    	if (n < 0) 
         	error("ERROR writing to socket");
    	n = read(sockfd, buffer, 255);
    	if (n < 0) 
         	error("ERROR reading from socket");
			count++;
			if (count>10) done=true;
			std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    return 0;
}
