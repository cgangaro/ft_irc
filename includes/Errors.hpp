#ifndef ERRORS_HPP
#define ERRORS_HPP

#define ERR_NEEDMOREPARAMS(command) ("461 * " + command + ": Not enough parameters")
#define ERR_ALREADYREGISTRED "462 * :Unauthorized command (already registered)"
#define ERR_PASSWDMISMATCH "464 * :Password incorrect\r\n"

#endif
