#include <Server.hpp>

void	Server::server_accept(void)
{
	int			new_socket;
	pollfd		new_pollfd;
	sockaddr	address;
	socklen_t	address_len = sizeof(sockaddr);

	_pollfds[0].revents = 0;

	new_socket = accept(_pollfds[0].fd, &address, &address_len);
	if (new_socket == -1) {
		std::cerr << RED << "Error trying to accept a new client" << NC << std::endl;
		return;
	}
	if (address_len != sizeof(address)) {
		std::cerr << RED << "Error whith the client address" << NC << std::endl;
		return;
	}
	//Using fcntl to make the new socket non-blocking
	if (fcntl(new_socket, F_SETFL, O_NONBLOCK)) {
		std::cerr << RED << "Error trying to make a client non-block" << NC << std::endl;
		return;
	}
	
	new_pollfd.fd = new_socket;
	new_pollfd.events = POLLIN;
	new_pollfd.revents = 0;
	
	_pollfds.push_back(new_pollfd);
	_clients.push_back(Client(new_pollfd, ++_clients_number, address));
	_clients_to_auth++;
}