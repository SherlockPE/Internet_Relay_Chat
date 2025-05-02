#include <Server.hpp>

void	Server::_PRIVMSG(std::string command, std::string params, size_t client_i)
{
	std::string	dest;
	size_t	dest_pos;
	std::string	msg;
	std::string	client_nick = _clients[client_i].getNick();

	std::cout << GREEN << "Executing _PRIVMSG" << NC << "\n";
	if (!_clients[client_i].getReg()) {
		std::cout << RED << command << " ERR_NOTREGISTERED (451)" << NC << "\n";
		msg = ":42.irc 451 " + client_nick + " :You have not registered\r\n";
		send(_pollfds[client_i + 1].fd, msg.c_str(), msg.size(), 0);
		return;
	}
	if (params.empty()) {
		std::cout << RED << command << " ERR_NEEDMOREPARAMS (461)" << NC << "\n";
		msg = ":42.irc 461 " + client_nick + " " + command + " :Not enough parameters\r\n";
		send(_pollfds[client_i + 1].fd, msg.c_str(), msg.size(), 0);
		return;
	}
	dest_pos = params.find(' ');
	dest = params.substr(0, dest_pos);
	if (dest_pos == std::string::npos) {
		std::cout << RED << command << " ERR_NEEDMOREPARAMS (461)" << NC << "\n";
		msg = ":42.irc 461 " + client_nick + " " + command + " :Not enough parameters\r\n";
		send(_pollfds[client_i + 1].fd, msg.c_str(), msg.size(), 0);
		return;
	}
	if (dest[0] == '#') {
		for (size_t i = 0; i < _channels.size(); i++) {
			if (_channels[i].getName() == dest) {
				if (!_channels[i].isMember(client_nick)) {
					std::cout << RED << command << "   ERR_CANNOTSENDTOCHAN (404) " << NC << "\n";
					msg = ":42.irc 404 " + client_nick + " " + dest + " :Cannot send to channel\r\n";
					send(_pollfds[client_i + 1].fd, msg.c_str(), msg.size(), 0);
					return;
				}
				msg = ":" + client_nick + " " + command + " " + params + "\r\n";
				for (size_t n = 0; n < _clients.size(); n++) {
					if (_clients[n].getNick() != client_nick && _channels[i].isMember(_clients[n].getNick()))
						send(_pollfds[n + 1].fd, msg.c_str(), msg.size(), 0);
				}
				return;
			}
		}
	}
	else {
		for (size_t i = 0; i < _clients.size(); i++) {
			if (_clients[i].getReg() && _clients[i].getNick() == dest) {
				msg = ":" + client_nick + " " + command + " " + params + "\r\n";
				send(_pollfds[i + 1].fd, msg.c_str(), msg.size(), 0);
				return;
			}
		}
	}
	std::cout << RED << command << "  ERR_NOSUCHNICK (401)" << NC << "\n";
	msg = ":42.irc 401 " + client_nick + " " + dest + " :No such nick/channel\r\n";
	send(_pollfds[client_i + 1].fd, msg.c_str(), msg.size(), 0);
}

// void	Server::_NOTICE(std::string command, std::string params, size_t client_i)
// {
// 	(void)command;
// 	(void)params;
// 	(void)client_i;
// 	std::cout << GREEN << "Executing _NOTICE" << NC << "\n";
// }
