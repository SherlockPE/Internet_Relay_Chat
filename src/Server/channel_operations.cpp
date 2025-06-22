#include <Server.hpp>

// TODO: https://modern.ircdocs.horse/#kick-message
// TODO: Eject a client from the channel
void	Server::_KICK(std::string command, std::string params, size_t client_i)
{
	std::string msg; 
	std::string dest_chan;
	std::string client_target;
	size_t		client_target_id;
	std::string	client_nick = _clients[client_i].getNick();

	std::cout << GREEN << "Executing " << command << NC << "\n";
	if (params.empty())
		_clients[client_i].sendToClient(":Not enough parameters", 461);

	size_t pos = params.find(' ');
	if (pos == std::string::npos)
		return ;
	dest_chan = params.substr(0, pos); // <-- Canal de destino
	params.erase(0, pos + 1);

	pos = params.find(' ');
	client_target = params.substr(0, pos); // <-- Objetivo del ban :D
	if (pos == std::string::npos)
		params = ":you have been banned";
	else
		params.erase(0, pos + 1);
	if (client_target == client_nick)
	{
		msg = command + " " + dest_chan + " " + client_target + " :You can't kick yourself, don't be a dummy\r\n";
		_clients[client_i].sendToClient(msg, 0);
		return ;
	}
	for (size_t i = 0; i < _channels.size(); i++)
	{
		if ((_channels[i].getName() == dest_chan))
		{
			if (_channels[i].isOperator(client_nick))
			{
				if (_channels[i].erraseMember(client_target))
				{
					// Notificacion al baneado de que ha sido baneado ;D
					client_target_id = search_client_by_name(client_target);
					msg = ":42.irc " + command + " " + dest_chan + " " + client_target + " " + params + "\r\n";
					send(_pollfds[client_target_id + 1].fd, msg.c_str(), msg.size(), 0);
					msg = dest_chan + "User: [" + client_target + "] " + "has been banned for: " + params ;
					_clients[client_i].sendToClient(msg, 0);
				}
				else
				{
					msg = dest_chan + " :They aren't on that channel";
					_clients[client_i].sendToClient(msg, 441);
				}
				return ;
			}
			msg = dest_chan + " :You're not channel operator";
			_clients[client_i].sendToClient(msg, 482);
			return ;
		} 
	}
}

// TODO: https://modern.ircdocs.horse/#topic-message
// TODO: Change or view the channel topic
void	Server::_TOPIC(std::string command, std::string params, size_t client_i)
{
	std::string msg;
	std::string dest_chan;
	std::string new_topic;
	std::string old_topic;
	std::string	client_nick = _clients[client_i].getNick();
	bool	show_topic = false;
	bool	is_oper;
	bool	oper_needed;

	std::cout << GREEN << "Executing " << command << NC << "\n";
	if (params.empty())
		_clients[client_i].sendToClient(":Not enough parameters", 461);

	size_t pos = params.find(' ');
	if (pos == std::string::npos)
		return ;
	dest_chan = params.substr(0, pos);
	params.erase(0, pos + 1);

	pos = params.find(' ');
	new_topic = params.substr(0, pos);
	if (pos == std::string::npos)
		show_topic = true;
	for (size_t i = 0; i < _channels.size(); i++)
	{
		if ((_channels[i].getName() == dest_chan))
		{
			old_topic = _channels[i].getTopic();
			if (show_topic)
			{
				if (old_topic.empty())
				{
					// RPL_NOTOPIC (331)
					msg = dest_chan + " :No topic is set";
					_clients[client_i].sendToClient(msg, 331);
				}
				else
				{
					// RPL_TOPIC (332)
					msg = dest_chan + " :" + old_topic;
					_clients[client_i].sendToClient(msg, 332);
				}
				return ;
			}
			if (new_topic == old_topic)
				return ;
			is_oper = _channels[i].isOperator(client_nick);
			oper_needed = _channels[i].getTopicMode();
			if (oper_needed && !is_oper)
			{
				msg = dest_chan + " :You're not channel operator";
				_clients[client_i].sendToClient(msg, 482);
				return ;
			}
			_channels[i].setTopic(new_topic);
			msg = ":42.irc TOPIC " + dest_chan + " :" + new_topic;
			for (size_t n = 0; n < _clients.size(); n++) {
				if (_channels[i].isMember(_clients[n].getNick()))
					send(_pollfds[n + 1].fd, msg.c_str(), msg.size(), 0);
			}
			return ;
		} 
	}
	msg = dest_chan + " :No such channel";
	_clients[client_i].sendToClient(msg, 403);
}

// TODO: https://modern.ircdocs.horse/#invite-message
// TODO: Invite a client to a channel
void	Server::_INVITE(std::string command, std::string params, size_t client_i)
{
	std::string msg;
	std::string dest_chan;
	std::string dest_client;
	std::string	client_nick = _clients[client_i].getNick();
	bool	is_oper;
	bool	oper_needed;

	std::cout << GREEN << "Executing " << command << NC << "\n";
	if (params.empty())
		_clients[client_i].sendToClient(":Not enough parameters", 461);

	size_t pos = params.find(' ');
	dest_client = params.substr(0, pos);
	if (pos == std::string::npos)
		return ;
	params.erase(0, pos + 1);
	
	pos = params.find(' ');
	dest_chan = params.substr(0, pos);
	if (pos == std::string::npos)
		return ;

	for (size_t i = 0; i < _channels.size(); i++)
	{
		if (_channels[i].getName() == dest_chan)
		{
			if (!_channels[i].isMember(client_nick))
			{
				msg = dest_chan + " :You're not on that channel";
				_clients[client_i].sendToClient(msg, 442);
				return ;
			}
			is_oper = _channels[i].isOperator(client_nick);
			oper_needed = _channels[i].getInviteMode();
			if (oper_needed && !is_oper)
			{
				msg = dest_chan + " :You're not channel operator";
				_clients[client_i].sendToClient(msg, 482);
				return ;
			}
			if (_channels[i].isMember(dest_client))
			{
				msg = dest_client + " " + dest_chan + " :Is already on channel";
				_clients[client_i].sendToClient(msg, 443);
				return ;
			}
			msg = ":" + client_nick + " INVITE " + dest_client + dest_chan;
			size_t n = search_client_by_name(dest_client);
			if (n < _clients.size())
				send(_pollfds[n + 1].fd, msg.c_str(), msg.size(), 0);
			msg = dest_client + dest_chan;
			_clients[client_i].sendToClient(msg, 341);
		}
		msg = dest_chan + " :No such channel";
		_clients[client_i].sendToClient(msg, 403);
	}
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
	std::string msg;
	std::string dest_chan;
	std::string mode_string;
	std::string	client_nick = _clients[client_i].getNick();
	bool	is_oper;
	bool	oper_needed;

	std::cout << GREEN << "Executing " << command << NC << "\n";
	if (params.empty())
		_clients[client_i].sendToClient(":Not enough parameters", 461);

	size_t pos = params.find(' ');
	dest_chan = params.substr(0, pos);
	if (pos == std::string::npos)
		return ;
	params.erase(0, pos + 1);
	
	pos = params.find(' ');
	if (pos < std::string::npos)
	{
		mode_string = params.substr(0, pos);
		params.erase(0, pos + 1);
	}

	for (size_t i = 0; i < _channels.size(); i++)
	{
		if (_channels[i].getName() == dest_chan)
		{
			if (!_channels[i].isMember(client_nick))
			{
				msg = dest_chan + " :You're not on that channel";
				_clients[client_i].sendToClient(msg, 442);
				return ;
			}
			if (mode_string.empty())
			{
				// RPL_CHANNELMODIS (324)
				mode_string = _channels[i].getModeString();
				params = _channels[i].getModeArg();
				msg = ":42.irc 324 " + client_nick + " " + dest_chan + " " + mode_string + " " + params + "\r\n";
			}
			is_oper = _channels[i].isOperator(client_nick);
			oper_needed = _channels[i].getInviteMode();
			if (oper_needed && !is_oper)
			{
				msg = dest_chan + " :You're not channel operator";
				_clients[client_i].sendToClient(msg, 482);
				return ;
			}

		}
		msg = dest_chan + " :No such channel";
		_clients[client_i].sendToClient(msg, 403);
	}
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
	bool	is_key;
	
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
		is_key = false;
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
			is_key = true;
		}
		if (name[0] != '#')
		{
			std::cout << RED << command << " ERR_BADCHANMASK (476)" << NC << "\n";
			msg = ":42.irc 476 " + name + " :Bad Channel Mask\r\n";
			send(_pollfds[client_i + 1].fd, msg.c_str(), msg.size(), 0);
			continue;
		}
		if (is_key)
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
				else if (_channels[i].getPass().empty() || _channels[i].getPass() == it->second)
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
