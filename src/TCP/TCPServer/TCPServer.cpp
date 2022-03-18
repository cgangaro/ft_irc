#include "TCPServer.hpp"

TCPServer::TCPServer() {
	createServer(DEFAULT_PORT);
}

TCPServer::TCPServer(int port) {
	createServer(port);
	this->_communicationManager = TCPCommunicationManager(&this->_clientManager);
	signal(SIGINT, TCPServer::killServer);
}


TCPServer::~TCPServer() {
	close(_socket);
}

int TCPServer::getPort(void) const {
	return ntohs(this->_sin.sin_port);
}

char* TCPServer::getAddress(void) const {
	return inet_ntoa(this->_sin.sin_addr);
}

void TCPServer::listenning(void) {
	try {
		std::cout << "Listening on port " << this->getPort() << " ..." << std::endl;
		serverListen();
	} catch (std::exception &e) {
		std::cerr << e.what() << std::endl;
		exit(EXIT_FAILURE);
	}
}

void TCPServer::killServer(int sig) {
	(void)sig;
	std::cout << std::endl << "Shutting server down..." << std::endl;
	exit(EXIT_SUCCESS);
}