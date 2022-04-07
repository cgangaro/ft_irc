#include "Server.hpp"

Server::Server(int port, std::string pwd) {
	Command cmd(&this->_communicationManager, pwd);
	createServer(port);
	this->_password = pwd;
	this->_communicationManager = CommunicationManager(&this->_clientManager);
	this->_communicationManager.setInterpreter(cmd);
	signal(SIGINT, Server::killServer);
}


Server::~Server() {
	close(_socket);
}

int Server::getPort(void) const {
	return ntohs(this->_sin.sin_port);
}

char* Server::getAddress(void) const {
	return inet_ntoa(this->_sin.sin_addr);
}

void Server::listenning(void) {
	try {
		std::cout << "Listening on port " << this->getPort() << " ..." << std::endl;
		serverListen();
	} catch (std::exception &e) {
		std::cerr << e.what() << std::endl;
		exit(EXIT_FAILURE);
	}
}

void Server::killServer(int sig) {
	(void)sig;
	std::cout << std::endl << "Shutting server down..." << std::endl;
	exit(EXIT_SUCCESS);
}
