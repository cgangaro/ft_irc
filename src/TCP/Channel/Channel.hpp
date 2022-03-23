#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include <string>
#include <vector>
#include "User.hpp"

class Channel {
	private:
		std::string _name;
		std::string _password;
		std::vector<User> _list_admin;
		std::vector<User> _list_user;

	public:
		Channel();
		Channel(Channel const &src);
		Channel(std::string name, std::string password, User admin);
		~Channel();

		Channel &operator=(Channel const &rhs);

		std::string getName(void) const;
		std::string getPassword(void) const;
		std::vector<User> getListAdmin(void) const;
		std::vector<User> getListUser(void) const;

		void setName(std::string username);
		void setPassword(std::string password);
		void addAdmin(User admin);
		void addUser(User user);

		bool verifIfAdmin(User admin);
		bool verifIfUser(User user);
};

#endif