#ifndef USER_HPP
#define USER_HPP

#include <string>
#include <vector>

class User {
	private:
		std::string _username;
		std::string _password;
		std::string _nickname;
		std::vector<std::string> _channels; // a string beginning with #

	public:
		User();
		User(User const &src);
		~User();

		User &operator=(User const &rhs);

		std::string getUsername(void) const;
		std::string getPassword(void) const;
		std::string getNickname(void) const;
		std::vector<std::string> getChannels(void) const;

		void setPassword(std::string password);
		void setUsername(std::string username);
		void setNickname(std::string nickname);
		void addChannel(std::string channel);
};

#endif