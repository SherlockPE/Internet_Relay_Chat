#include "Channel.hpp"
#include <iostream>

// CONSTRUCTORS AND DESTRUCTORS-------------------------------------------------
Channel::Channel(const std::string &channel_name, const std::string &channel_pass)
: _channel_name(channel_name), _password(channel_pass)
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
	_channel_name = other._channel_name;
	_password = other._password;
	_topic = other._topic;
	_members = other._members;
	_operators = other._operators;
	_invite_type = other._invite_type;
	_user_limit = other._user_limit;
	_channel_type = other._channel_type;
	return *this;
}

// METHODS AND MEMBER FUNCTIONS-------------------------------------------------

std::string	Channel::getName(void)
{
	return _channel_name;
}
std::string	Channel::getPass(void)
{
	return _password;
}
std::string	Channel::getTopic(void)
{
	return _topic;
}

void	Channel::addMember(std::string client_nick)
{
	_members.push_back(client_nick);
}
void	Channel::addOperator(std::string client_nick)
{
	_operators.push_back(client_nick);
}

bool	Channel::erraseMember(std::string client_nick)
{
	std::vector<std::string>::iterator	it;
	it = std::find(_members.begin(), _members.end(), client_nick);
	if (it == _members.end())
		return false;
	_members.erase(it);
	it = std::find(_operators.begin(), _operators.end(), client_nick);
	if (it == _operators.end())
		return false;
	_operators.erase(it);
	return (true);
}

bool	Channel::isMember(std::string client_nick)
{
	std::vector<std::string>::iterator	it;
	it = std::find(_members.begin(), _members.end(), client_nick);
	if (it != _members.end())
		return true;
	return false;
}
bool	Channel::isOperator(std::string client_nick)
{
	std::vector<std::string>::iterator	it;
	it = std::find(_operators.begin(), _operators.end(), client_nick);
	if (it != _operators.end())
		return true;
	return false;
}
bool	Channel::isEmpty(void)
{
	if (_members.empty() && _operators.empty())
		return true;
	return false;
}