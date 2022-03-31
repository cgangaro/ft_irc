#ifndef REPLIES_HPP
#define REPLIES_HPP

#include "Replies.hpp"

#define SERVER_NAME "ft_irc_server"
#define SERVER_VERSION "0.0.1"
// TODO : get current date
#define SERVER_CREATED "2022-03-25"
// TODO : what are those ?
#define AVAILABLE_USER_MODES "<available user modes>"
#define AVAILABLE_CHANNEL_MODES "<available channel modes>"

#define RPL_WELCOME(nickname)  "001 " + nickname + " Welcome to the IRC Network " + nickname + CRLF
#define RPL_YOURHOST(nickname) "002 "+ nickname + " Your host is " + SERVER_NAME + ", running version " + SERVER_VERSION + CRLF
#define RPL_CREATED(nickname) "003 "+ nickname + " This server was created on " + SERVER_CREATED + CRLF
#define RPL_MYINFO(nickname) "004 "+ nickname + " " + SERVER_NAME + " " + SERVER_VERSION + " " + AVAILABLE_USER_MODES + " " + AVAILABLE_CHANNEL_MODES + CRLF

#define REGISTRATION_SUCCESS(nickname) RPL_WELCOME(nickname) + RPL_YOURHOST(nickname) + RPL_CREATED(nickname) + RPL_MYINFO(nickname)

// Those are used in Exception.hpp
#define ERR_ERRONEOUSNICKNAME_BUILDER(nickname) ("432 * " + nickname + " :Erroneous nickname" + CRLF)
#define ERR_NICKNAMEINUSE_BUILDER(nickname) ("433 * " + nickname + " :Nickname is already in use" + CRLF)
#define ERR_NEEDMOREPARAMS_BUILDER(command) ("461 * " + command + " :Not enough parameters" + CRLF)
#define ERR_CHANNELISFULL_BUILDER(channel) ("471 * " + channel + " CHANNEL_IS_FULL :Cannot join channel" + CRLF)
#define ERR_NOSUCHCHANNEL_BUILDER(channel) ("403 * " + channel + " :No such channel" + CRLF)
#define ERR_TOOMANYCHANNELS_BUILDER(channel) ("405 * " + channel + " :You have joined too many channels" + CRLF)
#define ERR_BADCHANNELKEY_BUILDER(channel) ("475 * " + channel + " BAD_CHANNEL_KEY :Cannot join channel" + CRLF)
#define ERR_CANNOTSENDTOCHAN_BUILDER(channel) ("404 * " + channel + " :Cannot send to channel" + CRLF)
#define ERR_TOOMANYTARGETS_BUILDER(targets) ("407 * " + targets + " :too much recipients" + CRLF)
#define ERR_NOSUCHNICK_BUILDER(nickname) ("401 * " + nickname + " :No such nick/channel" + CRLF)

#endif