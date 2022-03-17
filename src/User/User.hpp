#ifndef USER_HPP
#define USER_HPP

#include <string>

class User {
	private:
		std::string _username;
		std::string _password;
		std::string _nickname;
		std::string _channel; // a string beginning with #

	public:
		User();
		~User();

		std::string getUsername(void) const;
		std::string getPassword(void) const;
		std::string getNickname(void) const;
		std::string getChannel(void) const;

		void setPassword(std::string password);
		void setUsername(std::string username);
		void setNickname(std::string nickname);
};

#endif