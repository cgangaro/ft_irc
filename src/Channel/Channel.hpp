#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include <string>
#include <vector>
#include "Client.hpp"

class Channel {
	private:
		std::string _name;
		std::string _password;
		std::vector<std::string> _list_admin;
		std::vector<std::string> _list_user;

		int _modeSettings;

	public:
		Channel();
		Channel(Channel const &src);
		Channel(std::string name, std::string password, std::string admin);
		~Channel();

		Channel &operator=(Channel const &rhs);

		std::string getName(void) const;
		std::string getPassword(void) const;
		std::vector<std::string> getListAdmin(void) const;
		std::vector<std::string> getListUser(void) const;
		std::string getChannelmode();
		int getModeSettings(void);

		void setName(std::string username);
		void setPassword(std::string password);
		void addAdmin(std::string admin);
		void removeAdmin(std::string admin);
		void addUser(std::string user);
		void removeUser(std::string user);
		void addMode(int mode);
		void removeMode(int mode);

		bool verifIfRegisteredAdmin(std::string admin);
		bool verifIfRegisteredUser(std::string user);
		bool isOperator(std::string user);
};

#endif