#include "Client.hpp"
#include "Server.hpp"
#include <iostream>

// CONSTRUCTORS AND DESTRUCTORS ------------------------------------------------
Client::Client(pollfd poll_data, sockaddr address)
: _poll_data(poll_data), _address(address)
{
	sockaddr_in *address_data = (sockaddr_in *)&address;
	std::cout << GREEN << "New client:"
		<< "\n-> fd: [" << poll_data.fd
		<< "]\n-> port: [" << ntohs(address_data->sin_port)
		<< "]\n-> ip: [" << inet_ntoa(address_data->sin_addr)
		<< "]\n" << NC;
	
	_registered = false;
}

Client::~Client(void) {}

Client::Client(const Client &other)
{
	*this = other;
}

// OPERATORS -------------------------------------------------------------------
Client& Client::operator=(const Client &other)
{
	if (this == &other) {
		return *this;
	}
	_poll_data = other._poll_data;
	_address = other._address;
	_nick_name = other._nick_name;
	_user_name = other._user_name;
	_registered = other._registered;
	return *this;
}

// METHODS AND MEMBER FUNCTIONS ------------------------------------------------

void	Client::fillBuff(const std::string &append)
{
	_buffer += append;
}
void	Client::clearBuff(void)
{
	_buffer.erase();
}
std::string	Client::readBuff(void)
{
	return _buffer;
}

void Client::close_socket(void)
{
	close(_poll_data.fd);
	std::cout << YELLOW << "Client [" << _nick_name << "]: "
		<< "Disconected" << NC << "\n";
}

std::string	Client::getUser(void) const
{
	return _user_name;
}
std::string	Client::getNick(void) const
{
	return _nick_name;
}
bool Client::getReg(void) const
{
	return _registered;
}

bool Client::isInvited(std::string channel_name)
{
	if (std::find(_invites.begin(), _invites.end(), channel_name) != _invites.end())
		return true;
	return false;
}
void Client::addInvite(std::string channel_name)
{
	if (isInvited(channel_name))
		return;
	_invites.push_back(channel_name);
	return;
}
void Client::removeInvite(std::string channel_name)
{
	std::vector<std::string>::iterator	it;

	it = std::find(_invites.begin(), _invites.end(), channel_name);
	if (it != _invites.end())
		_invites.erase(it);
	return;
}

void	Client::setPass(const std::string &new_pass)
{
	_password = new_pass;
}
void	Client::setNick(const std::string &new_nick)
{
	_nick_name = new_nick;
}
void	Client::setUser(const std::string &new_user)
{
	_user_name = new_user;
}
void	Client::setRealName(const std::string &realname)
{
	_real_name = realname;
}

void	Client::sendToClient(const std::string &com, size_t code_num)
{
	std::string msg;

	msg = ":42.irc " + to_string(code_num) + " " + _nick_name + " " + com + "\r\n";
	send(this->_poll_data.fd, msg.c_str(), msg.size(), 0);
}

bool	Client::_register(const std::vector<std::string> &client_nicks)
{
	std::string	msg;

	if (this->getReg())
		return (false);
	if (_user_name.empty() || _nick_name.empty() || _password.empty())
		return false;
	if (std::find(client_nicks.begin(), client_nicks.end(), _nick_name) != client_nicks.end())
	{
		std::cout << RED << "sending to:" << _nick_name << " ERR_NICKNAMEINUSE (433)" << NC << "\n";
		msg = ":42.irc 433" + _nick_name + " " + _nick_name + " :Nickname is already in use\r\n";
		send(_poll_data.fd, msg.c_str(), msg.size(), 0);
		return false;
	}
	std::cout << YELLOW << "Client [" << _nick_name << "]: "
		<< "Registered" << NC << "\n";
	_registered = true;
	return true;
}
// bool	Client::_register(const std::string &password, const std::vector<std::string> &clients_nicks)
// {
// 	if (password != _password)
// 	{
// 		// ERR_PASSWDMISMATCH (464)
// 		return false;
// 	}
// 	_registered = true;
// 	return true;
// }