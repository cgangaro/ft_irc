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

	std::cout << "Waiting for activity..." << std::endl;
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
	this->_communicationManager.sendToOne(SERVER_NAME, csock, MOTD);
	this->_clientManager.addClient(csock, csin);
}

void TCPServer::refreshReadfds() {
	FD_ZERO(_clientManager.getReadfds());
	_clientManager.addSocket(this->_socket);
	for (std::vector<TCPClient>::iterator it = _clientManager.getClients()->begin(); it != _clientManager.getClients()->end(); ++it)
		_clientManager.addSocket(it->getSocket());
}

void TCPServer::serverListen() {
	if (listen(this->_socket, SOMAXCONN) == SOCKET_ERROR)
		throw TCPException::ListenFailed();
		
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
