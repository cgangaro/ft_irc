#ifndef TCP_SERVER_H
#define TCP_SERVER_H

#include "TCPCommons.hpp"
#include "TCPClientManager.hpp"

class TCPServer {

	private:
		SOCKET _socket;
		SOCKADDR_IN _sin;
		TCPClientManager _clientManager;
		fd_set	_readfds; //contient une liste de fd à surveiller, pour n'importe qu'elle activité
		SOCKET _max_socket; //pour slect(), premier argument. Correspond à la plus grande socket à surveiller


		static SOCKET createSocket();
		int bindSocket();
		void createServer(int port);
		void serverListen(void);
		void initReadfds(void);

	public:
		TCPServer();
		TCPServer(int port);
		~TCPServer();

		void listenning(void);
		int getPort(void) const;

		/*
		** Exceptions:
		*/
		class BindFailed : public std::exception
		{
			public:
				virtual const char* what() const throw();
		};
		class SocketCreationFailed : public std::exception
		{
			public:
				virtual const char* what() const throw();
		};
		class ListenFailed : public std::exception
		{
			public:
				virtual const char* what() const throw();
		};
		class AcceptFailed : public std::exception
		{
			public:
				virtual const char* what() const throw();
		};
		class SelectFailed : public std::exception
		{
			public:
				virtual const char* what() const throw();
		};
		class SendFailed : public std::exception
		{
			public:
				virtual const char* what() const throw();
		};
		class ReadFailed : public std::exception
		{
			public:
				virtual const char* what() const throw();
		};
};

#endif