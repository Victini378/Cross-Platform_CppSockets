#include "net/socket"

#include <iostream>
#include <string>

int main(const int argc, char const** argv) {
    net::socket* server = new net::socket();
    const char* address = argc < 2 ? "127.0.0.1" : argv[1];
    const int port = argc < 3 ? 8002 : std::atoi(argv[2]);

    std::cout << "Welcome to Factorial Client!\n" << std::endl;

    std::cerr << "Client[Info]: Trying " << address << " connection on " << port << " port..." << std::endl;
    
    if (server->connect(address, port) == CONNECT_ERROR) {
        std::cerr << "Client[Error]: " << server->get_socketaddress()->get_address() << " connection on " << server->get_socketaddress()->get_port() << " port lost\n";
        return CONNECT_ERROR;
    }

    std::cerr << "Client[Info]: " << server->get_socketaddress()->get_address() << " connection on " << server->get_socketaddress()->get_port() << " port successful" << std::endl;

    std::string number;
    std::string info;

    server->read(info);
    std::clog << "Server[Info]: " << info << std::flush;

    while (true) {
        std::string response;
        std::cout << "Number: ";
        std::getline(std::cin, number);

        server->sendln(number);

        if (number == "/quit")
            break;

        if (server->read(response) <= 0) {
            std::cerr << "Client[Error]: " << server->get_socketaddress()->get_address() << " connection on " << server->get_socketaddress()->get_port() << " port lost\n";
            return CONNECT_ERROR;
        }

        std::cout << "Factorial: " << response << std::endl;
    } server->close();
    
}