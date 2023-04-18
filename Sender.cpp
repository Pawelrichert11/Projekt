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
uint32_t ipToUint(std::string ipAddr) {
    struct in_addr addr;
    inet_pton(AF_INET, ipAddr.c_str(), &addr);
    return ntohl(addr.s_addr);
}
std::string broadcastAddress(const std::string ipAddress) {
	size_t pos = ipAddress.find('/');
    int mask = std::stoi(ipAddress.substr(pos + 1));
    std::string ipAddr = ipAddress.substr(0, pos);

    uint32_t ip = ipToUint(ipAddr);
    uint32_t subnet = (0xFFFFFFFF << (32 - mask));
    uint32_t broadcast = ip | ~subnet;
    struct in_addr addr;
    addr.s_addr = htonl(broadcast);
    return std::string(inet_ntoa(addr));
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
void Sender::send_packet(const int& sockfd,const char* ip, char* packet)
{
    std::string str(ip);
    const char* ipAddress = broadcastAddress(str).c_str();
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