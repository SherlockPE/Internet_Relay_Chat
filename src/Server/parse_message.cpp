#include <Server.hpp>

// TODO: improve parsing of the command (optional)
void	Server::select_command(std::string command, size_t client_i)
{
	std::string	com;
	std::string	msg;
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
	if (it == _coms.end()) {
		std::cout << RED << com << " ERR_UNKNOWNCOMMAND (421)" << NC << "\n";
		// msg = ":42.irc 421 " + _clients[client_i].getNick() + " " + com + " :Unknown command\r\n";
		// send(_pollfds[client_i + 1].fd, msg.c_str(), msg.size(), 0);
		return;
	}

	std::cout << GREEN << "COMMAND FOUND: \"" << com << "\"" << NC << "\n";
	std::cout << GREEN << "COMMAND PARAMS: \"" << command << "\"" << NC << "\n";

	(this->*(it->second))(com, command, client_i);
}

void	Server::parse_message(std::string msg, size_t client_i)
{
	std::string	command;
	size_t	msg_pos;

	while (!msg.empty() || msg != "\r\n")
	{
		msg_pos = msg.find("\r\n");

		if (msg_pos == std::string::npos)
		{
			_clients[client_i].fillBuff(msg);
			return;
		}
		command = msg.substr(0, msg_pos);
		_clients[client_i].fillBuff(command);
		msg.erase(0, msg_pos + 2);
		command = _clients[client_i].readBuff();
		select_command(command, client_i);
		_clients[client_i].clearBuff();
	}
}

