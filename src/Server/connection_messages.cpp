#include <Server.hpp>

void	Server::_PASS(std::string command, std::string params, size_t client_i)
{
	std::string	msg;
	std::string	client_nick = _clients[client_i].getNick();

	std::cout << GREEN << "Executing _PASS" << NC << "\n";

	if (_clients[client_i].getReg())
	{
		std::cout << RED << command << " ERR_ALREADYREGISTERED (462)" << NC << "\n";
		msg = ":42.irc 462 " + client_nick + " :You may not reregister\r\n";
		send(_pollfds[client_i + 1].fd, msg.c_str(), msg.size(), 0);
		return;
	}
	if (params.empty())
	{
		std::cout << RED << command << " ERR_NEEDMOREPARAMS (461)" << NC << "\n";
		msg = ":42.irc 461 " + client_nick + " " + command + " :Not enough parameters\r\n";
		send(_pollfds[client_i + 1].fd, msg.c_str(), msg.size(), 0);
		return;
	}
	if (params != _password)
	{
		std::cout << RED << command << " ERR_PASSWDMISMATCH (464)" << NC << "\n";
		msg = ":42.irc 464 " + client_nick + " :Password incorrect\r\n";
		send(_pollfds[client_i + 1].fd, msg.c_str(), msg.size(), 0);
		return;
	}
	_clients[client_i].setPass(params);
}

void	Server::_NICK(std::string command, std::string params, size_t client_i)
{
	std::string	msg;
	std::string	client_nick = _clients[client_i].getNick();

	std::cout << GREEN << "Executing _NICK" << NC << "\n";

	if (params.empty())
	{
		std::cout << RED << command << " ERR_NONICKNAMEGIVEN (431)" << NC << "\n";
		msg = ":42.irc 431 " + client_nick + " :No nickname given\r\n";
		send(_pollfds[client_i + 1].fd, msg.c_str(), msg.size(), 0);
		return;
	}
	if (params.find("=#&%$@:") != std::string::npos)
	{
		std::cout << RED << command << " ERR_ERRONEUSNICKNAME (432)" << NC << "\n";
		msg = ":42.irc 432 " + client_nick + " " + client_nick + " :Erroneus nickname\r\n";
		send(_pollfds[client_i + 1].fd, msg.c_str(), msg.size(), 0);
		return;
	}
	if (std::find(_client_nicks.begin(), _client_nicks.end(), params) != _client_nicks.end())
	{
		std::cout << RED << command << " ERR_NICKNAMEINUSE (433)" << NC << "\n";
		msg = ":42.irc 433 " + client_nick + " " + client_nick + " :Nickname is already in use\r\n";
		send(_pollfds[client_i + 1].fd, msg.c_str(), msg.size(), 0);
		return;
	}
	_clients[client_i].setNick(params);
}

// TODO: parse the user params (optional)
void	Server::_USER(std::string command, std::string params, size_t client_i)
{
	std::string	msg;
	std::string	client_nick = _clients[client_i].getNick();

	std::cout << GREEN << "Executing _USER" << NC << "\n";

	if (_clients[client_i].getReg())
	{
		std::cout << RED << command << " ERR_ALREADYREGISTERED (462)" << NC << "\n";
		msg = ":42.irc 462 " + client_nick + " :You may not reregister\r\n";
		send(_pollfds[client_i + 1].fd, msg.c_str(), msg.size(), 0);
		return;
	}
	if (params.empty())
	{
		std::cout << RED << command << " ERR_NEEDMOREPARAMS (461)" << NC << "\n";
		msg = ":42.irc 461 " + client_nick + " " + command + " :Not enough parameters\r\n";
		send(_pollfds[client_i + 1].fd, msg.c_str(), msg.size(), 0);
		return;
	}

	std::string	username = params.substr(0, params.find(" "));
	std::string	realname = params.substr(params.find(":"));

	if (realname == "realname")
		realname = username;

	_clients[client_i].setUser(username);
	_clients[client_i].setRealName(realname);
}

// void	Server::_PING(std::string command, std::string params, size_t client_i)
// {
// 	(void)command;
// 	(void)params;
// 	(void)client_i;
//	std::cout << GREEN << "Executing _PING" << NC << "\n";
// }

// void	Server::_PONG(std::string command, std::string params, size_t client_i)
// {
// 	(void)command;
// 	(void)params;
// 	(void)client_i;
//	std::cout << GREEN << "Executing _PONG" << NC << "\n";
// }

//TODO: Will this message be needed? (optional)
void	Server::_OPER(std::string command, std::string params, size_t client_i)
{
	(void)command;
	(void)params;
	(void)client_i;
	std::cout << GREEN << "Executing _OPER" << NC << "\n";
}

// void	Server::_QUIT(std::string command, std::string params, size_t client_i)
// {
// 	(void)command;
// 	(void)params;
// 	(void)client_i;
//	std::cout << GREEN << "Executing _QUIT" << NC << "\n";
// }

// void	Server::_ERROR(std::string command, std::string params, size_t client_i)
// {
// 	(void)command;
// 	(void)params;
// 	(void)client_i;
//	std::cout << GREEN << "Executing _ERROR" << NC << "\n";
// }
