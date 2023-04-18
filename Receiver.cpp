#include "Receiver.hpp"

Receiver::Receiver(int& sockfd)
{
	bzero (&serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(54321);
	sender_len = sizeof(serv_addr);
	if (bind (sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
		fprintf(stderr, "bind error: %s\n", strerror(errno)); 
	}

}
void print_data(char* data){
    for (int i = 0; i < 9; i++) {
        printf("%02X ", data[i]);
    }
    printf("\n");
}
void Receiver::receive_packet(int& sockfd, char* buffer, std::string& outputSender)
{
	memset(buffer, 0, 9);
	ssize_t datagram_len = recvfrom (sockfd, buffer, 9, 0, (struct sockaddr*)&serv_addr, &sender_len);
	if (datagram_len < 0) {
		fprintf(stderr, "recvfrom error: %s\n", strerror(errno)); 
	}
	char sender_ip_str[20];
	inet_ntop(AF_INET, &(serv_addr.sin_addr), sender_ip_str, sizeof(sender_ip_str));

	outputSender = sender_ip_str;
	printf ("\nReceived UDP packet from IP address: %s, port: %d packet: ", sender_ip_str, ntohs(serv_addr.sin_port));
	print_data(buffer);
}