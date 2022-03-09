#include "server.h"

int main (void)
{
	int sock;
	struct sockaddr_in	sin;
	int socket_error_bind;
	int socket_error_listen;

	sock = socket(PF_INET, SOCK_STREAM, 0);
	sin.sin_addr.s_addr = htonl(INADDR_ANY);
	sin.sin_family = AF_INET;
	sin.sin_port = htons(23); //le port
	socket_error_bind = bind(sock, (SOCKADDR*)&sin, sizeof(sin));
	socket_error_listen = listen(sock, 5); //deuxieme parametre = nombre de co pouvant etre mise en attente
	
}