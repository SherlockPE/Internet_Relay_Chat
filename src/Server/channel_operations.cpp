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
		return;
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
		return;
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
				return;
			}
			msg = dest_chan + " :You're not channel operator";
			_clients[client_i].sendToClient(msg, 482);
			return;
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
		return;
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
				return;
			}
			if (new_topic == old_topic)
				return;
			is_oper = _channels[i].isOperator(client_nick);
			oper_needed = _channels[i].getTopicMode();
			if (oper_needed && !is_oper)
			{
				msg = dest_chan + " :You're not channel operator";
				_clients[client_i].sendToClient(msg, 482);
				return;
			}
			_channels[i].setTopic(new_topic);
			msg = ":42.irc TOPIC " + dest_chan + " :" + new_topic;
			for (size_t n = 0; n < _clients.size(); n++) {
				if (_channels[i].isMember(_clients[n].getNick()))
					send(_pollfds[n + 1].fd, msg.c_str(), msg.size(), 0);
			}
			return;
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
		return;
	params.erase(0, pos + 1);
	
	pos = params.find(' ');
	dest_chan = params.substr(0, pos);
	if (pos == std::string::npos)
		return;

	for (size_t i = 0; i < _channels.size(); i++)
	{
		if (_channels[i].getName() == dest_chan)
		{
			if (!_channels[i].isMember(client_nick))
			{
				msg = dest_chan + " :You're not on that channel";
				_clients[client_i].sendToClient(msg, 442);
				return;
			}
			is_oper = _channels[i].isOperator(client_nick);
			oper_needed = _channels[i].getInviteMode();
			if (oper_needed && !is_oper)
			{
				msg = dest_chan + " :You're not channel operator";
				_clients[client_i].sendToClient(msg, 482);
				return;
			}
			if (_channels[i].isMember(dest_client))
			{
				msg = dest_client + " " + dest_chan + " :Is already on channel";
				_clients[client_i].sendToClient(msg, 443);
				return;
			}
			msg = ":" + client_nick + " INVITE " + dest_client + dest_chan;
			size_t n = search_client_by_name(dest_client);
			if (n < _clients.size())
			{
				_clients[n].addInvite(dest_chan);
				send(_pollfds[n + 1].fd, msg.c_str(), msg.size(), 0);
			}
			msg = dest_client + dest_chan;
			_clients[client_i].sendToClient(msg, 341);
		}
		msg = dest_chan + " :No such channel";
		_clients[client_i].sendToClient(msg, 403);
	}
}

static bool	check_mode_str(std::string mode_string)
{
	if (mode_string[0] != '-' && mode_string[0] != '+')
		return true;
	if (mode_string.back() == '+' || mode_string.back() == '-')
		return true;
	if (mode_string.find_first_not_of("itkol+-") != std::string::npos)
		return true;
	if (mode_string.find_first_not_of("+-") == std::string::npos)
		return true;
	if (mode_string.size() <= 1)
		return true;
	if (mode_string[1] == '+' || mode_string[1] == '-')
		return true;
	if (std::count(mode_string.begin(), mode_string.end(), '+') > 1)
		return true;
	if (std::count(mode_string.begin(), mode_string.end(), '-') > 1)
		return true;

	return false;
}
static void	remove_modes(std::string &modes_to_remove, Channel &chan, Client &client, std::string &dest_chan, std::string &params)
{
	std::string msg;
	std::string mode_param;
	size_t	pos;

	for (size_t n = 1; n < modes_to_remove.size(); n++) {
		if (modes_to_remove[n] == 'i') {
			chan.setInviteMode(false);
		}
		else if (modes_to_remove[n] == 't') {
			chan.setTopicMode(false);
		}
		else if (modes_to_remove[n] == 'k') {
			chan.setPass("");
		}
		else if (modes_to_remove[n] == 'o') {
			pos = params.find(' ');
			mode_param = params.substr(0, pos);
			if (pos == std::string::npos)
				params.erase(0, pos);
			else
				params.erase(0, pos + 1);

			if (chan.isOperator(mode_param))
				chan.erraseOperator(mode_param);
			else {
				msg = dest_chan + " -o " + mode_param + " :User is not an operator";
				client.sendToClient(msg, 696);
			}
		}
		else if (modes_to_remove[n] == 'l') {
			chan.setUserLimit(0);
		}
	}
}
static bool is_not_print(unsigned char c) {
    return !std::isprint(c);
}
static void	add_modes(std::string &modes_to_add, Channel &chan, Client &client, std::string &dest_chan, std::string &params)
{
	std::string msg;
	std::string mode_param;
	size_t	pos;
	size_t	user_limit;

	for (size_t n = 1; n < modes_to_add.size(); n++) {
		if (modes_to_add[n] == 'i') {
			chan.setInviteMode(true);
		}
		else if (modes_to_add[n] == 't') {
			chan.setTopicMode(true);
		}
		else if (modes_to_add[n] == 'k') {
			pos = params.find(' ');
			mode_param = params.substr(0, pos);
			if (pos == std::string::npos)
				params.erase(0, pos);
			else
				params.erase(0, pos + 1);

			if (std::count_if(mode_param.begin(), mode_param.end(), is_not_print) == 0)
				chan.setPass(mode_param);
			else {
				msg = dest_chan + " +k " + mode_param + " :Invalid channel key";
				client.sendToClient(msg, 696);
			}
		}
		else if (modes_to_add[n] == 'o') {
			pos = params.find(' ');
			mode_param = params.substr(0, pos);
			if (pos == std::string::npos)
				params.erase(0, pos);
			else
				params.erase(0, pos + 1);

			if (chan.isOperator(mode_param))
				chan.erraseOperator(mode_param);
			else {
				msg = dest_chan + " +o " + mode_param + " :User is not an operator";
				client.sendToClient(msg, 696);
			}
		}
		else if (modes_to_add[n] == 'l') {
			pos = params.find(' ');
			mode_param = params.substr(0, pos);
			if (pos == std::string::npos)
				params.erase(0, pos);
			else
				params.erase(0, pos + 1);

			user_limit = to_int(mode_param);
			if (user_limit > 0)
				chan.setUserLimit(user_limit);
			else {
				msg = dest_chan + " +l " + mode_param + " :Invalid user limit";
				client.sendToClient(msg, 696);
			}
		}
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
	std::string modes_to_add;
	std::string modes_to_remove;
	std::string	client_nick = _clients[client_i].getNick();

	std::cout << GREEN << "Executing " << command << NC << "\n";
	if (params.empty())
		_clients[client_i].sendToClient(":Not enough parameters", 461);

	size_t pos = params.find(' ');
	dest_chan = params.substr(0, pos);
	if (pos == std::string::npos)
		return;
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
				return;
			}
			if (mode_string.empty())
			{
				// RPL_CHANNELMODIS (324)
				mode_string = _channels[i].getModeString();
				msg = dest_chan + " " + mode_string;
				_clients[client_i].sendToClient(msg, 324);
				return;
			}
			if (_channels[i].isOperator(client_nick))
			{
				msg = dest_chan + " :You're not channel operator";
				_clients[client_i].sendToClient(msg, 482);
				return;
			}
			// ERR_INVALIDMODEPARAM (696)
			// "<client> <target chan/user> <mode char> <parameter> :<description>"
			if (check_mode_str(mode_string))
			{
				msg = dest_chan + " " + mode_string + " :Invalid mode parameters";
				_clients[client_i].sendToClient(msg, 696);
				return;
			}
			if (mode_string[0] != '-')
			{
				pos = mode_string.find('+');
				modes_to_remove = mode_string.substr(0, pos);
				if (pos < std::string::npos)
					modes_to_add = mode_string.substr(pos + 1);
				remove_modes(modes_to_remove, _channels[i], _clients[client_i], dest_chan, params);
				add_modes(modes_to_add, _channels[i], _clients[client_i], dest_chan, params);				
			}
			else
			{
				pos = mode_string.find('-');
				modes_to_add = mode_string.substr(0, pos);
				if (pos < std::string::npos)
					modes_to_remove = mode_string.substr(pos + 1);
				add_modes(modes_to_add, _channels[i], _clients[client_i], dest_chan, params);
				remove_modes(modes_to_remove, _channels[i], _clients[client_i], dest_chan, params);
			}
			return;
		}
		msg = dest_chan + " :No such channel";
		_clients[client_i].sendToClient(msg, 403);
	}
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
				else if (_channels[i].getMemberNum() >= _channels[i].getUserLimit())
				{
					std::cout << RED << command << " ERR_CHANNELISFULL (471)" << NC << "\n";
					msg = ":42.irc 471 " + name + " " + it->first + " :Cannot join channel, user limit reached\r\n";
					send(_pollfds[client_i + 1].fd, msg.c_str(), msg.size(), 0);
				}
				else if (!_channels[i].getPass().empty() && _channels[i].getPass() != it->second)
				{
					std::cout << RED << command << " ERR_BADCHANNELKEY (475)" << NC << "\n";
					msg = ":42.irc 475 " + name + " " + it->first + " :Cannot join channel, bad password\r\n";
					send(_pollfds[client_i + 1].fd, msg.c_str(), msg.size(), 0);
				}
				else if (_channels[i].getInviteMode() && !_clients[client_i].isInvited(it->first))
				{
					std::cout << RED << command << " ERR_INVITEONLYCHAN (473)" << NC << "\n";
					msg = ":42.irc 473 " + name + " " + it->first + " :Cannot join channel, invite needed\r\n";
					send(_pollfds[client_i + 1].fd, msg.c_str(), msg.size(), 0);
				}
				else
				{
					_channels[i].addMember(client_nick);
					_clients[client_i].removeInvite(it->first);
					msg = ":" + client_nick + " JOIN " + it->first + "\r\n";
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
