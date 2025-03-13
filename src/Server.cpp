#include <Server.hpp>
#include <iostream>

// CONSTRUCTOR AND DESTRUCTOR --------------------------------------------------

Server::Server(int port, std::string password): _port(port), _password(password)
{
	std::cout << GREEN << "Server intializing\n" << NC;
	std::cout << GREEN << "\n" << NC;
	std::cout << GREEN << "Port: " << _port << "\n" << NC;
	std::cout << GREEN << "Password: " << _password << "\n" << NC;
	std::cout << GREEN << "\n" << NC;

	init_server();
	_clients_number = 0;

	std::cout << GREEN << "\n" << NC;
	std::cout << GREEN << "Server intialized\n" << NC << std::endl;

	server_listen_loop();
}

Server::~Server(void)
{

	std::cout << YELLOW << "Server closed" << NC << std::endl;
}

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
}

void	Server::server_read(size_t i)
{
	ssize_t	read;

	//Flag MSG_DONTWAIT if you want the operation to be non-blocking
	// read = recv(_pollfds[i].fd, _buff, BUFF_SIZE, MSG_DONTWAIT);
	read = recv(_pollfds[i].fd, _buff, BUFF_SIZE, 0);
	if (read <= 0) {
		if (read == -1)
			std::cerr << RED << "Error trying to read from a client" << NC << std::endl;
		
		_clients[i - 1].close_socket();
		_pollfds.erase(_pollfds.begin() + i);
		_clients.erase(_clients.begin() + i - 1);
		return;
	}
	for (size_t n = 1; n < _pollfds.size(); n++) {
		if (i == n)
			continue;
		// send(_pollfds[n].fd, _buff, read, MSG_DONTWAIT);
		send(_pollfds[n].fd, _buff, read, 0);
	}
	std::cout << CYAN << "Msg from client: " << _pollfds[i].fd << "\n"
		<< "length = " << read << "\n" << "[ " << _buff << " ]\n" << NC;
	std::fill_n(_buff, read, 0);
	_pollfds[i].revents = 0;
}