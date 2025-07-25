#include <Server.hpp>

void	Server::server_read(size_t poll_i)
{
	ssize_t	read;

	//Flag MSG_DONTWAIT if you want the operation to be non-blocking
	// read = recv(_pollfds[i].fd, _buff, BUFF_SIZE, MSG_DONTWAIT);
	read = recv(_pollfds[poll_i].fd, _buff, BUFF_SIZE, 0);
	if (read <= 0) {
		if (read == -1)
			std::cerr << RED << "Error trying to read from a client" << NC << std::endl;
		
		_clients[poll_i - 1].close_socket();
		if (!_clients[poll_i - 1].getReg())
			_clients_to_auth--;
		else
		{
			std::string	nick = _clients[poll_i - 1].getNick();
			std::vector<std::string>::iterator it = std::find(_client_nicks.begin(), _client_nicks.end(), nick);
			if (it != _client_nicks.end())
				_client_nicks.erase(it);
			for (size_t i = 0; i < _channels.size(); i++) {
				_channels[i].erraseMember(nick);
			}
		}
		_pollfds.erase(_pollfds.begin() + poll_i);
		_clients.erase(_clients.begin() + poll_i - 1);
		return;
	}
	_pollfds[poll_i].revents = 0;
	std::cout << CYAN << "Msg from client: " << _clients[poll_i - 1].getNick() << "\n"
		<< "length = " << read << "\n" << "[ " << _buff << " ]\n" << NC;
	parse_message(_buff, poll_i - 1);
	std::fill_n(_buff, read, 0);
}