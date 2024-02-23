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

namespace SC
{

  class SockClient
  {

    int sockFD;
    int port;
    std::string host;

    void error(const char *msg)
    {
      perror(msg);
      exit(0);
    }
    void initiateConnection()
    {
      struct sockaddr_in serv_addr;
      struct hostent *server;
      sockFD = socket(AF_INET, SOCK_STREAM, 0);
      if (sockFD < 0)
        error("ERROR opening socket");
      server = gethostbyname(host.c_str());
      if (server == NULL)
      {
        fprintf(stderr, "ERROR, no such host\n");
        exit(0);
      }
      std::cout << "Connecting to " << host << " " << port << std::endl;
      serv_addr.sin_family = AF_INET;
      memcpy((char *)&serv_addr.sin_addr.s_addr, (char *)server->h_addr, server->h_length);
      serv_addr.sin_port = htons(port);
      if (connect(sockFD, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
        error("ERROR connecting");
    }

  public:
    SockClient(const std::string &host_, int port_) : host(host_), port(port_)
    {
      initiateConnection();
    }

    void sendAndReceive(std::string_view s)
    {
			char buffer[256];
      int pid = getpid();
      buffer[s.size()] = 0;
      strcpy(buffer, std::string(s).c_str());
      int noBytesRead = write(sockFD, buffer, s.size());
      if (noBytesRead < 0)
          error("ERROR writing to socket");
      noBytesRead = read(sockFD, buffer, 255);
      buffer[noBytesRead] = 0;
      if (noBytesRead < 0)
          error("ERROR reading from socket");
      std::cout << "From Server [" << buffer << "]" << std::endl;
    }
    void sendMessage(std::string_view s)
    {
			char buffer[256];
      int pid = getpid();
      buffer[s.size()] = 0;
      strcpy(buffer, std::string(s).c_str());
      int noBytesRead = write(sockFD, buffer, s.size());
    }
  };
};
