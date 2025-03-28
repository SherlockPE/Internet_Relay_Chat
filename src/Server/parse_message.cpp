#include <Server.hpp>
#include <cstring>

void    Server::com_KICK(void)
{

}

void    Server::com_INVITE(void)
{

}

void    Server::com_TOPIC(void)
{

}

void    Server::com_MODE(void)
{

}



int	Server::select_command(std::string command)
{
	str_toupper(command);
	std::cout << YELLOW << "Select command function [" << command << "]" << NC << std::endl;
	if (!strcmp(command.c_str(), "KICK"))
        std::cout << "You have chossen KICK " << std::endl;
	if (!strcmp(command.c_str(), "INVITE"))
        std::cout << "You have chossen INVITE" << std::endl;
	if (!strcmp(command.c_str(), "TOPIC"))
        std::cout << "You have chossen  TOPIC" << std::endl;
	if (!strcmp(command.c_str(), "MODE"))
        std::cout << "You have chossen MODE " << std::endl;
	return (EXIT_SUCCESS);
}


int	Server::parse_message(std::string msg)
{
	for (size_t i = 0; i < msg.length(); i++)
	{
		while (strchr(" \n\t", msg[i]))
			i++;
		if (msg[i] == '/')
		{
			i++;
			if (select_command(&msg[i]))
				return (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}

