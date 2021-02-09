#include <net/serversocket>
#include <net/socket>

#include <iostream>
#include <string>

int main() {
    net::serversocket* server = new net::serversocket(8002);
    int err = server->listen();

    if (err != 0) {
        std::cerr << strerror(err) << std::endl;
        exit(err);
    }

    while (true) {
        std::clog << "Listening" << std::endl;
        net::socket* client = server->accept();
        client->sendln("Ciao");

        client->close();
        
        if (!client->valid()) {
            delete client;
            std::cout << "Ciao" << std::endl;
        }
    }
}