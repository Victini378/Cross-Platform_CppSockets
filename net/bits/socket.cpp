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
	inline void net::socket::set_blocking() {
		unsigned long opts = 0;
		ioctlsocket(socketfd, FIONBIO, &opts);
	}

	inline void net::socket::set_unblocking() {
		unsigned long opts = 1;
		ioctlsocket(socketfd, FIONBIO, &opts);
	}
#else
	inline void net::socket::set_blocking() {
		int opts = fcntl(socketfd, F_GETFL);
		opts = opts & (~O_NONBLOCK);
		fcntl(socketfd, F_SETFL, opts);
	}

	inline void net::socket::set_unblocking() {
		fcntl(socketfd, F_SETFL, O_NONBLOCK);
	}
#endif


inline std::string net::socket::read() {
	std::string response;
	net::socket::read(response);
	return response;
}

int net::socket::read(std::string& msg) {
	int bytes_total = 0;
	char buffer[DEFAULT_SOCKET_BUFFER];

	int bytes_read = recv(socketfd, buffer, DEFAULT_SOCKET_BUFFER, 0);

	if (bytes_read <= 0)
		return bytes_read;

	msg.append(std::string(buffer, 0, bytes_read));
	bytes_total += bytes_read;

	set_unblocking();


	while (bytes_read > 0) {
		memset(buffer, 0, DEFAULT_SOCKET_BUFFER);
		bytes_read = recv(socketfd, buffer, DEFAULT_SOCKET_BUFFER, 0);

		if (bytes_read < 0)
			break;

		msg.append(std::string(buffer, 0, bytes_read));
		bytes_total += bytes_read;
	}

	set_blocking();

	return bytes_total;
}

inline int net::socket::read(char* buf, const int len) {
	return ::recv(socketfd, buf, len, 0);
}

inline int net::socket::sendln(std::string const& data) {
	return send(data + '\n');
}

inline int net::socket::send(std::string const& data) {
	return send(data.c_str(), data.length(), 0);
}

inline int net::socket::send(const char* buf, const int len, const int flags) {
	return ::send(socketfd, buf, len, flags);
}

int net::socket::connect(std::string const& address, const int port) {
	this->address = new socketaddress(address, port);

	struct sockaddr_in servaddr = this->address->get_struct();
     
    if (::connect(socketfd, (struct sockaddr*)&servaddr, sizeof(struct sockaddr)) < 0)
        return CONNECT_ERROR;
    
    return 0;
}

inline SOCKET net::socket::get_socket() {
	return socketfd;
}

inline net::socketaddress* net::socket::get_socketaddress() {
	return address;
}

inline bool net::socket::valid() {
#ifdef _WIN32
	return socketfd != INVALID_SOCKET;
#else
	return socketfd != -1;
#endif
}

inline void net::socket::close() {
#ifdef _WIN32
	::closesocket(socketfd);
#else
	if (socketfd == -1)
		return;

	::close(socketfd);
#endif
}