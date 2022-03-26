#include "Client.hpp"
#include "Channel.hpp"

Client::Client() {}

Client::Client(SOCKET sock, SOCKADDR_IN sin) : _socket(sock), _sin(sin), _isAuthenticated(false) {
	this->_nickname = "";
	this->_username = "";
	this->_isRegistered = false;
	
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
	this->_password = rhs.getPassword();
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

std::string Client::getUsername(void) const {
	return this->_username;
}

std::string Client::getPassword(void) const {
	return this->_password;
}

std::string Client::getNickname(void) const {
	return this->_nickname;
}

std::vector<Channel> Client::getChannels(void) const {
	return this->_channels;
}

void Client::registerMe(void) {
	this->_isRegistered = true;
}

void Client::setPassword(std::string password) {
	this->_password = password;
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

void Client::addChannel(Channel & channel) {
	_channels.push_back(channel);
}
