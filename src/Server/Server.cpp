#include <Server.hpp>
#include <iostream>


// CONSTRUCTORS AND DESTRUCTOR --------------------------------------------------

Server::Server(int port, std::string password): _port(port), _password(password)
{
	std::cout << GREEN << "Server intializing\n" << NC;
	std::cout << GREEN << "\n" << NC;
	std::cout << GREEN << "Port: " << _port << "\n" << NC;
	std::cout << GREEN << "Password: " << _password << "\n" << NC;
	std::cout << GREEN << "\n" << NC;

	time(&_init_timer);
	_init_time = gmtime(&_init_timer);
	_time_str = asctime(_init_time);
	_time_str.erase(_time_str.size() - 1, 1);
	std::cout << GREEN << "Server init time (UTC+0): " << _time_str << "\n" << NC;

	init_server();
	_clients_number = 0;
	_clients_to_auth = 0;

	std::cout << GREEN << "\nServer intialized:\n"
	<< "-> fd: [" << _pollfds[0].fd
	<< "]\n-> port: [" << ntohs(_address.sin_port)
	<< "]\n-> ip: [" << inet_ntoa(_address.sin_addr)
	<< "]\n" << NC;
	
	init_commands();

	server_listen_loop();
}

Server::~Server(void)
{
	std::cout << YELLOW << "Server closed" << NC << std::endl;
}
