#include "server.h"

bool	init_server(t_server *serv)
{
	int i;

	serv->max_clients = 5;
	serv->max_sock_client = 0;
	serv->long_address_server = sizeof(serv->address_server);
	serv->long_address_client = sizeof(serv->address_client);

	serv->server_sock = socket(AF_INET, SOCK_STREAM, 0);
	if (serv->server_sock < 0)
	{
		dprintf(1, "Error socket");
		return (0);
	}
	dprintf(1, "Socket ouverte en TCP/IP\n");

	serv->address_server.sin_addr.s_addr = htonl(INADDR_ANY);
	//sin.sin_addr.s_addr = inet_addr("127.0.0.1");
	dprintf(1, "adrr = |%u|\n", serv->address_server.sin_addr.s_addr);
	serv->address_server.sin_family = AF_INET; //TCP/IP
	serv->address_server.sin_port = htons(23); //le port

	for (i = 0; i < serv->max_clients; i++)
	{
			serv->client_socket[i] = 0;
	}

	if (bind(serv->server_sock, (SOCKADDR*)&serv->address_server, sizeof(serv->address_server)) < 0)
	{
		dprintf(1, "Error bind\n");
		return (0);
	}

	if (listen(serv->server_sock, 5) < 0) //deuxieme parametre = nombre de co pouvant etre mise en attente
	{
		dprintf(1, "Error listen\n");
		return (0);
	}
	return (1);
}

void	init_readfs(t_server *serv)
{
	int i;
	int sock_temp;

	FD_ZERO(&serv->readfs); //initialise le readfs
	FD_SET(serv->server_sock, &serv->readfs); //ajoute le server_sock au readfs

	// FD_ZERO(&writefs); //pareil mais pour write, pas encore utilisé
	// FD_SET(sock, &writefs);

	serv->max_sock_client = serv->server_sock;
	for (i = 0; i < serv->max_clients; i++)
	{
		sock_temp = serv->client_socket[i];
		if (sock_temp > 0)
			FD_SET(sock_temp, &serv->readfs); //ajoute les client_sock au readfs
		if (sock_temp > serv->max_sock_client)
			serv->max_sock_client = sock_temp; //il faut connaitre le fd le plus grand pour select
	}
}

bool	check_existing_client(int new_client, t_server *serv)
{
	int i;
	int f = 0;

	for (i = 0; i < serv->max_clients; i++)
	{
		if (serv->client_socket[i] == new_client && serv->client_socket[i] != 0)
		{
			dprintf(1, "Client déjà existant\n");
			return (1);
		}
		if (serv->client_socket[i] == 0)
			f = 1;
	}
	// if (!f)
	// {
	// 	dprintf(1, "Max clients atteints\n");
	// 	return (1);
	// }
	return (0);
}

void	check_and_add_client(int new_client, t_server *serv)
{
	int i;

	for (i = 0; i <= serv->max_clients; i++)
	{
		if (i == serv->max_clients)
		{
			dprintf(1, "Max clients atteint\n");
			break ;
		}
		if (serv->client_socket[i] == 0)
		{
			serv->client_socket[i] = new_client;
			dprintf(1, "Ajout du sock client numero %d\n", i);
			break ;
		}
	}
}

bool	run_server(t_server *serv)
{
	int sock_client;
	char message[] = "Wsh mon gros\r\n";

	while (1)
	{
		init_readfs(serv);
		if (select(serv->max_sock_client + 1, &serv->readfs, NULL, NULL, 0) < 0)
		{
			dprintf(1, "Error select");
			return (-1);
		}
		if (FD_ISSET(serv->server_sock, &serv->readfs)) //vérifie si la socket server_sock est contenu dans l'ensemble readfs, dans ce cas savoir si on a reçu des données
		{
			dprintf(1, "\n\nNouveau paquet reçus !\n");
			dprintf(1, "En attente d'accept...\n\n");
			sock_client = accept(serv->server_sock, (SOCKADDR*)&serv->address_server, &serv->long_address_server);
			if (!check_existing_client(sock_client, serv))
			{
				dprintf(1, "Un client se connect avec la socket %d de %s:%d\n", sock_client, inet_ntoa(serv->address_server.sin_addr), htons(serv->address_server.sin_port));
				if (send(sock_client, message, strlen(message), 0) != (ssize_t)strlen(message)) //envoie de msg au nouveau client, !!send() retourne un ssize_t, strlen retourne un size_t. D'où le cast
				{
					dprintf(1, "Error send");
					return (0);
				}
				check_and_add_client(sock_client, serv);
			}
		}
	}
	return (0);
}

void	close_sockets(t_server *serv)
{
	int i;

	for (i = 0; i < serv->max_clients; i++)
	{
		close(serv->client_socket[i]);
	}	
	dprintf(1, "Fermeture sockets clients\n");
	close(serv->server_sock);
	dprintf(1, "Fermeture socket serveur\n");
}

int main (void)
{
	t_server serv;

	dprintf(1, "DEBUT\n");
	if (!init_server(&serv))
		return (-1);
	dprintf(1, "FIN INIT\n\n");
	run_server(&serv);
	close_sockets(&serv); //pour l'instant ne sert à rien puisqu'on ne sort jamais de run_server -> while(1)
	return (0);
}