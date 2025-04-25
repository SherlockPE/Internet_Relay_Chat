#include <Server.hpp>

void	Server::register_clients(void)
{
	size_t	i = 0;

	while (i < _clients.size() && _clients_to_auth)
	{
		std::cout << WHITE "FD: [" << _pollfds[i + 1].fd << "]\n" << NC;
		if (_clients[i]._register())
		{
			_client_nicks.push_back(_clients[i].getNick());
			_clients_to_auth--;
		}
		i++;
	}
}
