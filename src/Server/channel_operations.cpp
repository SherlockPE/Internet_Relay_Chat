#include <Server.hpp>

// TODO: https://modern.ircdocs.horse/#kick-message
// TODO: Eject a client from the channel
void	Server::_KICK(std::string command, std::string params, size_t client_i)
{
	(void)command;
	(void)params;
	(void)client_i;
	std::cout << ITALIC MAGENTA "Usage: KICK <nick> [reason], kicks the nick from the current channel (needs chanop)";
	std::cout << GREEN << "Executing _KICK" << NC << "\n";
}

// TODO: https://modern.ircdocs.horse/#invite-message
// TODO: Invite a client to a channel
void	Server::_INVITE(std::string command, std::string params, size_t client_i)
{
	(void)command;
	(void)params;
	(void)client_i;
	std::cout << ITALIC MAGENTA "Usage: INVITE <nick> [<channel>], invites someone to a channel, by default the current channel (needs chanop)";
	std::cout << GREEN << "Executing _INVITE" << NC << "\n";
}

// TODO: https://modern.ircdocs.horse/#topic-message
// TODO: Change or view the channel topic
void	Server::_TOPIC(std::string command, std::string params, size_t client_i)
{
	(void)command;
	(void)params;
	(void)client_i;
	std::cout << GREEN << "Executing _TOPIC" << NC << "\n";
}

// TODO: https://modern.ircdocs.horse/#mode-message
// TODO: only change the channel modes:
	// i: Set/remove Invite-only channel
	// t: Set/remove the restrictions of the TOPIC command to channel operators
	// k: Set/remove the channel key (password)
	// o: Give/take channel operator privilege
	// l: Set/remove the user limit to channel
void	Server::_MODE(std::string command, std::string params, size_t client_i)
{
	(void)command;
	(void)params;
	(void)client_i;
	std::cout << GREEN << "Executing _MODE" << NC << "\n";
}

// TODO: inprove parsing (optional)
// TODO: implement ERR_TOOMANYCHANNELS (405) (optional)
// TODO: once KICK, INVITE, TOPIC and MODE are added, implement:
	// ERR_BADCHANNELKEY (475)
	// ERR_CHANNELISFULL (471)
	// ERR_INVITEONLYCHAN (473)
	// RPL_TOPIC (332) 
void	Server::_JOIN(std::string command, std::string params, size_t client_i)
{
	std::map<std::string, std::string>	channel_names_keys;
	std::string	channel_names;
	std::string	channel_keys;
	std::string	name;
	std::string	key;
	size_t	names_pos;
	size_t	keys_pos;
	std::string	msg;
	std::string	client_nick = _clients[client_i].getNick();

	std::cout << GREEN << "Executing _JOIN" << NC << "\n";
	if (!_clients[client_i].getReg())
	{
		std::cout << RED << command << " ERR_NOTREGISTERED (451)" << NC << "\n";
		msg = ":42.irc 451 " + client_nick + " :You have not registered\r\n";
		send(_pollfds[client_i + 1].fd, msg.c_str(), msg.size(), 0);
		return;
	}
	if (params.empty())
	{
		std::cout << RED << command << " ERR_NEEDMOREPARAMS (461)" << NC << "\n";
		msg = ":42.irc 461 " + client_nick + " " + command + " :Not enough parameters\r\n";
		send(_pollfds[client_i + 1].fd, msg.c_str(), msg.size(), 0);
		return;
	}
	names_pos = params.find(' ');
	channel_names = params.substr(0, names_pos);
	if (names_pos != std::string::npos)
	{
		names_pos++;
		keys_pos = params.find(' ', names_pos);
		channel_keys = params.substr(names_pos, keys_pos);
	}

	while (!channel_names.empty())
	{
		names_pos = channel_names.find(',');
		name = channel_names.substr(0, names_pos);
		if (names_pos != std::string::npos)
			names_pos++;
		channel_names.erase(0, names_pos);
		if (!channel_keys.empty())
		{
			keys_pos = channel_keys.find(',');
			key = channel_keys.substr(0, keys_pos);
			if (keys_pos != std::string::npos)
				keys_pos++;
			channel_keys.erase(0, keys_pos);
		}
		if (name[0] != '#')
		{
			std::cout << RED << command << " ERR_BADCHANMASK (476)" << NC << "\n";
			msg = ":42.irc 476 " + name + " :Bad Channel Mask\r\n";
			send(_pollfds[client_i + 1].fd, msg.c_str(), msg.size(), 0);
			continue;
		}
		if (!channel_keys.empty())
			channel_names_keys[name] = key;
		else
			channel_names_keys[name];
	}
	uint32_t	channel_found;
	std::map<std::string, std::string>::iterator it = channel_names_keys.begin();
	while (it != channel_names_keys.end())
	{
		channel_found = 0;
		std::cout << MAGENTA << "Channel: " << it->first
			<< " - Key: " << it->second << "\n" << NC;

		for (size_t i = 0; i < _channels.size(); i++) {
			if (it->first == _channels[i].getName()) {
				if (_channels[i].isMember(client_nick))
					std::cout << RED << "Channel " << it->first << " already joined" << NC << "\n";
				else if (_channels[i].getPass() == it->second)
				{
					_channels[i].addMember(client_nick);
					msg = ":" + client_nick + " JOIN " + it->first + "\r\n";
					send(_pollfds[client_i + 1].fd, msg.c_str(), msg.size(), 0);
				}
				else
				{
					std::cout << RED << command << " ERR_BADCHANNELKEY (475)" << NC << "\n";
					msg = ":42.irc 475 " + name + " " + it->first + " :Cannot join channel (+k)\r\n";
					send(_pollfds[client_i + 1].fd, msg.c_str(), msg.size(), 0);
				}
				channel_found = 1;
				break;
			}
		}
		if (channel_found) {
			it++;
			continue;
		}
		_channels.push_back(Channel(it->first, it->second));
		_channels.back().addMember(client_nick);
		_channels.back().addOperator(client_nick);
		msg = ":" + client_nick + " JOIN " + it->first + "\r\n";
		send(_pollfds[client_i + 1].fd, msg.c_str(), msg.size(), 0);
		it++;
	}
}

// void	Server::_PART(std::string command, std::string params, size_t client_i)
// {
// 	(void)command;
// 	(void)params;
// 	(void)client_i;
// 	std::cout << GREEN << "Executing _PART" << NC << "\n";
// }
