#include "Client.hpp"
#include "Channel.hpp"

Client::Client() {}

Client::Client(SOCKET sock, SOCKADDR_IN sin) : _socket(sock), _sin(sin), _isAuthenticated(false) {
	this->_nickname = "";
	this->_username = "";
	this->_isRegistered = false;
	this->_isOperator = false;
	this->buffer = "";
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

std::vector<Channel> Client::getChannels(void) const {
	return this->_channels;
}

const std::string & Client::getBuffer(void) const {
	return this->buffer;
}

void Client::setOperator(bool isOperator) {
	this->_isOperator = isOperator;
}

void Client::setBuffer(std::string buffer) {
	this->buffer = buffer;
}

void Client::registerMe(void) {
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
