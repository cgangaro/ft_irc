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
		TCPClient(TCPClient const &src);
		TCPClient(SOCKET sock, SOCKADDR_IN sin);
		virtual ~TCPClient();

		TCPClient &operator=(TCPClient const &rhs);
		SOCKET getSocket(void) const;
		User getUser(void) const;
		bool isAuthenticated(void) const;
		SOCKADDR_IN getSin(void) const;

		char* getAddress(void) const;
		int getPort(void) const;
};

#endif