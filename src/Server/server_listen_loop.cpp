#include <Server.hpp>

void	Server::server_listen_loop(void)
{
	int			number_of_polls;
	
	while (true)
	{
		number_of_polls = poll(&_pollfds[0], _pollfds.size(), -1);
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
	}
}