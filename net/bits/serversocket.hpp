#ifndef SERVERSOCKET_H
#define SERVERSOCKET_H

#include "socket.hpp"

namespace net {
	class serversocket {
		private:
			#ifdef _WIN32
			void init() {
				WSADATA wsa_data;
				WSAStartup(MAKEWORD(2,2), &wsa_data);
			}
			#endif

		protected:
			int port;
			int backlog;
			std::string address;

			SOCKET socketfd;

		public:

			/**
			 * Constructs a listening socket on the specified port.
			 * The default address is 0.0.0.0 and the default backlog is 10.
			 *
			 * @param the port to listen to
			 */
			serversocket(const int port) {
			#ifdef _WIN32
				init();
			#endif
				this->port = port;
				backlog = 10;
				address = "0.0.0.0";
			}

			/**
			 * Constructs a listening socket on the specified port with a backlog.
			 * The default address is 0.0.0.0.
			 *
			 * @param the port to listen to
			 * @param the number of backlogs
			 */
			serversocket(const int port, const int backlog) {
			#ifdef _WIN32
				init();
			#endif
				this->port = port;
				this->backlog = backlog;
				address = "0.0.0.0";
			}

			/**
			 * Constructs a listening socket on the specified port and address
			 * @param the port to listen to
			 * @param the number of backlogs
			 * @param the address to bind to
			 */
			serversocket(const int port, const int backlog, std::string const& address) {
			#ifdef _WIN32
				init();
			#endif
				this->port = port;
				this->backlog = backlog;
				this->address = address;
			}

			virtual ~serversocket();

			/**
			 * Creates the listening socket and binds to the current port and address
			 * @return error code if there was a problem
			 */
			int listen();

			/**
			 * Accepts a new incomming client (blocking call).
			 * @return A client socket instance
			 */
			net::socket* accept();

			/**
			 * Closes the listening socket
			 */
			inline void close();

			/**
			 * Checks whether or not the socket is valid
			 * @return true the socket is valid, false otherwise
			 */
			inline bool valid();

			/**
			 * Gets the socket file descriptor
			 * @return the socket file descriptor
			 */
			inline SOCKET get_socket();
	};
};

#endif
