#ifndef SOCKET_H
#define SOCKET_H

#include <string>
#include <cerrno>

#ifdef _WIN32
	#ifndef _WIN32_WINNT
		#define _WIN32_WINNT 0x0501  /* Windows XP. */
	#endif
	#include <winsock2.h>
	#include <Ws2tcpip.h>
#else
	#include <sys/socket.h>
	#include <sys/types.h>
	#include <netinet/in.h>
	#include <unistd.h>

	typedef int SOCKET;
#endif

#include "socketaddress.hpp"

#define HOSTNAME_ERROR -2
#define CONNECT_ERROR -3

namespace net {
	class socket {
		protected:
			SOCKET socketfd;
			socketaddress* address;

		public:
			/**
			 * Creates a socket instance
			 */
			socket() {
			#ifdef _WIN32
				WSADATA wsa_data;
				WSAStartup(MAKEWORD(2,2), &wsa_data);
				socketfd = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
			#else
				socketfd = ::socket(AF_INET, SOCK_STREAM, 0);
			#endif
				//if (socketfd == -1)
					//todo throw
			}

			/**
			 * Creates a socket instance based upon an already existing
			 * socket file descriptor and sockaddr_in structure.
			 * Used for example after a call to ::accept()
			 * @param the socket file descriptor
			 * @param the address structure
			 */
			socket(SOCKET socketfd, struct sockaddr_in addr) {
				this->socketfd = socketfd;
				address = new net::socketaddress(addr);
			}

			~socket();

			int connect(const std::string, int);

			/**
			 * Reads all data being sent from the client. The function will block until there's
			 * data, and then read the rest if any.
			 */
			std::string read();


			/**
			 * Reads all data being sent from the client. The function will block until there's
			 * data, and then read the rest if any.
			 * @param the string object to save the data into
			 */
			int read(std::string&);

			/**
			 * Reads a specified amount of data into a character pointer
			 * @param the character buffer
			 * @param the length of the character buffer
			 */
			int read(char*, const int);

			int sendln(const std::string);

			/**
			 * Sends a string to the client
			 * @param the string to send
			 */
			int send(const std::string);

			/**
			 * Sends an array of charactes to the client, with a specified start and end index
			 * @param the character buffer
			 * @param the starting position
			 * @param the length
			 */
			int send(const char*, const int, const int);

			/**
			 * Sets the socket in blocking mode
			 */
			void set_blocking();

			/**
			 * Sets the socket in non-blocking mode
			 */
			void set_unblocking();

			/**
			 * Closes the socket connection
			 */
			void close();

			/**
			 * Checks whether the socket is valid
			 * @return true if the socket is valid, false otherwise
			 */
			bool valid();

			/**
			 * Gets the socket file descriptor
			 * @return the socket file descriptor
			 */
			SOCKET get_socket();

			/**
			 * Gets the socketaddress instance of the socket, which contains
			 * information about the socket's address and port
			 * @return the socketaddress instance
			 */
			socketaddress* get_socketaddress();
	};
};

#endif
