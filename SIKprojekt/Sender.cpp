#include "Sender.hpp"

Sender::Sender(const char* ip_addr )
{ 
	/* uzupełnianie struktury adresata */
	bzero( &destination, sizeof( destination ) );
	destination.sin_family = AF_INET;
    destination.sin_port = htons(54321);
	if( inet_pton( AF_INET, ip_addr, &destination.sin_addr ) != 1 )
    {
        throw std::runtime_error( "incorrect address" );
    }
}

void Sender::send_packet(const int& sockfd, char* packet)
{
    std::cout<<"fix this";
    /*
    int len = 9;
    if (sendto(sockfd, packet, len, 0, (struct sockaddr*)&destination, destinationLength) != len) {
		fprintf(stderr, "sendto error: %s\n", strerror(errno)); 
	}
    else
    {
        std::cout<<"packet send"<<std::endl;
    }
    */
}
void Sender::send_packet(const int& sockfd,const char* ipAddress, char* packet)
{
    struct sockaddr_in differentDestination;
    socklen_t differentDestinationLength = sizeof(differentDestination);
    bzero( &differentDestination, sizeof( differentDestination ) );
	differentDestination.sin_family = AF_INET;
    differentDestination.sin_port = htons(54321);
	if( inet_pton( AF_INET, ipAddress, &differentDestination.sin_addr ) != 1 )
    {
        throw std::runtime_error( "incorrect address" );
    }
    if (sendto(sockfd, packet, 9, 0, (struct sockaddr*)&differentDestination, differentDestinationLength) != 9) {
		fprintf(stderr, "sendto error: %s\n", strerror(errno)); 
	}
}