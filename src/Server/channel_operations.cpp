#include <Server.hpp>

void	Server::_KICK(std::string command, std::string params, size_t client_i)
{
	(void)command;
	(void)params;
	(void)client_i;
	std::cout << GREEN << "Executing _KICK" << NC << "\n";
}

void	Server::_INVITE(std::string command, std::string params, size_t client_i)
{
	(void)command;
	(void)params;
	(void)client_i;
	std::cout << GREEN << "Executing _INVITE" << NC << "\n";
}

void	Server::_TOPIC(std::string command, std::string params, size_t client_i)
{
	(void)command;
	(void)params;
	(void)client_i;
	std::cout << GREEN << "Executing _TOPIC" << NC << "\n";
}

void	Server::_MODE(std::string command, std::string params, size_t client_i)
{
	(void)command;
	(void)params;
	(void)client_i;
	std::cout << GREEN << "Executing _MODE" << NC << "\n";
}

void	Server::_JOIN(std::string command, std::string params, size_t client_i)
{
	(void)command;
	(void)params;
	(void)client_i;
	std::cout << GREEN << "Executing _JOIN" << NC << "\n";
}

// void	Server::_PART(std::string command, std::string params, size_t client_i)
// {
// 	(void)command;
// 	(void)params;
// 	(void)client_i;
// 	std::cout << GREEN << "Executing _PART" << NC << "\n";
// }
