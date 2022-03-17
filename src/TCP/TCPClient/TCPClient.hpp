#ifndef TCP_CLIENT_H
#define TCP_CLIENT_H

#include "TCPCommons.hpp"
#include "User.hpp"

class TCPClient {
	private:
		SOCKET _socket;
		SOCKADDR_IN _sin;
		bool _isAuthenticated;
		User _data;

	public:
		TCPClient();
		TCPClient(SOCKET sock, SOCKADDR_IN sin);
		~TCPClient();

		char* getAddress(void) const;
		int getPort(void) const;
		SOCKET getSocket(void) const;
		bool isAuthenticated(void) const;
};

#endif