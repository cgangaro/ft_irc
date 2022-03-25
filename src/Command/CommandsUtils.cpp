#include "Command.hpp"

bool Command::isValidStringData(std::string & data) {
	unsigned long pos;

	if (data.empty())
		return false;
	pos = data.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_\r\n");
	return (pos == std::string::npos);
}

void Command::eraseSubstr(std::string & str, const std::string & substr) {
	size_t pos = 0;

	while ((pos = str.find(substr, pos)) != std::string::npos) {
		str.erase(pos, substr.length());
	}
}

std::vector<std::string> Command::split(const char *buffer, std::string separators)
{
	std::string buf(buffer);

    std::vector<std::string> ret;

    size_t pos = 0;
    while ((pos = buf.find_first_of(separators)) != std::string::npos)
	{
        ret.push_back(buf.substr(0, pos));
        buf.erase(0, pos + 1);
    }
	if (!buf.empty())
		ret.push_back(buf.substr(0, buf.length()));
	buf.erase(0, buf.length());
	return (ret);
}
