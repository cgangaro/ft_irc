#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include <string>
#include <vector>

class Channel {
	private:
		std::string _name;
		std::string _password;
		std::vector<std::string> _list_admin;
		std::vector<std::string> _list_user;

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

		void setName(std::string username);
		void setPassword(std::string password);
		void addAdmin(std::string admin);
		void addUser(std::string user);

		bool verifIfAdmin(std::string admin);
		bool verifIfUser(std::string user);
};

#endif