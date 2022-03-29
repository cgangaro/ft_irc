#ifndef COMMAND_HPP
#define COMMAND_HPP

#include "Commons.hpp"
#include "Client.hpp"

#define COMMANDS "NICK USER PASS JOIN PRIVMSG MSG QUIT"
#define NB_COMMANDS 7
#define COMMAND_EXECUTOR(name) bool name(Client * client, std::vector<std::string> tokens, std::string cmd);

class Command;

typedef bool (Command::*commandExecutor)(Client *, std::vector<std::string>, std::string cmd);
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

		Command& operator=(const Command& cm);
		bool interpret(char* buffer, Client * client);
		bool processCommand(std::string *cmd, Client * client);
		static std::vector<std::string> split(const char *buffer, std::string space_delimiter);
		static bool isValidStringData(std::string & data);
		static void eraseSubstr(std::string & str, const std::string & substr);

		COMMAND_EXECUTOR(commandNick)
		COMMAND_EXECUTOR(commandUser)
		COMMAND_EXECUTOR(commandPass)
		COMMAND_EXECUTOR(commandJoin)
		COMMAND_EXECUTOR(commandPrivmsg)
		COMMAND_EXECUTOR(commandMsg)
		COMMAND_EXECUTOR(commandQuit)

		void joinChannel(Client * client, std::string tokens_name, std::string tokens_pass);
		void addClientChannel(Client * client, Channel * channel);
};

#endif
