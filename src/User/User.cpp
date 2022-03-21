#include "User.hpp"

User::User() {
	this->_username = "";
	this->_nickname = "";
}

User::User(User const &src) {
	*this = src;
}

User::~User() {}

User & User::operator=(User const &rhs) {
	if (this == &rhs)
		return (*this);
	this->_username = rhs.getUsername();
	this->_password = rhs.getPassword();
	this->_nickname = rhs.getNickname();
	this->_channel = rhs.getChannel();
	return (*this);
}

std::string User::getUsername(void) const {
	return this->_username;
}

std::string User::getPassword(void) const {
	return this->_password;
}

std::string User::getNickname(void) const {
	return this->_nickname;
}

std::string User::getChannel(void) const {
	return this->_channel;
}

void User::setPassword(std::string password) {
	this->_password = password;
}

void User::setUsername(std::string username) {
	this->_username = username;
}
void User::setNickname(std::string nickname) {
	this->_nickname = nickname;
}