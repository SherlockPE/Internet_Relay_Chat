#include "Channel.hpp"
#include "Server.hpp"
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
	_user_limit = other._user_limit;
	_invite_mode = other._invite_mode;
	_topic_mode = other._topic_mode;
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
size_t Channel::getMemberNum(void)
{
	return _members.size();
}
size_t Channel::getUserLimit(void)
{
	return _user_limit;
}
bool Channel::getInviteMode(void)
{
	return _invite_mode;
}
bool Channel::getTopicMode(void)
{
	return _topic_mode;
}
// i: Set/remove Invite-only channel
// t: Set/remove the restrictions of the TOPIC command to channel operators
// k: Set/remove the channel key (password)
// o: Give/take channel operator privilege
// l: Set/remove the user limit to channel
std::string	Channel::getModeString(void)
{
	std::string	result;

	if (_invite_mode)
		result += "i";
	if (_topic_mode)
		result += "t";
	if (!_password.empty())
		result += "k";
	if (_user_limit)
		result += "l " + to_string(_user_limit);
	if (!result.empty())
		result.insert(0,"+");
	return result;
}

void	Channel::setPass(std::string new_password)
{
	_password = new_password;
}
void	Channel::setTopic(std::string new_topic)
{
	_topic = new_topic;
}
void Channel::setUserLimit(size_t new_user_limit)
{
	_user_limit = new_user_limit;
}
void Channel::setInviteMode(bool new_invite_mode)
{
	_invite_mode = new_invite_mode;
}
void Channel::setTopicMode(bool new_topic_mode)
{
	_topic_mode = new_topic_mode;
}

void	Channel::addMember(std::string client_nick)
{
	if (!isMember(client_nick))
		_members.push_back(client_nick);
}
void	Channel::addOperator(std::string client_nick)
{
	if (isMember(client_nick) && !isOperator(client_nick))
		_operators.push_back(client_nick);
}

bool	Channel::erraseMember(std::string client_nick)
{
	bool	result = false;

	std::vector<std::string>::iterator	it;
	it = std::find(_members.begin(), _members.end(), client_nick);
	if (it == _members.end())
		return result;
	_members.erase(it);
	result = true;
	it = std::find(_operators.begin(), _operators.end(), client_nick);
	if (it == _operators.end())
		return result;
	_operators.erase(it);
	return result;
}

bool	Channel::erraseOperator(std::string client_nick)
{
	bool	result = false;

	std::vector<std::string>::iterator	it;
	it = std::find(_operators.begin(), _operators.end(), client_nick);
	if (it == _operators.end())
		return result;
	_operators.erase(it);
	result = true;
	return result;
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