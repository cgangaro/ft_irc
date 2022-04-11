#include "Command.hpp"
#include "CommunicationManager.hpp"

std::vector<std::string> Command::getOperations(std::vector<std::string> input, std::string legalOps) {
	std::vector<std::string> output;
	std::string tmp = "";

	tmp.resize(2);
	if (input.size() < 3) return output;
	for (std::vector<std::string>::iterator it = input.begin() + 2; it != input.end(); ++it) {
		if ((it->at(0) == '+' || it->at(0) == '-') && it->length() > 1) {
			tmp[0] = it->at(0);
			for (size_t i = 1; i < it->length(); i++) {
				if (legalOps.find(it->at(i)) == std::string::npos) throw Exception::ERR_UMODEUNKNOWNFLAG(); // change error on channel operation
				tmp[1] = it->at(i);
				output.push_back(tmp);
			}
		}
	}
	return output;
}

std::vector<std::string> Command::getArg(std::vector<std::string> input)
{
	std::vector<std::string> arg;
	if (input.size() < 4)
		return arg;
	for (size_t i = 3; i < input.size(); i++)
		arg.push_back(input[i]);
	return arg;
}

int Command::userCharToFlag(char c) {
	switch (c) {
		case 'a': return F_AWAY;
		case 'i': return F_INVISIBLE;
		case 'w': return F_WALLOPS;
		case 'r': return F_RESTRICTED;
		case 'o': return F_OPER;
		case 'O': return F_LOCALOPER;
		default: return 0;
	}
}

char Command::userFlagTochar(int flag) {
	switch (flag) {
		case F_AWAY: return 'a';
		case F_INVISIBLE: return 'i';
		case F_WALLOPS: return 'w';
		case F_RESTRICTED: return 'r';
		case F_OPER: return 'o';
		case F_LOCALOPER: return 'O';
		default: return 0;
	}
}

char Command::channelFlagToChar(int flag) {
	switch (flag) {
		case F_CREATOR: return 'O';
		case F_OP: return 'o';
		case F_VOICE: return 'v';
		case F_ANONYMOUS: return 'a';
		case F_INVITE: return 'i';
		case F_MODERATED: return 'm';
		case F_NOEXTERNMSGS: return 'n';
		case F_QUIET: return 'q';
		case F_PRIVATE: return 'p';
		case F_SECRET: return 's';
		case F_REOP: return 'r';
		case F_TOPICOP: return 't';
		case F_KEY: return 'k';
		case F_LIMIT: return 'l';
		case F_BAN: return 'b';
		case F_EXCEPT: return 'e';
		case F_INVITEONLY: return 'I';
		default: return 0;
	}
}

int Command::channelCharToFlag(char c) {
	switch (c) {
		case 'O': return F_CREATOR;
		case 'o': return F_OP;
		case 'v': return F_VOICE;
		case 'a': return F_ANONYMOUS;
		case 'i': return F_INVITE;
		case 'm': return F_MODERATED;
		case 'n': return F_NOEXTERNMSGS;
		case 'q': return F_QUIET;
		case 'p': return F_PRIVATE;
		case 's': return F_SECRET;
		case 'r': return F_REOP;
		case 't': return F_TOPICOP;
		case 'k': return F_KEY;
		case 'l': return F_LIMIT;
		case 'b': return F_BAN;
		case 'e': return F_EXCEPT;
		case 'I': return F_INVITEONLY;
		default: return 0;
	}
}

void Command::execOperation(Client * client, std::string op) {
	int mode = userCharToFlag(op.at(1));

	if (op.at(0) == '+') {
		client->addMode(mode);
	} else if (op.at(0) == '-') {
		client->removeMode(mode);
	}
}

void Command::execChannelOperation(Channel * channel, std::string op, std::vector<std::string> arg) {
	int mode = channelCharToFlag(op.at(1));
	bool activ = true;
	if (op.at(0) == '+') {
		channel->addMode(mode);
	} else if (op.at(0) == '-') {
		channel->removeMode(mode);
		activ = false;
	}
	if (arg.size() > 0) {
		if (mode == F_OP || mode == F_VOICE)
			channelOperationUser(channel, arg, mode, activ);
		else if (mode == F_KEY)
			channel->setPassword(arg[0]);
		else if (mode == F_LIMIT)
			channel->setMaxUsers(arg[0]);
	}
}

void Command::channelOperationUser(Channel * channel, std::vector<std::string> arg, int mode, bool activ) {
	if (!_communicationManager->getClientManager()->isNicknameTaken(arg[0])) throw Exception::ERR_NOSUCHNICK(arg[0]);
	else if (!channel->verifIfRegisteredUser(arg[0])) throw Exception::ERR_CANNOTSENDTOCHAN(channel->getName());
	else {
		if (mode == F_CREATOR) {
			channel->setUserCreator(arg[0], activ);
		}
		else if (mode == F_OP) {
			channel->setUserOp(arg[0], activ);
		}
		else if (mode == F_VOICE) {
			channel->setUserVoice(arg[0], activ);
		}
	}
	
}
