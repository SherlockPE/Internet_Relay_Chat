#include <Server.hpp>

void	Server::register_clients(void)
{
	size_t	i = 0;

	while (i < _clients.size() && _clients_to_auth)
	{
		if (_clients[i]._register())
		{
			_client_nicks.push_back(_clients[i].getNick());
			_clients_to_auth--;
		}
		i++;
	}
}
