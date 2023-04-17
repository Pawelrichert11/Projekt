#include "Tools.hpp"

struct Route
{
    std::string ipAddress;
    uint8_t ipAddressMask;
    std::string crossingIpAddress;
    uint32_t distance;
};

class RoutingTable
{
    public:
    void printRoute();
    void readArguments();
    void actualizeRoute(std::string sender,char* buffer);
    void convertToUdpPacket(const char* ipAddress,uint8_t netmask, uint32_t distance,char *message);
    void convertFromUdpPacket(const char* message, char* ipAddress, uint8_t& netmask, uint32_t& distance);

    RoutingTable();

    std::vector<char*>getUdpPackets();
    std::vector<char*> ipAddresses;

    void print_data(char data[9]);

    private:
    std::vector<Route> table;
    Route& routeToDestination(std::string dest);
    Route decomposePacketToRoute(std::string sender, char* buffer);
    bool eq(Route& r1, Route& r2);
    void EraseElementFromTable(Route element);
    Route emptyRoute;

};