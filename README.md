![logo](logo_github.png)


[![Windows Build](https://github.com/Victini378/Cross-Platform_CppSockets/workflows/Windows%20Build/badge.svg)](https://github.com/Victini378/Cross-Platform_CppSockets/actions?query=workflow%3A"Windows+Build")
[![Linux Build](https://github.com/Victini378/Cross-Platform_CppSockets/workflows/Linux%20Build/badge.svg)](https://github.com/Victini378/Cross-Platform_CppSockets/actions?query=workflow%3A"Linux+Build")
[![macOS Build](https://github.com/Victini378/Cross-Platform_CppSockets/workflows/macOS%20Build/badge.svg)](https://github.com/Victini378/Cross-Platform_CppSockets/actions?query=workflow%3A"macOS+Build")

## Creating a Server Socket

```

net::serversocket* server = new net::serversocket(8080);
int err = server->listen();

if (err != 0) {
    std::cerr << strerror(err) << std::endl;
    exit(err);
}

while (true) {
    net::socket* client = server->accept();
    
    if (!client->valid()) {
        delete client;
        continue;
    }
    
    std::string message;
    client->read(&message);
    std::cout << "Message: " << message << std::endl;
}

```

## Creating a Socket (TCP Client)

```

net::socket* client = new net::socket();

if (client->connect("127.0.0.1", 8002) == CONNECT_ERROR)
    std::cerr << "Problem with connection!\n";

client->sendln("Hello guys!");

std::cout << client->read() << std::endl;

```
