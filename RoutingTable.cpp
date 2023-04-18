#include "RoutingTable.hpp"


RoutingTable::RoutingTable()
{
    emptyRoute = {"",0,"",0};
}
void RoutingTable::printRoute()
{
    for(auto g : table)
    {
        std::cout<<g.ipAddress<<"/"<<(int)g.ipAddressMask;
        if(g.distance == UINT32_MAX)
        {
            std::cout<<" unreachable ";
        }
        else
        {
            std::cout<<" distance "<<g.distance;
        }
        
        if(g.crossingIpAddress == "direct")
        {
            std::cout<<" connected directly";
        }
        else
        {
            std::cout<<" via "<<g.crossingIpAddress;
        }
        std::cout<<std::endl;
    }
}
void  RoutingTable::readArguments()
{
    int n;
    std::cin >> n;

    for (int i = 0; i < n; i++)
    {
        std::string ipAddress;
        uint32_t distance;
        std::string temp;
        uint8_t mask;

        std::cin >> ipAddress >> temp >> distance;

        size_t pos = ipAddress.find('/');
        mask = std::stoi(ipAddress.substr(pos + 1));
        ipAddress = ipAddress.substr(0, pos);

        char* charStr = new char[ipAddress.length() + 1];
        std::strcpy(charStr, ipAddress.c_str());
        ipAddresses.push_back(charStr);
        table.push_back({ipAddress,mask,"direct",distance});
    }
}
void checkConnection(){
    //jezeli przez trzy tury nie dostalismy pakietu z danego adresu to usuwamy ten adres
}
void RoutingTable::convertToUdpPacket(const char* ipAddress,uint8_t netmask, uint32_t distance,char *message) {
        struct in_addr address;
        inet_aton(ipAddress, &address);
    *(uint32_t *)message  = address.s_addr;
    //*reinterpret_cast<uint32_t*>(message) = address.s_addr;
    message[4] = netmask;
    distance = htonl(distance >= 16 ? INT_MAX : distance);//tutaj wsm nie wiem czemu maks 16 jest
    for (int i = 0; i < 4; i++) {
        *(message + 5 + i) = *((char *)(&distance) + i); 
    }
}
void RoutingTable::convertFromUdpPacket(const char* message, char* ipAddress, uint8_t& netmask, uint32_t& distance) {
    uint32_t ipAddressInt = *(uint32_t *)message;
    struct in_addr address;
    address.s_addr = ipAddressInt;
    const char* ipAddressStr = inet_ntoa(address);
    std::strcpy(ipAddress, ipAddressStr);
    netmask = *(uint8_t *)(message + 4);
    distance = ntohl(*(uint32_t *)(message + 5));
    distance = distance == INT_MAX ? 16 : distance;
}
Route& RoutingTable::routeToDestination(std::string dest)//ta funkcja zwraca nam połączenie do adresu albo emptyRoute
{
    for(auto& g : table)
    {
        if(dest == g.ipAddress)
        {
            return g;
        }
    }
    return emptyRoute;
}
void RoutingTable::print_data(char data[9]){
    for (int i = 0; i < 9; i++) {
        printf("%02X ", data[i]);
    }
    printf("\n");
}
bool RoutingTable::eq(Route& r1, Route& r2)
{
    if(r1.ipAddress == r2.ipAddress)//
    {
       return true;
    }
    else
    {
       return false;
    }
}
Route RoutingTable::decomposePacketToRoute(std::string sender, char* buffer)
{
    char destinationAddress[20];
    uint8_t netmask;
    uint32_t distance;
    convertFromUdpPacket(buffer,destinationAddress,netmask,distance);
    std::string str(destinationAddress, destinationAddress + std::strlen(destinationAddress));
    return {str,netmask,"direct",distance};
}
void RoutingTable::EraseElementFromTable(Route element)
{
    auto it = std::find_if(table.begin(), table.end(), [&](Route& e){ return eq(e, element); });
    if (it != table.end()) {
        table.erase(it);
    }
    auto it2 = std::find_if(ipAddresses.begin(), ipAddresses.end(), [&](const std::string& e){ return e == element.ipAddress; });
    if (it2 != ipAddresses.end()) {
        ipAddresses.erase(it2);
    }
}
void RoutingTable::actualizeRoute(std::string sender, char* buffer)
{
    Route newRoute = decomposePacketToRoute(sender,buffer);//to jest ścieżka od sendera do destination
    Route routeToSender = routeToDestination(sender);//to jest ścieżka do adresu od którego mamy pakiet
    Route ourRouteToDestination = routeToDestination(newRoute.ipAddress); //to jest nasza ścieżka do destination albo pusta ścieżka

    if(eq(ourRouteToDestination,emptyRoute)) //nie mamy tego połącznia
    {
        table.push_back({newRoute.ipAddress,newRoute.ipAddressMask,sender,newRoute.distance});
        ipAddresses.push_back(strdup(newRoute.ipAddress.c_str()));
    }
    else //tu sprawdzamy, czy opłaca nam się dodać ścieżkę przez nowego sendera
    {
        if((newRoute.distance + routeToSender.distance) < ourRouteToDestination.distance)
        {
            
            EraseElementFromTable(ourRouteToDestination);
            table.push_back({newRoute.ipAddress,newRoute.ipAddressMask,sender,newRoute.distance + routeToSender.distance});
            ipAddresses.push_back(strdup(newRoute.ipAddress.c_str()));
        }
    }
}
std::vector<char*> RoutingTable::getUdpPackets()
{
    std::vector<char*> packets;
    for(Route g : table)
    {
        char buffer[9];
        convertToUdpPacket(g.ipAddress.c_str(),g.ipAddressMask,g.distance,buffer);
        print_data(buffer);
        char* packet_copy = new char[9];
        std::memcpy(packet_copy, buffer, 9);
        packets.push_back(packet_copy);
    }
    return packets;
}
/*
PLAN AKCJI:
* ogarnąć, czy dobrze konwertujemy 
* ogarnąć plik makefile
* ogarnąć convert from udp zeby nie robilo od tylu
* ogarnąc linkowanie plików
* refactoring
* wykomentować wszystko
* obsługa wyjątków
* ogarnąć zarządzanie pamięcią
* zrefaktorować convertToUdpPacket
*/