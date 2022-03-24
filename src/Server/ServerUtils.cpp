#include "Server.hpp"

SOCKET Server::createSocket() {
	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET)
		throw Exception::SocketCreationFailed();
	return (sock);
}

int Server::bindSocket() {
	int ret = bind(this->_socket, (SOCKADDR*)&this->_sin, sizeof(this->_sin));
	if (ret == SOCKET_ERROR)
		throw Exception::BindFailed();
	return (ret);
}

void Server::createServer(int port) {
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

void Server::waitForActivity() {
	int selectRet;

	selectRet = select(_clientManager.getMaxSocket() + 1, _clientManager.getReadfds(), NULL, NULL, NULL);
	if (selectRet == SOCKET_ERROR)
			throw Exception::SelectFailed();
}

bool Server::isNewClientWaiting() {
	return FD_ISSET(this->_socket, _clientManager.getReadfds());
}

void Server::promptNewClient(int sock) {
	std::cout << "Client connected with socket " << sock << " on " << this->getAddress() << ":" << this->getPort() << std::endl;
}

void Server::registerNewClient() {
	int csock;
	SOCKADDR_IN csin;
	socklen_t csin_size = sizeof(csin);

	csock = accept(this->_socket, (SOCKADDR*)&csin, &csin_size);
	if (csock == SOCKET_ERROR)
		throw Exception::AcceptFailed();
	promptNewClient(csock);
	this->_clientManager.addClient(csock, csin);
}

void Server::refreshReadfds() {
	FD_ZERO(_clientManager.getReadfds());
	_clientManager.addSocket(this->_socket);
	for (std::vector<Client>::iterator it = _clientManager.getClients()->begin(); it != _clientManager.getClients()->end(); ++it)
		_clientManager.addSocket(it->getSocket());
}

void Server::serverListen() {
	if (listen(this->_socket, SOMAXCONN) == SOCKET_ERROR)
		throw Exception::ListenFailed();
		
	try {
		while (true) {
			refreshReadfds();
			waitForActivity();
			if (isNewClientWaiting()) registerNewClient();
			else this->_communicationManager.processClientActivity();
		}
	} catch (std::exception &e) {
		std::cerr << e.what() << std::endl;
		exit(EXIT_FAILURE);
	}
}
