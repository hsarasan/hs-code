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

#define MAX 1024
#define BACKLOG 5

using namespace std;

namespace EV
{

	class ServerSocketHandler
	{
		fd_set allset;
		std::vector<int> client;

	public:

		void error(const char *msg)
		{
			perror(msg);
			exit(1);
		}
		ServerSocketHandler():client(FD_SETSIZE,-1)
		{
			FD_ZERO(&allset);
		}

		int handleEvents(int listenfd)
		{
			int i, maxi, maxfd{5};
			int connfd, sockfd;
			int nready;
			ssize_t n; // size of buffer.
			fd_set rset;
			char buf[MAX];

			socklen_t clilen;
			struct sockaddr_in serveraddr, clientaddr;
			FD_SET(listenfd, &allset); // i.e listenfd is available for connections.
			for (;;)
			{
				rset = allset;
				if ((nready = select(maxfd + 1, &rset, NULL, NULL, NULL)) < 0)
				{
					error("Error is select");
				}

				/* this is done for new connections */
				if (FD_ISSET(listenfd, &rset)) /* new client has requested connection */
				{
					clilen = sizeof(clientaddr);
					// This is not blocking, because we know for sure that someone is trying to
					// connect, as listenfd=1.
					if ((connfd = accept(listenfd, (struct sockaddr *)&clientaddr, &clilen)) < 0)
						error("accept error");

					/* find the first client[]=-1 */
					for (i = 0; i < FD_SETSIZE; i++)
					{
						if (client[i] < 0)
						{
							client[i] = connfd;
							break;
						}
					}

					// 'for loop' may break or run out of iterations.
					// Incase it runs out of iterations, that means

					// all spaces in client[] array has been filled.
					// In that case, just drop the request.
					if (i == FD_SETSIZE)
						error("Too many clients, dropping the request.");

					FD_SET(connfd, &allset); /* add the new file descriptor to set */

					// to increase the maxfdp1 value that goes in select().
					if (connfd > maxfd)
						maxfd = connfd;

					// to update max number of clients.
					if (i > maxi)
						maxi = i;

					/* i.e nready is the number of fds that are set(number of ready connections)
					  if its zero, then don't bother checking other fds, in set*/
					if ((--nready) <= 0)
						continue;
				}

				/* handle all the clients requesting */
				for (i = 0; i <= maxi; i++)
				{
					if ((sockfd = client[i]) < 0)
						continue;

					if (FD_ISSET(sockfd, &rset))
					{
						if ((n = recv(sockfd, buf, MAX, 0)) == 0)
						{
							/* connection closed by client side */
							close(sockfd);
							FD_CLR(sockfd, &allset);
							client[i] = -1;
						}
						else
						{
							buf[n] = 0;
							std::cout << "Received " << buf << " from client " << sockfd << std::endl;
							std::string reply("Ack from server => ");
							strcpy(buf, reply.c_str());
							send(sockfd, buf, reply.size(), 0);
						}
						if (--nready < 0)
							break;
					}
				}
			}

			close(listenfd);
		}
	};

};
