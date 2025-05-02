#include <Server.hpp>

// void	Server::select_command(std::string command, size_t client_i)
// {
// 	str_toupper(command);
// 	std::cout << YELLOW << "COMMAND: \"" << command << "\"" << NC << "\n";

// 	if (!strcmp(command.c_str(), "KICK "))
// 		com_KICK(command);
// 	if (!strcmp(command.c_str(), "INVITE "))
// 		com_INVITE(command);
// 	if (!strcmp(command.c_str(), "TOPIC "))
// 		com_TOPIC(command);
// 	if (!strcmp(command.c_str(), "MODE "))
// 		com_MODE(command);
// 	return;
// }

void	Server::select_command(std::string command, size_t client_i)
{
	std::string	com;
	size_t	com_pos;
	std::map<std::string, com_fn>::iterator it;
	
	std::cout << YELLOW << "MESSAGE: \"" << command << "\"" << NC << "\n";

	com_pos = command.find(' ');
	com = command.substr(0, com_pos);
	if (com_pos != std::string::npos)
		com_pos++;
	command.erase(0, com_pos);
	
	std::cout << YELLOW << "COMMAND: \"" << com << "\"" << NC << "\n";

	it = _coms.find(com);
	if (it == _coms.end())
		return;

	std::cout << GREEN << "COMMAND FOUND: \"" << com << "\"" << NC << "\n";
	std::cout << GREEN << "COMMAND PARAMS: \"" << command << "\"" << NC << "\n";

	(this->*(it->second))(com, command, client_i);
}

void	Server::parse_message(std::string msg, size_t client_i)
{
	std::string	command;
	size_t	msg_pos;
	// size_t	com_pos;

	while (!msg.empty() || msg != "\r\n")
	{
		msg_pos = msg.find("\r\n");

		if (msg_pos == std::string::npos)
			return;

		command = msg.substr(0, msg_pos);
		msg.erase(0, msg_pos + 2);

		select_command(command, client_i);
		// com_pos = command.find_first_not_of(" \n\t");
		// if (com_pos != std::string::npos)
		// 	select_command(command.substr(com_pos));
	}
}

