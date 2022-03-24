#include "Channel.hpp"

Channel::Channel() {
	this->_name = "";
	this->_password = "";
}

Channel::Channel(Channel const &src) {
	*this = src;
}

Channel::Channel(std::string name, std::string password, Client admin) {
	_name = name;
	_password = password;
	// std::cout << "admin.getSocket() = " << admin.getSocket() << " | username = " << admin.getUsername() << std::endl;
	_list_admin.push_back(admin);
	// std::cout << "_list_admin[0].getSocket() = " << _list_admin[0].getSocket() << " | username = " << _list_admin[0].getUsername() << std::endl;
	_list_user.push_back(admin);
	// std::cout << "_list_user[0].getSocket() = " << _list_user[0].getSocket() << " | username = " << _list_user[0].getUsername() << std::endl;
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

std::vector<Client> Channel::getListAdmin(void) const {
	return _list_admin;
}

std::vector<Client> Channel::getListUser(void) const {
	return _list_user;
}

void Channel::setPassword(std::string password) {
	_password = password;
}

void Channel::setName(std::string name) {
	_name = name;
}

void Channel::addAdmin(Client admin)
{
	_list_admin.push_back(admin);
}

void Channel::addUser(Client user)
{
	_list_user.push_back(user);
}

bool Channel::verifIfAdmin(Client admin)
{
	for (size_t i = 0; i < _list_admin.size(); i++)
	{
		if (_list_admin[i].getUsername().compare(admin.getUsername()) == 0)
			return (true);
	}
	return (false);
}

bool Channel::verifIfUser(Client user)
{
	for (size_t i = 0; i < _list_user.size(); i++)
	{
		if (_list_user[i].getUsername().compare(user.getUsername()) == 0)
			return (true);
	}
	return (false);
}
