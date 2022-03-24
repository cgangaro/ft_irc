#include "Server.hpp"

int main (int argc, char **argv)
{
	if (argc != 2) // should be 3 when password will be implemented
	{
		std::cerr << "Usage: " << argv[0] << " <port>" << std::endl;
		exit(EXIT_FAILURE);
	}

	Server server(atoi(argv[1]));
	server.listenning();

	return (EXIT_SUCCESS);
}


