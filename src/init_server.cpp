#include <Server.hpp>
#include <sys/socket.h>
#include <poll.h>

// To accept connections, the following steps are performed:

//    (1)  A socket is created with socket().
//    (2)  The socket is bound to a local address using bind(), so
//         that other sockets may be connected to it.
//    (3)  A willingness to accept incoming connections and a queue
//         limit for incoming connections are specified with
//         listen().
//    (4)  The server then enters a loop to accept incoming connections.

void	Server::init_server(void)
{
	int			return_value;


	this->_fd_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (this->_fd_socket == -1)
		throw ("Error trying to display the socket (system error)");


	if (bind(this->_fd_socket, &this->_address, sizeof(sockaddr)) == -1)
		throw ("Error trying to bind the socket (system error)");


	if (listen(this->_fd_socket, 4000) == -1)
		throw ("Error trying to listen for socket (system error)");
	


	struct pollfd		pollfds[1];
	
	pollfds[0].fd = this->_fd_socket;
	pollfds[0].events = POLLIN;
	pollfds[0].revents = 0;
	while (true)
	{
		return_value = poll(pollfds, 1, -1);
		if (return_value == -1)
			throw ("Error trying to poll the socket (system error)");
		else if (return_value > 0)
		{
			// Poll was successful
			if (pollfds[0].revents & POLLIN)
			{
				this->_socket_len = sizeof(sockaddr);
				accept(this->_fd_socket, &this->_address, &this->_socket_len);
			}
		}
	}

//    (5)  When a connection is accepted, a new socket is created with
//         accept() and the address of the client is returned.
//         The server can communicate using the new socket and the
//         original socket continues to listen for new connections.

//    (6)  The connection is terminated using close() when finished.

}