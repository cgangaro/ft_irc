#include "Command.hpp"

bool isValidStringData(std::string & data) {
	if (data.empty())
		return false;
	if (data.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_") != std::string::npos)
		return false;
	return true;
}

std::vector<std::string> Command::split(const char *buffer, std::string space_delimiter)
{
	std::string buf(buffer);

    std::vector<std::string> ret;

    size_t pos = 0;
    while ((pos = buf.find(space_delimiter)) != std::string::npos)
	{
        ret.push_back(buf.substr(0, pos));
        buf.erase(0, pos + space_delimiter.length());
    }
	if (buf[buf.length() - 1] == '\n')
		buf.erase(buf.length() - 1, 1);
	ret.push_back(buf.substr(0, buf.length()));
    buf.erase(0, buf.length());
	return (ret);
}
