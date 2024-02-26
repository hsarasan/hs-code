#include <bits/stdc++.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <sys/select.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 

#include <string>
#include <thread>
#include <cstdlib>
   

#define MAXLINE 1024

class UDP
{
    struct sockaddr_in servaddr;
    int sockfd;
    void initUDP(int port)
    {
        char buffer[MAXLINE];
        // Creating socket file descriptor
        if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
        {
            perror("socket creation failed");
            exit(EXIT_FAILURE);
        }

        memset(&servaddr, 0, sizeof(servaddr));

        // Filling server information
        servaddr.sin_family = AF_INET;
        servaddr.sin_port = htons(port);
        servaddr.sin_addr.s_addr = INADDR_ANY;
    }
    public:

    void initClient(int port){
        return initUDP(port);
    }
    void initServer(int port)
    {
        initUDP(port);
        // Bind the socket with the server address
        if (bind(sockfd, (const struct sockaddr *)&servaddr,
                 sizeof(servaddr)) < 0)
        {
            perror("bind failed");
            exit(EXIT_FAILURE);
        }
    }
    std::string sendAndReceive(const std::string & mesg){
        sendto(sockfd, (const char *)mesg.c_str(), strlen(mesg.c_str()), MSG_CONFIRM, (const struct sockaddr *) &servaddr,  sizeof(servaddr)); 
        char buffer[256];
        socklen_t len;
    	int n = recvfrom(sockfd, (char *)buffer, MAXLINE,  MSG_WAITALL, (struct sockaddr *) &servaddr, &len); 
        buffer[n]=0;
        return std::string(buffer);
    }
    void send(const std::string & mesg){
        sendto(sockfd, (const char *)mesg.c_str(), strlen(mesg.c_str()), MSG_CONFIRM, (const struct sockaddr *) &servaddr,  sizeof(servaddr)); 
    }
    void setCallbackOnReceive(){
        fd_set fdSetToMonitor;
        FD_SET(sockfd, &fdSetToMonitor);
        for (;;){
            if (int nFD = select (sockfd+1, &fdSetToMonitor, NULL, NULL, NULL)<0 ){
                std::cerr<<"ERROR in select"<<std::endl;
                exit(1);
            }
            if (FD_ISSET(sockfd, &fdSetToMonitor)){
                char buffer[256];
                socklen_t len;
                int n = recvfrom(sockfd, (char *)buffer, MAXLINE,  MSG_WAITALL, (struct sockaddr *) &servaddr, &len); 
                buffer[n]=0;
                std::cout<<"Message Received "<<buffer<<std::endl;
            }
        }
    }

};
