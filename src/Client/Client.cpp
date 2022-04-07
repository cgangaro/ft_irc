#include "Client.hpp"
#include "Channel.hpp"

Client::Client() {}

Client::Client(SOCKET sock, SOCKADDR_IN sin) : _socket(sock), _sin(sin), _isAuthenticated(false) {
	this->_nickname = "";
	this->_username = "";
	this->_isRegistered = false;
	this->_isOperator = false;
	this->buffer = "";
	this->_toKill = false;
	this->_modeSettings = 0;
}

Client::Client(Client const & src) {
	*this = src;
}

Client::~Client() {
}

Client & Client::operator=(Client const &rhs) {
	if (this == &rhs)
		return (*this);
	this->_socket = rhs.getSocket();
	this->_sin = rhs.getSin();
	this->_isAuthenticated = rhs.isAuthenticated();
	this->_isRegistered = rhs.isRegistered();
	this->_username = rhs.getUsername();
	this->_nickname = rhs.getNickname();
	this->_channels = rhs.getChannels();
	this->_toKill = rhs.getToKill();
	this->_modeSettings = rhs.getModeSettings();
	this->_isOperator = rhs.isOperator();
	return (*this);
}

SOCKET Client::getSocket(void) const {
	return this->_socket;
}

SOCKADDR_IN Client::getSin(void) const {
	return this->_sin;
}

char* Client::getAddress(void) const {
	return inet_ntoa(this->_sin.sin_addr);
}

int Client::getPort(void) const {
	return ntohs(this->_sin.sin_port);
}

bool Client::isAuthenticated(void) const {
	return _isAuthenticated;
}

bool Client::isRegistered(void) const {
	return _isRegistered;
}

bool Client::isOperator(void) const {
	return _isOperator;
}

std::string Client::getUsername(void) const {
	return this->_username;
}

std::string Client::getNickname(void) const {
	return this->_nickname;
}

int Client::getModeSettings(void) const {
	return this->_modeSettings;
}

std::string Client::getSujet(void) const {
	std::string ret(":" + _nickname + "!~" + _username + "@" + getAddress());
	return ret;
}

std::vector<Channel> Client::getChannels(void) const {
	return this->_channels;
}

const std::string & Client::getBuffer(void) const {
	return this->buffer;
}

bool Client::getToKill(void) const {
	return this->_toKill;
}

void Client::setOperator(bool isOperator) {
	this->_isOperator = isOperator;
}

void Client::setBuffer(std::string buffer) {
	this->buffer = buffer;
}

void Client::setToKill(void) {
	this->_toKill = true;
}

void Client::registerMe(void) {
	if (!getUsername().empty() && !getNickname().empty())
		this->_isRegistered = true;
}

void Client::setUsername(std::string username) {
	this->_username = username;
}

void Client::setNickname(std::string nickname) {
	this->_nickname = nickname;
}

void Client::setSocket(SOCKET socket) {
	this->_socket = socket;
}

void Client::authenticate(void) {
	this->_isAuthenticated = true;
}

void Client::addChannel(Channel * channel) {
	_channels.push_back(*channel);
}

bool Client::verifIfRegisteredChannel(Channel * channel) {
	for (size_t i = 0; i < _channels.size(); i++)
	{
		if (_channels[i].getName().compare(channel->getName()) == 0)
			return (true);
	}
	return (false);
}

bool Client::hasCommonChannel(Client client)
{
	for (size_t i = 0; i < client.getChannels().size(); i++)
	{
		if (verifIfRegisteredChannel(&client.getChannels()[i]))
			return (true);
	}
	return (false);
}

void Client::test_printChannels(void)
{
	std::cout << "Print client: " << _username << " channels" << std::endl;
	std::cout << "size = " << _channels.size() << std::endl;
	for (size_t i = 0; i < _channels.size(); i++)
	{
		std::cout << _channels[i].getName() << std::endl;
	}
	std::cout << "End print client channels" << std::endl;
}

void Client::addMode(int mode) {
	this->_modeSettings |= mode;
}

void Client::removeMode(int mode) {
	this->_modeSettings &= ~mode;
}

std::string Client::getUsermode() {
	std::string usermode;

	usermode += '+';
	if (_modeSettings & F_AWAY) usermode += 'a';
	if (_modeSettings & F_INVISIBLE) usermode += 'i';
	if (_modeSettings & F_WALLOPS) usermode += 'w';
	if (_modeSettings & F_RESTRICTED) usermode += 'r';
	if (_modeSettings & F_OPER) usermode += 'o';
	if (_modeSettings & F_LOCALOPER) usermode += 'O';
	return usermode;
}
