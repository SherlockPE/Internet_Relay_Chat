#include <Server.hpp>
#include <cstring>

void    /* Server:: */com_KICK(std::string command)
{

}

void    /* Server:: */com_INVITE(std::string command)
{

}

void    /* Server:: */com_TOPIC(std::string command)
{

}

void    /* Server:: */com_MODE(std::string command)
{

}



int	Server::select_command(std::string command)
{
	str_toupper(command);
	std::cout << YELLOW << "Select command function [" << command << "]" << NC << std::endl;
	if (!strcmp(command.c_str(), "KICK"))
        com_KICK(command);
	if (!strcmp(command.c_str(), "INVITE"))
        com_INVITE(command);
	if (!strcmp(command.c_str(), "TOPIC"))
        com_TOPIC(command);
	if (!strcmp(command.c_str(), "MODE"))
        com_MODE(command);
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

