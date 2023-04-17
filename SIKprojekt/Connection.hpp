#include "Tools.hpp"

class Connection
{
    public:
    int sockfd;
    struct sockaddr_in serverAddr;
    socklen_t addrLen;

    Connection();
    ~Connection();
};
