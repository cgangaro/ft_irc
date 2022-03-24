#ifndef _CLIENT_H
#define _CLIENT_H

#include "Commons.hpp"
#include <vector>

class Client {
	private:
		SOCKET _socket;
		SOCKADDR_IN _sin;
		bool _isAuthenticated;

		std::string _username;
		std::string _password;
		std::string _nickname;
		std::vector<std::string> _channels; // a string beginning with #


	public:
		Client();
		Client(Client const &src);
		Client(SOCKET sock, SOCKADDR_IN sin);
		virtual ~Client();

		Client &operator=(Client const &rhs);
		SOCKET getSocket(void) const;
		bool isAuthenticated(void) const;
		SOCKADDR_IN getSin(void) const;

		char* getAddress(void) const;
		int getPort(void) const;
		std::string getUsername(void) const;
		std::string getPassword(void) const;
		std::string getNickname(void) const;
		std::vector<std::string> getChannels(void) const;

		void setPassword(std::string password);
		void setUsername(std::string username);
		void setNickname(std::string nickname);
		void setSocket(SOCKET socket);
		void addChannel(std::string channel);
};

#endif