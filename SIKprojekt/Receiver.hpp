#include "Tools.hpp"
class Receiver
{
private:
	struct sockaddr_in serv_addr;
    socklen_t sender_len;
public:
	Receiver(int& sockfd);
    void receive_packet(int& sockfd, char *buffer,std::string& outputSender);
    //u_int8_t buffer[IP_MAXPACKET+1];
};