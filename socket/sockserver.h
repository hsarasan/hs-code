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

#include <algorithm>
#include <iostream>
#include <string>
#include <sstream>
#include <thread>
#include <vector>
#include <functional>

#define MAX 1024
#define BACKLOG 5

using namespace std;

namespace EV
{

	class ServerSocketHandler
	{
		fd_set fullFDSet;
		int listenFD;
		std::vector<int> client;
		std::function<std::string(std::string, int)> callback;

	public:
		void error(const char *msg)
		{
			perror(msg);
			exit(1);
		}
		ServerSocketHandler() : client(FD_SETSIZE, -1)
		{
			FD_ZERO(&fullFDSet);
		}

		int handleEvents()
		{
			int i, maxi, maxfd{5};
			int connfd, sockfd;
			int noFDsSet;
			ssize_t n; // size of buffer.
			fd_set fdSetCopy;
			char buf[MAX];

			socklen_t clilen;
			struct sockaddr_in serveraddr, clientaddr;
			FD_SET(listenFD, &fullFDSet); // i.e listenFD is available for connections.
			for (;;)
			{
				fdSetCopy = fullFDSet;
				if ((noFDsSet = select(maxfd + 1, &fdSetCopy, NULL, NULL, NULL)) < 0)
				{
					error("Error is select");
				}

				/* this is done for new connections */
				if (FD_ISSET(listenFD, &fdSetCopy)) /* new client has requested connection */
				{
					clilen = sizeof(clientaddr);
					if ((connfd = accept(listenFD, (struct sockaddr *)&clientaddr, &clilen)) < 0)
						error("accept error");

					for (i = 0; i < FD_SETSIZE; i++)
					{
						if (client[i] < 0)
						{
							client[i] = connfd;
							break;
						}
					}
					if (i == FD_SETSIZE)
						error("Too many clients, dropping the request.");
					FD_SET(connfd, &fullFDSet); /* add the new file descriptor to set */
					if (connfd > maxfd)
						maxfd = connfd;

					// to update max number of clients.
					if (i > maxi)
						maxi = i;

					/* i.e noFDsSet is the number of fds that are set(number of ready connections)
					  if its zero, then don't bother checking other fds, in set*/
					if ((--noFDsSet) <= 0)
						continue;
				}

				/* handle all the clients requesting */
				for (i = 0; i <= maxi; i++)
				{
					if ((sockfd = client[i]) < 0)
						continue;

					if (FD_ISSET(sockfd, &fdSetCopy))
					{
						if ((n = recv(sockfd, buf, MAX, 0)) == 0)
						{
							/* connection closed by client side */
							close(sockfd);
							FD_CLR(sockfd, &fullFDSet);
							client[i] = -1;
						}
						else
						{
							buf[n] = 0;
							std::string reply = callback(buf,sockfd);
							if (!reply.empty()){
								strcpy(buf, reply.c_str());
								send(sockfd, buf, reply.size(), 0);
							}
						}
						if (--noFDsSet < 0)
							break;
					}
				}
			}

			close(listenFD);
		}

		void listenAndCallback(const int portno, std::function<std::string(std::string, int)> f)
		{
			int i, maxi, maxfd;
			int connfd, sockfd;
			socklen_t clilen;
			struct sockaddr_in serveraddr, clientaddr;

			listenFD = socket(AF_INET, SOCK_STREAM, 0);
			if (listenFD < 0)
				error("ERROR opening socket");

			serveraddr.sin_family = AF_INET;
			serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
			serveraddr.sin_port = htons(portno);

			if (bind(listenFD, (struct sockaddr *)&serveraddr,
					 sizeof(serveraddr)) < 0)
				error("ERROR on binding");

			if (listen(listenFD, BACKLOG) < 0) /* allow 5 requests to queue up */
				error("ERROR on listen, or too many clients to handle.");

			callback = f;
			handleEvents();
		}
		void broadcast(std::string_view s, int exceptionFD) {
			char buf[256];
			strcpy(buf, std::string(s).c_str());
			std::for_each(client.begin(), client.end(), [&](int fd){
				if (fd!=-1 && fd!=exceptionFD){
					send(fd, buf, s.size(), 0);
				}
			});
		}
	};
};
