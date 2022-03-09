#include "server.h"

int main (void)
{
	int sock;
	struct sockaddr_in	sin;
	int sock_client;
	struct sockaddr_in	sin_client;
	socklen_t long_sock_c = sizeof(sin_client);

	printf("DEBUT");
	sock = socket(PF_INET, SOCK_STREAM, 0);
	if (sock < 0)
		printf("Error socket");
	printf("Socket ouverte en TCP/IP");
	sin.sin_addr.s_addr = htonl(INADDR_ANY);
	sin.sin_family = AF_INET;
	sin.sin_port = htons(23); //le port

	if (bind(sock, (SOCKADDR*)&sin, sizeof(sin)) < 0)
		printf("Error bind\n");
	if (listen(sock, 5) < 0) //deuxieme parametre = nombre de co pouvant etre mise en attente
		printf("Error lsiten\n");
	sock_client = accept(sock, (SOCKADDR*)&sin_client, &long_sock_c);
	printf("Un client se connect avec la socket %d dde %s:%d\n", sock_client, inet_ntoa(sin_client.sin_addr), htons(sin_client.sin_port));
	close(sock_client);
	printf("Fermeture socket client");
	close(sock);
	printf("Fermeture socket serveur");
	return (0);
}