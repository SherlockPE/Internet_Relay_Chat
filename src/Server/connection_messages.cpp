#include <Server.hpp>

void	Server::_PASS(std::string command, std::string params, size_t client_i)
{
	std::cout << GREEN << "Executing _PASS" << NC << "\n";

	if (_clients[client_i].getReg())
	{
		std::cout << RED << command << " ERR_ALREADYREGISTERED (462)" << NC << "\n";
		return;
	}
	if (params.empty())
	{
		std::cout << RED << command << " ERR_NEEDMOREPARAMS (461)" << NC << "\n";
		return;
	}
	if (params != _password)
	{
		std::cout << RED << command << " ERR_PASSWDMISMATCH (464)" << NC << "\n";
		return;
	}
	_clients[client_i].setPass(params);
}

void	Server::_NICK(std::string command, std::string params, size_t client_i)
{
	std::cout << GREEN << "Executing _NICK" << NC << "\n";
	if (_clients[client_i].getReg())
	{
		std::cout << RED << command << " ERR_ALREADYREGISTERED (462)" << NC << "\n";
		return;
	}
	if (params.empty())
	{
		std::cout << RED << command << " ERR_NONICKNAMEGIVEN (431)" << NC << "\n";
		return;
	}
	// find invalid chars
	if (params.find("=") != std::string::npos)
	{
		std::cout << RED << command << " ERR_ERRONEUSNICKNAME (432)" << NC << "\n";
		return;
	}
	if (std::find(_client_nicks.begin(), _client_nicks.end(), params) != _client_nicks.end())
	{
		std::cout << RED << command << " ERR_NICKNAMEINUSE (433)" << NC << "\n";
		return;
	}
	_clients[client_i].setNick(params);
}

void	Server::_USER(std::string command, std::string params, size_t client_i)
{
	std::cout << GREEN << "Executing _USER" << NC << "\n";
	if (_clients[client_i].getReg())
	{
		std::cout << RED << command << " ERR_ALREADYREGISTERED (462)" << NC << "\n";
		return;
	}
	if (params.empty())
	{
		std::cout << RED << command << " ERR_NEEDMOREPARAMS (461)" << NC << "\n";
		return;
	}

	std::string	username = params.substr(0, params.find(" "));
	std::string	realname = params.substr(params.find(":"));

	if (realname == "realname")
		realname = username;

	_clients[client_i].setUser(username);
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
