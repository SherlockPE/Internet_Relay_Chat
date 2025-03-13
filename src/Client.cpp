#include "Client.hpp"
#include <iostream>

// CONSTRUCTORS AND DESTRUCTORS ------------------------------------------------
Client::Client(pollfd poll_data, size_t client_number, sockaddr address)
: _poll_data(poll_data), _address(address), _client_id(client_number)
{
	sockaddr_in *address_data = (sockaddr_in *)&address;
	std::cout << GREEN << "New client:"
		<< "\n-> id: [" << _client_id
		<< "]\n-> fd: [" << poll_data.fd
		<< "]\n-> port: [" << ntohs(address_data->sin_port)
		<< "]\n-> ip: [" << inet_ntoa(address_data->sin_addr)
		<< "]\n" << NC;
}

Client::~Client(void) {}

Client::Client(const Client &other)
{
	*this = other;
}

// OPERATORS -------------------------------------------------------------------
Client& Client::operator=(const Client &other)
{
	_poll_data = other._poll_data;
	_address = other._address;
	_nick_name = other._nick_name;
	_user_name = other._user_name;
	_client_id = other._client_id;
	_auth = other._auth;
	_channel_id = other._channel_id;
	_operator = other._operator;

	return *this;
}

// METHODS AND MEMBER FUNCTIONS ------------------------------------------------

void Client::close_socket(void)
{
	close(_poll_data.fd);
	std::cout << YELLOW << "Client [" << _client_id << "]: "
		<< "Disconected" << NC << "\n";
}

size_t Client::getId(void) const
{
	return _client_id;
}