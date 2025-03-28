#include <Server.hpp>
#include <iostream>

int usage(int exit_code)
{
	std::cout	<< GREEN << "Usage: " << "\n"
				<< "./ircserv [port] [password]" << std::endl;
	return (exit_code);
}

int	exit_error(const char *message, int exit_code)
{
	std::cerr << RED << message << NC << std::endl;
	return (usage(exit_code));
}

int	main(int argc, char **argv)
{
	if (argc != 3)
		return exit_error("Invalid number of arguments", EXIT_FAILURE);

	std::string port = argv[1];
	size_t	port_len = std::count_if(port.begin(), port.end(), isdigit);
	if (port_len != port.length())
		return exit_error("Invalid port: non digit found", EXIT_FAILURE);
	
	std::string password = argv[2];
	if (password.empty())
		return exit_error("Invalid password: empty password", EXIT_FAILURE);

	try
	{
		Server	main_serv(to_int(port), password);
	}
	catch (std::exception &e)
	{
		std::cerr << RED << "Error\n" << e.what() << NC << std::endl;
	}
	return (EXIT_SUCCESS);
}
