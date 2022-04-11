#include "Channel.hpp"

Channel::Channel() {
	this->_name = "";
	this->_password = "";
}

Channel::Channel(Channel const &src) {
	*this = src;
}

Channel::Channel(std::string name, std::string password, std::string admin) {
	_name = name;
	_password = password;
	channelUser newUser;
	newUser.nickname = admin;
	newUser.op = true;
	newUser.voice = false;
	_userList.push_back(newUser);
}

Channel::~Channel() {}

Channel & Channel::operator=(Channel const &rhs) {
	if (this == &rhs)
		return (*this);
	_name = rhs.getName();
	_password = rhs.getPassword();
	_userList = rhs.getUserList();
	return (*this);
}

std::string Channel::getName(void) const {
	return _name;
}

std::string Channel::getPassword(void) const {
	return _password;
}

std::vector<channelUser> Channel::getUserList(void) const {
	return _userList;
}

void Channel::setPassword(std::string password) {
	_password = password;
}

void Channel::setName(std::string name) {
	_name = name;
}

void Channel::setUserOp(std::string op, bool activ) {
	for (std::vector<channelUser>::iterator it = _userList.begin(); it != _userList.end(); ++it)
	{
		if (it->nickname == op)
		{
			it->op = activ; 
			return ;
		}
	}
}

void Channel::addUser(std::string user)
{
	channelUser newUser;
	newUser.nickname = user;
	newUser.op = false;
	newUser.voice = false;
	if (!verifIfRegisteredAdmin(user))
		_userList.push_back(newUser);
}

void Channel::removeUser(std::string user)
{
	for (std::vector<channelUser>::iterator it = _userList.begin(); it != _userList.end(); ++it)
	{
		if (it->nickname == user)
		{
			_userList.erase(it); 
			return ;
		}
	}
}

bool Channel::verifIfRegisteredAdmin(std::string admin)
{
	for (size_t i = 0; i < _userList.size(); i++)
	{
		if (_userList[i].nickname == admin && _userList[i].op == true)
			return (true);
	}
	return (false);
}

bool Channel::verifIfRegisteredUser(std::string user)
{
	for (size_t i = 0; i < _userList.size(); i++)
	{
		if (_userList[i].nickname == user)
			return (true);
	}
	return (false);
}

bool Channel::isOperator(std::string user) {
	for (size_t i = 0; i < _userList.size(); i++)
	{
		if (_userList[i].nickname == user) {
			if (_userList[i].op == true)
				return (true);
			return (false);
		}
	}
	return (false);
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
	usermode += 'C';
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
