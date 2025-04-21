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

	init_server();
	_clients_number = 0;

	init_commands();

	std::cout << GREEN << "\nServer intialized\n" << NC << std::endl;
	server_listen_loop();
}

Server::~Server(void)
{
	std::cout << YELLOW << "Server closed" << NC << std::endl;
}
