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
	if (!verifIfRegisteredAdmin(admin))
		_list_admin.push_back(admin);
}

void Channel::removeAdmin(SOCKET admin)
{
	for (std::vector<SOCKET>::iterator it = _list_admin.begin(); it != _list_admin.end(); ++it)
	{
		if (*it == admin)
		{
			_list_admin.erase(it); 
			return ;
		}
	}
}

void Channel::addUser(SOCKET user)
{
	if (!verifIfRegisteredAdmin(user))
		_list_user.push_back(user);
}

void Channel::removeUser(SOCKET user)
{
	for (std::vector<SOCKET>::iterator it = _list_user.begin(); it != _list_user.end(); ++it)
	{
		if (*it == user)
		{
			_list_user.erase(it); 
			return ;
		}
	}
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

bool Channel::isOperator(SOCKET user) {
	for (std::vector<SOCKET>::iterator it = _list_admin.begin(); it != _list_admin.end(); ++it)
		if (*it == user)
			return (true);
	return false;
}

void Channel::addMode(int mode) {
	this->_modeSettings |= mode;
}

void Channel::removeMode(int mode) {
	this->_modeSettings &= ~mode;
}

int Channel::getModeSettings(void){
	return this->_modeSettings;
}

std::string Channel::getChannelmode() {
	std::string usermode;

	usermode += '+';
	if (_modeSettings & F_CREATOR) usermode += 'O';
	if (_modeSettings & F_OP) usermode += 'o';
	if (_modeSettings & F_VOICE) usermode += 'v';
	if (_modeSettings & F_ANONYMOUS) usermode += 'a';
	if (_modeSettings & F_INVITE) usermode += 'i';
	if (_modeSettings & F_MODERATED) usermode += 'm';
	if (_modeSettings & F_NOEXTERNMSGS) usermode += 'n';
	if (_modeSettings & F_QUIET) usermode += 'q';
	if (_modeSettings & F_PRIVATE) usermode += 'p';
	if (_modeSettings & F_SECRET) usermode += 's';
	if (_modeSettings & F_REOP) usermode += 'r';
	if (_modeSettings & F_TOPICOP) usermode += 't';
	if (_modeSettings & F_KEY) usermode += 'k';
	if (_modeSettings & F_LIMIT) usermode += 'l';
	if (_modeSettings & F_BAN) usermode += 'b';
	if (_modeSettings & F_EXCEPT) usermode += 'e';
	if (_modeSettings & F_INVITEONLY) usermode += 'I';
	return usermode;
}
