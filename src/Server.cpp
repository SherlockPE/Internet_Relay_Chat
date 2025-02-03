#include <Server.hpp>
#include <iostream>

// CONSTRUCTORS AND DESTRUCTORS-------------------------------------------------
// Server::Server(void)
// {
// 	std::cout << GREEN "Server default constructor called" NC << std::endl;
// }

Server::Server(int port, std::string password): m_port(port), m_password(password)
{
	std::cout << GREEN "Server default constructor called" NC << std::endl;
	initial_parse();
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

void	Server::initial_parse()
{
	if ()
}