#include "Channel.hpp"

Channel::Channel() {
	this->_name = "";
	this->_password = "";
}

Channel::Channel(Channel const &src) {
	*this = src;
}

Channel::Channel(std::string name, std::string password, SOCKET admin) {
	_name = name;
	_password = password;
	_list_admin.push_back(admin);
	_list_user.push_back(admin);
}

Channel::~Channel() {}

Channel & Channel::operator=(Channel const &rhs) {
	if (this == &rhs)
		return (*this);
	_name = rhs.getName();
	_password = rhs.getPassword();
	_list_admin = rhs.getListAdmin();
	_list_user = rhs.getListUser();
	return (*this);
}

std::string Channel::getName(void) const {
	return _name;
}

std::string Channel::getPassword(void) const {
	return _password;
}

std::vector<SOCKET> Channel::getListAdmin(void) const {
	return _list_admin;
}

std::vector<SOCKET> Channel::getListUser(void) const {
	return _list_user;
}

void Channel::setPassword(std::string password) {
	_password = password;
}

void Channel::setName(std::string name) {
	_name = name;
}

void Channel::addAdmin(SOCKET admin)
{
	_list_admin.push_back(admin);
}

void Channel::addUser(SOCKET user)
{
	_list_user.push_back(user);
}

bool Channel::verifIfRegisteredAdmin(SOCKET admin)
{
	for (size_t i = 0; i < _list_admin.size(); i++)
	{
		if (_list_admin[i] == admin)
			return (true);
	}
	return (false);
}

bool Channel::verifIfRegisteredUser(SOCKET user)
{
	for (size_t i = 0; i < _list_user.size(); i++)
	{
		if (_list_user[i] == user)
			return (true);
	}
	return (false);
}
