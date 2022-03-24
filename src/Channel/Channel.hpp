#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include <string>
#include <vector>
#include "Client.hpp"

class Channel {
	private:
		std::string _name;
		std::string _password;
		std::vector<Client> _list_admin;
		std::vector<Client> _list_user;

	public:
		Channel();
		Channel(Channel const &src);
		Channel(std::string name, std::string password, Client admin);
		~Channel();

		Channel &operator=(Channel const &rhs);

		std::string getName(void) const;
		std::string getPassword(void) const;
		std::vector<Client> getListAdmin(void) const;
		std::vector<Client> getListUser(void) const;

		void setName(std::string username);
		void setPassword(std::string password);
		void addAdmin(Client admin);
		void addUser(Client user);

		bool verifIfAdmin(Client admin);
		bool verifIfUser(Client user);
};

#endif