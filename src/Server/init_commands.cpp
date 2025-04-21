#include <Server.hpp>

void    Server::init_commands(void)
{
	// Client messages
	_coms["PASS"] = &Server::_PASS;
	_coms["NICK"] = &Server::_NICK;
	_coms["USER"] = &Server::_USER;
	_coms["PING"] = &Server::_PING;
	_coms["PONG"] = &Server::_PONG;
	_coms["OPER"] = &Server::_OPER;
	_coms["QUIT"] = &Server::_QUIT;
	_coms["ERROR"] = &Server::_ERROR;

	// Channel operations
	_coms["JOIN"] = &Server::_JOIN;
	_coms["PART"] = &Server::_PART;
	_coms["KICK"] = &Server::_KICK;
	_coms["INVITE"] = &Server::_INVITE;
	_coms["TOPIC"] = &Server::_TOPIC;
	_coms["MODE"] = &Server::_MODE;
}