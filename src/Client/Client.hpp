#ifndef _CLIENT_H
#define _CLIENT_H

#include "Commons.hpp"
#include "User.hpp"

class Client {
	private:
		SOCKET _socket;
		SOCKADDR_IN _sin;
		bool _isAuthenticated;

	public:
		User _data;
		Client();
		Client(Client const &src);
		Client(SOCKET sock, SOCKADDR_IN sin);
		virtual ~Client();

		Client &operator=(Client const &rhs);
		SOCKET getSocket(void) const;
		User getUser(void) const;
		bool isAuthenticated(void) const;
		SOCKADDR_IN getSin(void) const;

		char* getAddress(void) const;
		int getPort(void) const;
};

#endif