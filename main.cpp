#include "Server.hpp"

int main (int argc, char **argv)
{
	if (argc != 3)
	{
		std::cerr << "Usage: " << argv[0] << " <port> " << "<password>" << std::endl;
		exit(EXIT_FAILURE);
	}

	Server server(atoi(argv[1]), argv[2]);
	server.listenning();

	return (EXIT_SUCCESS);
}
