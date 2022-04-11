#ifndef REPLIES_HPP
#define REPLIES_HPP

#include "Replies.hpp"

#define SERVER_NAME "ft_irc_server"
#define SERVER_VERSION "0.0.1"
// TODO : get current date
#define SERVER_CREATED "2022-03-25"
// TODO : what are those ?
#define AVAILABLE_USER_MODES UMODE_FLAGS
#define AVAILABLE_CHANNEL_MODES CMODE_FLAGS

#define RPL_WELCOME(nickname)  "001 " + nickname + " :Welcome to the IRC Network " + nickname + CRLF
#define RPL_YOURHOST(nickname) "002 "+ nickname + " :Your host is " + SERVER_NAME + ", running version " + SERVER_VERSION + CRLF
#define RPL_CREATED(nickname) "003 "+ nickname + " :This server was created on " + SERVER_CREATED + CRLF
#define RPL_MYINFO(nickname) "004 "+ nickname + " :" + SERVER_NAME + " " + SERVER_VERSION + " User modes are " + AVAILABLE_USER_MODES + ", Channel modes are " + AVAILABLE_CHANNEL_MODES + CRLF

#define REGISTRATION_SUCCESS(nickname) RPL_WELCOME(nickname) + RPL_YOURHOST(nickname) + RPL_CREATED(nickname) + RPL_MYINFO(nickname)

#define RPL_YOUREOPER(nickname) ("381 " + nickname + " You are now an IRC operator" + CRLF)
#define RPL_CHANNELMODEIS(nickname, channelname, channelmode) ("324 " + nickname + " " + channelname + " " + channelmode + CRLF)
#define RPL_UMODEIS(user, usermode) ("221 " + user + " " + usermode + CRLF)
#define RPL_NOTOPIC(channelname) ("331 " + channelname + " :No topic is set" + CRLF)
#define RPL_TOPIC(channelname, topic) ("332 " + channelname + " :" + topic + CRLF)
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
#define ERR_NORECIPIENT_PRIVMSG_BUILDER(nickname) ("411 * " + nickname + " No recipient given (PRIVMSG)" + CRLF)
#define ERR_CHANOPRIVSNEEDED_BUILDER(channel) ("482 * " + channel + " :You're not channel operator" + CRLF)	
#define ERR_CANTSPEAKINCHANNEL_BUILDER(channel) ("000 * " + channel + " :You can't speak in this channel. You haven't voice privilege" + CRLF)	
#define ERR_INVITEONLYCHAN_BUILDER(channel) ("473 * " + channel + " :Cannot join channel (+i)" + CRLF)	
#define ERR_BANNEDFROMCHAN_BUILDER(channel) ("474 * " + channel + " :Cannot join channel (+b)" + CRLF)	
#define ERR_NOTONCHANNEL_BUILDER(channel) ("442 * " + channel + " :You're not on that channel" + CRLF)
#define ERR_CANTSPEAKINCHANNELNOTICE_BUILDER(channel) ("000 * " + channel + " :You can't speak in this channel with NOTICE" + CRLF)	
#define ERR_INVITEONLYCHAN_BUILDER(channel) ("473 * " + channel + " :Cannot join channel (+i)" + CRLF)
#define ERR_BANNEDFROMCHAN_BUILDER(channel) ("474 * " + channel + " :Cannot join channel (+b)" + CRLF)
#define ERR_USERNOTINCHANNEL_BUILDER(nickname, channel) ("441 * " + nickname + " " + channel + " :You're not on that channel" + CRLF)

#endif
