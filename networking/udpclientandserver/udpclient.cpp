#include <bits/stdc++.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 

#include <string>
#include <thread>
#include <cstdlib>
   
#define PORT     8080 
#define MAXLINE 1024 
   
// Driver code 
int main() { 
    int sockfd; 
    char buffer[MAXLINE]; 
    struct sockaddr_in     servaddr; 
   
    // Creating socket file descriptor 
    if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) { 
        perror("socket creation failed"); 
        exit(EXIT_FAILURE); 
    } 
   
    memset(&servaddr, 0, sizeof(servaddr)); 
       
    // Filling server information 
    servaddr.sin_family = AF_INET; 
    servaddr.sin_port = htons(PORT); 
    servaddr.sin_addr.s_addr = INADDR_ANY; 
       
    int n;
    socklen_t len; 
      
		int seqNo{1};
		for (;;) 
		{
			std::string mesg="seq:" + std::to_string(seqNo++);
			std::this_thread::sleep_for(std::chrono::seconds(1));
    	sendto(sockfd, (const char *)mesg.c_str(), strlen(mesg.c_str()), MSG_CONFIRM, (const struct sockaddr *) &servaddr,  sizeof(servaddr)); 
    	n = recvfrom(sockfd, (char *)buffer, MAXLINE,  MSG_WAITALL, (struct sockaddr *) &servaddr, &len); 
    	buffer[n] = '\0'; 
    	std::cout<<"Server :"<<buffer<<std::endl; 
		}
   
    close(sockfd); 
    return 0; 
}
