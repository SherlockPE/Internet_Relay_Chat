#include "Client.hpp"
#include <iostream>

// CONSTRUCTOR AND DESTRUCTOR --------------------------------------------------
Client::Client(struct pollfd &poll_data, size_t client_number, sockaddr address): _poll_data(&poll_data)
{
	_client_id = client_number - 1;
	_address = address;
	
	sockaddr_in *address_data = (sockaddr_in *)&address;
	std::cout << GREEN << "New client:"
		<< "\n-> id: " << _client_id
		<< "\n-> fd: " << poll_data.fd
		<< "\n-> ip: " << inet_ntoa(address_data->sin_addr)
		<< "\n-> port: " << ntohs(address_data->sin_port)
		<< NC << "\n";
}

Client::~Client(void)
{
}


// METHODS AND MEMBER FUNCTIONS ------------------------------------------------
