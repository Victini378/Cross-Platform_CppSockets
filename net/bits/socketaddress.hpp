#ifndef SOCKET_ADDRESS_H
#define SOCKET_ADDRESS_H


#ifdef _WIN32
	#ifndef _WIN32_WINNT
		#define _WIN32_WINNT 0x0501  /* Windows XP. */
	#endif
	#include <winsock2.h>
	#include <Ws2tcpip.h>
	#include "strlcpy.c"
#else
	#include <netinet/in.h>
	#include <arpa/inet.h>
#endif

#include <string>
#include <cstring>

namespace net {
	class socketaddress {
		protected:
			int port;
			std::string address;

		public:
			/**
			 * Creates a new socketaddress instance based on a sockaddr_in structure
			 * @param the sockaddr_in structure
			 */
			socketaddress(struct sockaddr_in addr) {
				port = addr.sin_port;

				char ip[INET_ADDRSTRLEN];
			
				inet_ntop(addr.sin_family, &(addr.sin_addr), ip, INET_ADDRSTRLEN);
				
				address = std::string(ip);
			}

			/**
			 * Creates a new socketaddress instance with a specified address and port
			 * @param the address of the socket
			 * @param the port
			 */
			socketaddress(std::string address, int port) {
				this->address = address;
				this->port = port;
			}

			/**
			 * Returns a sockaddr_in structure based on the information of the socketaddress instance
			 * @return sockaddr_in structure
			 */
			struct sockaddr_in get_struct();

			/**
			 * Gets the port of the socket
			 * @return the port number
			 */
			int get_port();

			/**
			 * Gets the address of the socket
			 * @return the address
			 */
			std::string get_address();
	};
};
#endif
