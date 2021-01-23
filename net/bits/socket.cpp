#include "socket.hpp"

#include <string>
#include <fcntl.h>

#define DEFAULT_SOCKET_BUFFER 128

net::socket::~socket() {
	delete address;
	close();

	#ifdef _WIN32
		WSACleanup();
  	#endif
}

#ifdef _WIN32
	void net::socket::set_blocking() {
		unsigned long opts = 0;
		ioctlsocket(socketfd, FIONBIO, &opts);
	}

	void net::socket::set_unblocking() {
		unsigned long opts = 1;
		ioctlsocket(socketfd, FIONBIO, &opts);
	}
#else
	void net::socket::set_blocking() {
		int opts = fcntl(socketfd, F_GETFL);
		opts = opts & (~O_NONBLOCK);
		fcntl(socketfd, F_SETFL, opts);
	}

	void net::socket::set_unblocking() {
		fcntl(socketfd, F_SETFL, O_NONBLOCK);
	}
#endif


std::string net::socket::read() {
	std::string response;
	net::socket::read(response);
	return response;
}

int net::socket::read(std::string& msg) {
	int bytes_total = 0;
	char buffer[DEFAULT_SOCKET_BUFFER];

	int bytes_read = recv(socketfd, buffer, DEFAULT_SOCKET_BUFFER, 0);

	if (bytes_read <= 0) {
		return bytes_read;
	}

	msg.append(std::string(buffer, 0, bytes_read));
	bytes_total += bytes_read;

	set_unblocking();


	while (bytes_read > 0) {
		memset(buffer, 0, DEFAULT_SOCKET_BUFFER);
		bytes_read = recv(socketfd, buffer, DEFAULT_SOCKET_BUFFER, 0);

		if (bytes_read < 0) {
			break;
		}

		msg.append(std::string(buffer, 0, bytes_read));
		bytes_total += bytes_read;
	}

	set_blocking();


	return bytes_total;
}

int net::socket::read(char* buf, int len) {
	return ::recv(socketfd, buf, len, 0);
}

int net::socket::sendln(std::string data) {
	return send(data + '\n');
}

int net::socket::send(std::string data) {
	return send(data.c_str(), data.length(), 0);
}

int net::socket::send(const char* buf, int len, int flags) {
	return ::send(socketfd, buf, len, flags);
}

int net::socket::connect(std::string address, int port) {
	this->address = new socketaddress(address, port);

	struct sockaddr_in servaddr = this->address->get_struct();
     
    if (::connect(socketfd, (struct sockaddr*)&servaddr, sizeof(struct sockaddr)) < 0)
        return CONNECT_ERROR;
    
    return 0;
}