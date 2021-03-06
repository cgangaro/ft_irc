#ifndef _CLIENT_H
#define _CLIENT_H

#include <vector>
#include "Commons.hpp"
#include "Channel.hpp"

class Channel;

class Client {
	private:
		SOCKET _socket;
		SOCKADDR_IN _sin;
		bool _isRegistered;
		bool _isAuthenticated;
		bool _isOperator;

		std::string _username;
		std::string _nickname;
		std::vector<std::string> _channels; // a string beginning with #

		std::string buffer;
		int _modeSettings;

	public:
		Client();
		Client(Client const &src);
		Client(SOCKET sock, SOCKADDR_IN sin);
		virtual ~Client();

		Client &operator=(Client const &rhs);
		SOCKET getSocket(void) const;
		bool isAuthenticated(void) const;
		bool isRegistered(void) const;
		bool isOperator(void) const;
		SOCKADDR_IN getSin(void) const;

		char* getAddress(void) const;
		int getPort(void) const;
		std::string getUsername(void) const;
		std::string getNickname(void) const;
		int getModeSettings(void) const;
		std::string getUsermode();
		std::string getSujet(void) const;
		const std::string & getBuffer(void) const;
		std::vector<std::string> getChannels(void) const;
		bool isInChannel(std::string channelName) const;

		void setBuffer(std::string buffer);
		void setUsername(std::string username);
		void setNickname(std::string nickname);
		void setSocket(SOCKET socket);
		void authenticate(void);
		void registerMe(void);
		void setOperator(bool isOperator);
		void addChannel(std::string channel);
		bool hasCommonChannel(Client Client);
		void addMode(int mode);
		void removeMode(int mode);

		void test_printChannels(void);
};

#endif
