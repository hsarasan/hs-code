#pragma once

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <thread>

#include <iostream>
#include <string>
#include <sstream>

#define MAX 1024
#define BACKLOG 5

using namespace std;

void error(const char *msg)
{
  perror(msg);
  exit(1);
}

int socketInit(int portno)
{
  int i, maxi, maxfd;
  int listenfd, connfd, sockfd;
  socklen_t clilen;
  struct sockaddr_in serveraddr, clientaddr;

  listenfd = socket(AF_INET, SOCK_STREAM, 0);
  if (listenfd < 0)
    error("ERROR opening socket");

  serveraddr.sin_family = AF_INET;
  serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
  serveraddr.sin_port = htons(portno);

  if (bind(listenfd, (struct sockaddr *)&serveraddr,
           sizeof(serveraddr)) < 0)
    error("ERROR on binding");

  if (listen(listenfd, BACKLOG) < 0) /* allow 5 requests to queue up */
    error("ERROR on listen, or too many clients to handle.");

  return listenfd;
}
