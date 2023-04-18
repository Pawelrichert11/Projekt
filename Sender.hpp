#include "Tools.hpp"

class Sender
{
private:
	struct sockaddr_in destination;
    socklen_t destinationLength = sizeof(destination);
	//struct icmphdr create_icmphdr( int echo_id, int echo_seq );
public:
	Sender(const char* ip_addr );
	void send_packet(const int& socket, char* packet);
	void send_packet(const int& sockfd,const char* ip, char* packet);
};