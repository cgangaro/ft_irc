#include "User.hpp"

User::User() {
	this->_username = "defaultUsername";
}

User::~User() {}

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