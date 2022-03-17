#ifndef USER_HPP
#define USER_HPP

#include <string>

class User {
	private:
		std::string _username;
		std::string _password;
		std::string _nickname;
		// currentChannel

	public:
		User();
		~User();

		std::string getUsername(void) const;
		std::string getPassword(void) const;
		std::string getNickname(void) const;

		void setPassword(std::string password);
		void setUsername(std::string username);
		void setNickname(std::string nickname);
};

#endif