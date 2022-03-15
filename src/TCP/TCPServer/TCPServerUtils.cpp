#include "TCPServer.hpp"

SOCKET TCPServer::createSocket() {
	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET)
		throw TCPServer::SocketCreationFailed();
	return (sock);
}

int TCPServer::bindSocket() {
	int ret = bind(this->_socket, (SOCKADDR*)&this->_sin, sizeof(this->_sin));
	if (ret == SOCKET_ERROR)
		throw TCPServer::BindFailed();
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

void TCPServer::initReadfds()
{
	FD_ZERO(&_readfds); //clear le fd_set
	FD_SET(_socket, &_readfds); //ajoute un descriptor au fd_set, ici notre server_socket
	_max_socket = _socket;
	_max_socket = _clientManager.initReadfdsClient(&_readfds, _max_socket);
}

void TCPServer::serverListen() {
	int csock;

	if (listen(this->_socket, SOMAXCONN) == SOCKET_ERROR)
		throw TCPServer::ListenFailed();

	while (true) {
		SOCKADDR_IN csin;
		socklen_t csin_size = sizeof(csin);
		initReadfds();
		int select_ret = select(_max_socket + 1, &_readfds, NULL, NULL, 0);//surveille tous les fd qu'on a filé, regarde si au moins un est "prêt" pour une opération d'IN/OUTPUT
		if (select_ret == SOCKET_ERROR)
			throw TCPServer::SelectFailed();
		if (FD_ISSET(_socket, &_readfds)) //lit le _readfds pour voir si il y a une connexion entrante sur server_socket
		{
			csock = accept(this->_socket, (SOCKADDR*)&csin, &csin_size);
			if (csock == SOCKET_ERROR)
				throw TCPServer::AcceptFailed();
			std::cout << "Client connected with socket " << csock << " on " << inet_ntoa(this->_sin.sin_addr) << ":" << this->getPort() << std::endl;
			t_client *client = new t_client;
			client->socket = csock;
			client->sin = csin;
			this->_clientManager.addClient(*client, _nb_client);
			_nb_client++;
			char welcome_msg[21] = "Wsh, tu veux un 10?\n";
			ssize_t ret_send = send(csock, welcome_msg, strlen(welcome_msg), 0);
			if (ret_send != (ssize_t)strlen(welcome_msg))
				throw TCPServer::SendFailed();
			std::cout << "Welcome message sent" << std::endl;
		}
		if (_clientManager.readClient(&_readfds) < 0)
			throw TCPServer::ReadFailed();
	}
}