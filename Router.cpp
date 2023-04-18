#include "Tools.hpp"
#include "RoutingTable.cpp"
#include "Receiver.cpp"
#include "Sender.cpp"
#include "Connection.cpp"

int main()
{
	struct sockaddr_in serverAddr;
	int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if (sockfd < 0) {
		fprintf(stderr, "socket error: %s\n", strerror(errno)); 
		return EXIT_FAILURE;
	}
	const char* ip_address = "192.168.0.1";
	RoutingTable* routingTable= new RoutingTable();
	Sender* sender = new Sender(ip_address);
	Receiver* receiver = new Receiver(sockfd);
	//Connection* connector = new Connection();

    routingTable->readArguments();
	auto udpPackets = routingTable->getUdpPackets();
	while(true)
    {
		fd_set descriptors;
		FD_ZERO( &descriptors );
		FD_SET(sockfd, &descriptors );
		struct timeval tv; tv.tv_sec = 5 ; tv.tv_usec = 0;

		int ready = select(sockfd + 1, &descriptors, NULL, NULL, &tv);

		if(ready < 0)
		{
			throw std::runtime_error("Read from socket error");
		}
		if(ready == 0) 
		{
			routingTable->printRoute();
			for(char* udpPacket : udpPackets){
				for(auto ipAddress : routingTable->ipAddresses)
				{	
					sender->send_packet(sockfd,ipAddress,udpPacket);
				}
			}
		}
		else
		{
			char buffer[9];
			std::string sender;
			receiver->receive_packet(sockfd,buffer,sender);
			routingTable->actualizeRoute(sender,buffer);

		}
	}
	close(sockfd);
	delete routingTable;
	delete sender;
	delete receiver;
	return EXIT_SUCCESS;
}