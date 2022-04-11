#ifndef COMMAND_HPP
#define COMMAND_HPP

#include "Commons.hpp"
#include "Client.hpp"

#define COMMANDS "NICK USER PASS JOIN PRIVMSG MSG QUIT PING TOPIC OPER MODE NOTICE KICK"
#define NB_COMMANDS 13
#define COMMAND_EXECUTOR(name) bool name(Client * client, std::vector<std::string> tokens);

class Command;

typedef bool (Command::*commandExecutor)(Client *, std::vector<std::string>);
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
		static std::string channelPrefix; 
		CommunicationManager *_communicationManager;
		std::string _password;
		std::string _latestCommand;

		/*
		** Internal logic for MODE command 
		*/
		std::vector<std::string> getOperations(std::vector<std::string> input, std::string legalOps);
		std::vector<std::string> getArg(std::vector<std::string> input);
		int userCharToFlag(char c);
		char userFlagTochar(int flag);
		int channelCharToFlag(char c);
		char channelFlagToChar(int flag);
		void execOperation(Client * client, std::string op);
		void execChannelOperation(Channel * channel, std::string op, std::vector<std::string> arg);

		void channelOperationUser(Channel * channel, std::vector<std::string> arg, int mode, bool activ);
	public:
		Command();
		Command(CommunicationManager *_communicationManager, std::string pwd);
		~Command();

		Command& operator=(const Command& cm);
		bool interpret(char* buffer, Client * client);
		bool processCommand(std::string *cmd, Client * client);
		std::string recomposeCommand(char* inputBuffer, Client * client);
		void sendWelcomeMessage(Client * client);
		std::vector<std::string> extractArgs(std::string cmd);
		static std::vector<std::string> split(const char *buffer, std::string space_delimiter);
		static bool isValidStringData(std::string & data);
		static void eraseSubstr(std::string & str, const std::string & substr);
		static std::string buildCmdResponse(Client & client, std::string cmd, int mode = OPT_SERVER);
		static std::string buildMultipleCmdResponse(Client & client, std::vector<std::string> raw_cmds, int mode = OPT_SERVER);

		COMMAND_EXECUTOR(commandNick)
		COMMAND_EXECUTOR(commandUser)
		COMMAND_EXECUTOR(commandPass)
		COMMAND_EXECUTOR(commandJoin)
		COMMAND_EXECUTOR(commandPrivmsg)
		COMMAND_EXECUTOR(commandMsg)
		COMMAND_EXECUTOR(commandQuit)
		COMMAND_EXECUTOR(commandPing)
		COMMAND_EXECUTOR(commandTopic)
		COMMAND_EXECUTOR(commandOper)
		COMMAND_EXECUTOR(commandMode)
		COMMAND_EXECUTOR(commandNotice)
		COMMAND_EXECUTOR(commandKick)

		/*
		** Sub-executors, do not include in this->_executors array
		*/
		COMMAND_EXECUTOR(commandModeUser)
		COMMAND_EXECUTOR(commandModeChannel)

		void joinChannel(Client * client, std::string tokens_name, std::string tokens_pass);
		void addClientChannel(Client * client, Channel * channel, bool creator);

};

#endif
