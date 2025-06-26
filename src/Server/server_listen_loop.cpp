#include <Server.hpp>

void	Server::server_listen_loop(void)
{
	int			number_of_polls;
	
	while (true)
	{
		std::cout << WHITE "=============Clients============\n" NC;
		for (size_t i = 0; i < _client_nicks.size(); i++)
			std::cout << "Name [" << i << "] " << _client_nicks[i] << "\n";
		std::cout << WHITE "================================\n" NC;

		number_of_polls = poll(&_pollfds[0], _pollfds.size(), TIMEOUT);  
		if (number_of_polls == -1)
			std::cerr << RED << "Error trying to poll the socket" << NC << std::endl;
		else if (number_of_polls > 0)
		{
			std::cout << MAGENTA << "Number of polls: "<< number_of_polls << NC << "\n";
			for (size_t i = 0; i < _pollfds.size() && number_of_polls; i++)
			{
				if (_pollfds[i].revents & POLLIN)
				{
					if (i == 0)
						server_accept();
					else
						server_read(i);
					number_of_polls--;

				}
			}
		}
		if (_clients_to_auth)
			register_clients();
		for (size_t i = 0; i < _channels.size();) {
			if (_channels[i].isEmpty()) {
				for (size_t n = 0; n < _clients.size(); n++)
					_clients[n].removeInvite(_channels[i].getName());
				_channels.erase(_channels.begin() + i);
				continue;
			}
			i++;
		}
	}
}