#include <Server.hpp>

void	Server::_PRIVMSG(std::string command, std::string params, size_t client_i)
{
	(void)command;
	(void)params;
	(void)client_i;
	std::cout << GREEN << "Executing _PRIVMSG" << NC << "\n";
}

// void	Server::_NOTICE(std::string command, std::string params, size_t client_i)
// {
// 	(void)command;
// 	(void)params;
// 	(void)client_i;
// 	std::cout << GREEN << "Executing _NOTICE" << NC << "\n";
// }
