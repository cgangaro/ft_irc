#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include <string>
#include <vector>
#include "Client.hpp"

struct channelUser {
	std::string nickname;
	bool		op;
	bool		voice;
};

class Channel {
	private:
		std::string _name;
		std::string _password;
		std::vector<std::string> _list_admin;
		std::vector<std::string> _list_user;
		std::vector<channelUser> _userList;

		int _modeSettings;

	public:
		Channel();
		Channel(Channel const &src);
		Channel(std::string name, std::string password, std::string admin);
		~Channel();

		Channel &operator=(Channel const &rhs);

		std::string getName(void) const;
		std::string getPassword(void) const;
		std::vector<channelUser> getUserList(void) const;
		std::string getChannelmode();
		int getModeSettings(void);

		void setName(std::string username);
		void setPassword(std::string password);
		void addMode(int mode);
		void removeMode(int mode);

		void addUser(std::string user);
		void removeUser(std::string user);
	
		void setUserOp(std::string op, bool activ);

		bool verifIfRegisteredAdmin(std::string admin);
		bool verifIfRegisteredUser(std::string user);
		bool isOperator(std::string user);
};

#endif