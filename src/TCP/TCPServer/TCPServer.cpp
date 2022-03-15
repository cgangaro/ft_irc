#include "TCPServer.hpp"

TCPServer::TCPServer() {
	createServer(DEFAULT_PORT);
}

TCPServer::TCPServer(int port) {
	createServer(port);
}


TCPServer::~TCPServer() {
	close(_socket);
}

int TCPServer::getPort(void) const {
	return ntohs(this->_sin.sin_port);
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

void TCPServer::initServer(void)
{
	_nb_client = 0;
}
