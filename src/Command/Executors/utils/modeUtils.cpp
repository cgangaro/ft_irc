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
				if (legalOps.find(it->at(i)) == std::string::npos) throw Exception::ERR_UMODEUNKNOWNFLAG();
				tmp[1] = it->at(i);
				output.push_back(tmp);
			}
		}
	}
	return output;
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
		default: return 0;
	}
}

int Command::channelCharToFlag(char c) {
	switch (c) {
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

void Command::execOperation(Channel * channel, std::string op) {
	int mode = channelCharToFlag(op.at(1));
	if (op.at(0) == '+') {
		channel->addMode(mode);
	} else if (op.at(0) == '-') {
		channel->removeMode(mode);
	}
}