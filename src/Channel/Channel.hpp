#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include <string>
#include <vector>
#include "Client.hpp"

class Channel {
	private:
		std::string _name;
		std::string _password;
		std::vector<SOCKET> _list_admin;
		std::vector<SOCKET> _list_user;

		int _modeSettings;

	public:
		Channel();
		Channel(Channel const &src);
		Channel(std::string name, std::string password, SOCKET admin);
		~Channel();

		Channel &operator=(Channel const &rhs);

		std::string getName(void) const;
		std::string getPassword(void) const;
		std::vector<SOCKET> getListAdmin(void) const;
		std::vector<SOCKET> getListUser(void) const;

		void setName(std::string username);
		void setPassword(std::string password);
		void addAdmin(SOCKET admin);
		void addUser(SOCKET user);
		void addMode(int mode);
		void removeMode(int mode);

		bool verifIfRegisteredAdmin(SOCKET admin);
		bool verifIfRegisteredUser(SOCKET user);
		bool isOperator(SOCKET user);
};

#endif