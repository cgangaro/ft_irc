#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include <string>
#include <vector>
#include "Client.hpp"

struct channelUser {
	std::string nickname;
	bool		op;
	bool		voice;
	bool		creator;
};

class Channel {
	private:
		std::string _name;
		std::string _password;
		std::vector<channelUser> _userList;
		std::vector<std::string> _banAddress;

		int _modeSettings;
		int _maxUsers;

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
		int getModeSettings_operator(void) const;
		int getMaxUsers(void) const;

		void setName(std::string username);
		void setPassword(std::string password);
		void setMaxUsers(std::string max);
		void addMode(int mode);
		void removeMode(int mode);

		void addUser(std::string user);
		void removeUser(std::string user);

		void addBanAddress(std::string banAddress);
		void removeBanAddress(std::string banAddress);
	
		void setUserOp(std::string user, bool activ);
		void setUserVoice(std::string user, bool activ);
		void setUserCreator(std::string user, bool activ);

		bool verifIfRegisteredAdmin(std::string admin);
		bool verifIfRegisteredUser(std::string user);
		bool isOperator(std::string user);
		bool isCreator(std::string user);
		bool canUserSpeak(std::string user);
		bool isBan(std::string address);
};

#endif