#ifndef SERVER_H
#define SERVER_H

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>



// typedef struct sockaddr_in	t_sockaddr_in;
typedef struct sockaddr SOCKADDR;
// short      sin_family;
// unsigned short   sin_port;
// struct   in_addr   sin_addr;

struct sockaddr_in	sin;

typedef struct			s_server
{
	struct sockaddr_in	address_server; //ensemble des sock server + client
	socklen_t 			long_address_server;
	struct sockaddr_in	address_client;
	socklen_t 			long_address_client;
	int 				max_clients;
	int					server_sock;
	int 				client_socket[5];
	int 				max_sock_client;
	fd_set				readfs;
}						t_server;

// typedef struct			s_client
// {
// 	int					client_socket;
// 	struct sockaddr_in	address_client;
// 	socklen_t 			long_address_client;
// }						t_client;

#endif