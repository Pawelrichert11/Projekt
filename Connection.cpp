#ifndef connection_h
#define connection_h 
#include "Connection.hpp"

Connection::Connection()
{
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
		fprintf(stderr, "socket error: %s\n", strerror(errno)); 
	}
	bzero (&serverAddr, sizeof(serverAddr));
	serverAddr.sin_family      = AF_INET;
	serverAddr.sin_port        = htons(54321);
	serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	if (bind (sockfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
		fprintf(stderr, "bind error: %s\n", strerror(errno)); 
	}
}
Connection::~Connection()
{
    close(sockfd);
}
#endif