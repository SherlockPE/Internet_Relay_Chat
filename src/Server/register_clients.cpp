#include <Server.hpp>

// TODO: increase the number of messages sent after registration (optional)
// TODO: implement the RPL_ISUPPORT numeric parameters (optional)
void	Server::register_clients(void)
{
	size_t	i = 0;
	std::string	msg;
	std::string	nick_name;

	while (i < _clients.size() && _clients_to_auth)
	{
		std::cout << WHITE "FD: [" << _pollfds[i + 1].fd << "]\n" << NC;
		if (_clients[i]._register(_client_nicks))
		{
			nick_name = _clients[i].getNick();
			_client_nicks.push_back(nick_name);
			_clients_to_auth--;
			std::cout << " RPL_WELCOME (001)\n RPL_YOURHOST (002)\n"
			<< " RPL_CREATED (003)\n RPL_MYINFO (004)\n RPL_ISUPPORT (005)\n";
			msg = "\\▄▖              \n▐ ▛▘▛▘          \n▟▖▌ ▙▖          \n                \n▌               \n▛▌▌▌            \n▙▌▙▌            \n  ▄▌            \n▄▖▜ ▌     ▗   ▜ \n▌▌▐ ▛▌▀▌▛▘▜▘▛▌▐ \n▛▌▐▖▙▌█▌▌ ▐▖▙▌▐▖\n                \n      ▗ ▗       \n      ▚▘▚▘      \n      ▚▌▚▌      \n                \n▐▘▜             \n▜▘▐ ▛▌▛▌█▌▀▌▄▖▛▘\n▐ ▐▖▙▌▙▌▙▖▙▖  ▌ \n      ▌         \n";
			msg += ":42.irc 001 " + nick_name + " :Welcome " + nick_name + "\r\n";
			msg += ":42.irc 002 " + nick_name + " :Your host is 42_IRC, running version 0.1" + "\r\n";
			msg += ":42.irc 003 " + nick_name + " :This server was created " + _time_str + "\r\n";
			msg += ":42.irc 004 " + nick_name + " 42_IRC 0.1\r\n";
			msg += ":42.irc 005 " + nick_name + " CASEMAPPING=ascii "
			+ "CHANNELLEN=64 CHANTYPES=# HOSTLEN=64 KICKLEN=255 MAXTARGETS=64 "
			+ "NICKLEN=64 TOPICLEN=255 USERLEN=64" + " :are supported by this server\r\n";
			send(_pollfds[i + 1].fd, msg.c_str(), msg.size(), 0);
		}
		i++;
	}
}
