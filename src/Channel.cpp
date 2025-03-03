#include "Channel.hpp"
#include <iostream>

// CONSTRUCTORS AND DESTRUCTORS-------------------------------------------------
Channel::Channel(void)
{
	std::cout << GREEN "Channel default constructor called" NC << std::endl;
}

Channel::Channel(Channel const& other)
{
	std::cout << GREEN "Channel copy constructor called" NC << std::endl;
	*this = other;
}

Channel::~Channel(void)
{
	std::cout << RED "Channel destructor called" NC << std::endl;
}

// OPERATORS--------------------------------------------------------------------
Channel& Channel::operator=(Channel const& other)
{
	if (this == &other) {
		return *this;
	}
	// DO THINGS
	return *this;
}

// METHODS AND MEMBER FUNCTIONS-------------------------------------------------
