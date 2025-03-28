#include <Server.hpp>

// METHODS AND MEMBER FUNCTIONS ------------------------------------------------


// To accept connections, the following steps are performed:

//    (1)  A socket is created with socket().
//    (2)  The socket is bound to a local address using bind(), so
//         that other sockets may be connected to it.
//    (3)  A willingness to accept incoming connections and a queue
//         limit for incoming connections are specified with
//         listen().
//    (4)  The server then enters a loop to accept incoming connections.
//    (5)  When a connection is accepted, a new socket is created with
//         accept() and the address of the client is returned.
//         The server can communicate using the new socket and the
//         original socket continues to listen for new connections.
//    (6)  The connection is terminated using close() when finished.

void	Server::init_server(void)
{
	int			tcp_socket;
	sockaddr_in	address;

	tcp_socket = socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, 0);
	if (tcp_socket == -1)
		throw ErrorExcept("Error trying to display the socket (system error)");

	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(_port);
	std::cout << GREEN << "Network port: " << address.sin_port << "\n" << NC;

	if (bind(tcp_socket, (sockaddr *)&address, sizeof(address)) == -1)
		throw ErrorExcept("Error trying to bind the socket (system error)");

	if (listen(tcp_socket, QUEUE_SIZE) == -1)
		throw ErrorExcept("Error trying to listen for socket (system error)");
	
	pollfd new_pollfd;
	new_pollfd.fd = tcp_socket;
	new_pollfd.events = POLLIN;
	new_pollfd.revents = 0;
	_pollfds.push_back(new_pollfd);
}
