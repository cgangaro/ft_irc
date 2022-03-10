#include "server.h"

int main (void)
{
	int sock;
	struct sockaddr_in	sin;
	int sock_client;
	struct sockaddr_in	sin_client;
	socklen_t long_sock_c = sizeof(sin_client);

	dprintf(1, "DEBUT\n");
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock < 0)
		printf("Error socket");
	dprintf(1, "Socket ouverte en TCP/IP\n");
	sin.sin_addr.s_addr = htonl(INADDR_ANY);
	//sin.sin_addr.s_addr = inet_addr("127.0.0.1");
	dprintf(1, "adrr = |%u|\n", sin.sin_addr.s_addr);
	sin.sin_family = AF_INET;
	sin.sin_port = htons(23); //le port

	if (bind(sock, (SOCKADDR*)&sin, sizeof(sin)) < 0)
		dprintf(1, "Error bind\n");
	if (listen(sock, 5) < 0) //deuxieme parametre = nombre de co pouvant etre mise en attente
		dprintf(1, "Error listen\n");

	fd_set readfs;
	while (1)
	{
		FD_ZERO(&readfs);
		FD_SET(sock, &readfs);
		dprintf(1, "Before select\n");
		if (select(sock + 1, &readfs, NULL, NULL, NULL) < 0)
			dprintf(1, "Error select");
		dprintf(1, "Before select\n");
		if (FD_ISSET(sock, &readfs))
		{
			dprintf(1, "Before accept\n");
			sock_client = accept(sock, (SOCKADDR*)&sin_client, &long_sock_c);
			dprintf(1, "Un client se connect avec la socket %d de %s:%d\n", sock_client, inet_ntoa(sin_client.sin_addr), htons(sin_client.sin_port));
			close(sock_client);
			dprintf(1, "Fermeture socket client\n");
		}
	}

	close(sock_client);
	dprintf(1, "Fermeture socket client\n");
	close(sock);
	dprintf(1, "Fermeture socket serveur\n");
	return (0);
}