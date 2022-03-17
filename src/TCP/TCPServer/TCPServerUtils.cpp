#include "TCPServer.hpp"

SOCKET TCPServer::createSocket() {
	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET)
		throw TCPException::SocketCreationFailed();
	return (sock);
}

int TCPServer::bindSocket() {
	int ret = bind(this->_socket, (SOCKADDR*)&this->_sin, sizeof(this->_sin));
	if (ret == SOCKET_ERROR)
		throw TCPException::BindFailed();
	return (ret);
}

void TCPServer::createServer(int port) {
	try {
		// Create socket
		this->_socket = createSocket();

		// Socket parameters
		this->_sin.sin_addr.s_addr = htonl(INADDR_ANY);
		this->_sin.sin_family = AF_INET;
		this->_sin.sin_port = htons(port);

		// Bind socket
		bindSocket();
	}
	catch (std::exception &e) {
		std::cerr << e.what() << std::endl;
		exit(EXIT_FAILURE);
	}
}

void TCPServer::waitForActivity() {
	int selectRet;

	selectRet = select(_clientManager.getMaxSocket() + 1, _clientManager.getReadfds(), NULL, NULL, NULL);
	if (selectRet == SOCKET_ERROR)
			throw TCPException::SelectFailed();
}

bool TCPServer::isNewClientWaiting() {
	return FD_ISSET(this->_socket, _clientManager.getReadfds());
}

void TCPServer::promptNewClient(int sock) {
	std::cout << "Client connected with socket " << sock << " on " << this->getAddress() << ":" << this->getPort() << std::endl;
}

void TCPServer::registerNewClient() {
	int csock;
	SOCKADDR_IN csin;
	socklen_t csin_size = sizeof(csin);

	csock = accept(this->_socket, (SOCKADDR*)&csin, &csin_size);
	if (csock == SOCKET_ERROR)
		throw TCPException::AcceptFailed();
	promptNewClient(csock);
	ssize_t ret_send = send(csock, MOTD, strlen(MOTD), 0);
	if (ret_send != (ssize_t)strlen(MOTD))
		throw TCPException::SendFailed();
	this->_clientManager.addClient(csock, csin);
}

void TCPServer::serverListen() {
	if (listen(this->_socket, SOMAXCONN) == SOCKET_ERROR)
		throw TCPException::ListenFailed();
	_clientManager.addSocket(_socket);

	while (true) {
		waitForActivity();
		if (isNewClientWaiting()) registerNewClient();
/* 		if (_clientManager.readClient() < 0)
			throw TCPException::ReadFailed(); */
	}
}
