#ifndef COMMAND_HPP
#define COMMAND_HPP

#include "Client.hpp"
#include "Errors.hpp"

#define COMMANDS "NICK USER PASS JOIN MSG QUIT"
#define NB_COMMANDS 6
#define COMMAND_EXECUTOR(name) void name(Client & client, std::vector<std::string> tokens);

class Command;

typedef void (Command::*commandExecutor)(Client &, std::vector<std::string>);
typedef struct s_command {
	std::string name;
	commandExecutor executor;
} t_command;

class CommunicationManager;

class Command
{
	private:
		std::vector<t_command> _commands;
		static commandExecutor _executors[NB_COMMANDS];
		CommunicationManager *_communicationManager;
		std::string _password;

	public:
		Command();
		Command(CommunicationManager *_communicationManager, std::string pwd);
		~Command();

		void interpret(char* buffer, Client & client);
		static std::vector<std::string> split(const char *buffer, std::string space_delimiter);
		static bool isValidStringData(std::string & data);

		COMMAND_EXECUTOR(commandNick)
		COMMAND_EXECUTOR(commandUser)
		COMMAND_EXECUTOR(commandPass)
		COMMAND_EXECUTOR(commandJoin)
		COMMAND_EXECUTOR(commandMsg)
		COMMAND_EXECUTOR(commandQuit)
};

#endif
