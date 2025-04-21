#include <Server.hpp>

void	Server::_PASS(std::string command, size_t client_i)
{
	(void)command;
	(void)client_i;
    std::cout << GREEN << "Executing _PASS" << NC << "\n";
}

void	Server::_NICK(std::string command, size_t client_i)
{
	(void)command;
	(void)client_i;
    std::cout << GREEN << "Executing _NICK" << NC << "\n";
}

void	Server::_USER(std::string command, size_t client_i)
{
	(void)command;
	(void)client_i;
    std::cout << GREEN << "Executing _USER" << NC << "\n";
}

void	Server::_PING(std::string command, size_t client_i)
{
	(void)command;
	(void)client_i;
    std::cout << GREEN << "Executing _PING" << NC << "\n";
}

void	Server::_PONG(std::string command, size_t client_i)
{
	(void)command;
	(void)client_i;
    std::cout << GREEN << "Executing _PONG" << NC << "\n";
}

void	Server::_OPER(std::string command, size_t client_i)
{
	(void)command;
	(void)client_i;
    std::cout << GREEN << "Executing _OPER" << NC << "\n";
}

void	Server::_QUIT(std::string command, size_t client_i)
{
	(void)command;
	(void)client_i;
    std::cout << GREEN << "Executing _QUIT" << NC << "\n";
}

void	Server::_ERROR(std::string command, size_t client_i)
{
	(void)command;
	(void)client_i;
    std::cout << GREEN << "Executing _ERROR" << NC << "\n";
}
