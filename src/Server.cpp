#include <Server.hpp>
#include <iostream>
#include <ctype.h>
#include <cstdlib>
#include <stdio.h>

// CONSTRUCTORS AND DESTRUCTORS-------------------------------------------------
// Server::Server(void)
// {
// 	std::cout << GREEN "Server default constructor called" NC << std::endl;
// }

Server::Server(int argc, char **argv)
{
	initial_parse(argc, argv);
}


Server::Server(Server const& other)
{
	std::cout << GREEN "Server copy constructor called" NC << std::endl;
	*this = other;
}

Server::~Server(void)
{
	std::cout << RED "Server destructor called" NC << std::endl;
}

// OPERATORS--------------------------------------------------------------------
Server& Server::operator=(Server const& other)
{
	if (this == &other)
		return (*this);
	// DO THINGS
	return (*this);
}

// METHODS AND MEMBER FUNCTIONS-------------------------------------------------

//Parse
void	Server::initial_parse(int argc, char **argv)
{
	if (argc != 3)
		throw (ErrorExcept("Wrong Arguments"));

	// Port 
	std::string port = argv[1];
	for (size_t i = 0; i < port.length(); i++)
	{
		if (!isdigit(port[i]))
			throw (ErrorExcept("The port must be compose by numbers"));
	}
	m_port = atoi(port.c_str());

	// Password
	m_password = argv[2];

	std::cout << GREEN <<  "Access granted" << NC << std::endl;
}