#pragma once

#ifndef _COLORS
# define _COLORS
# define BLACK   "\033[1;30m"
# define RED     "\033[1;31m"
# define GREEN   "\033[1;32m"
# define YELLOW  "\033[1;33m"
# define BLUE    "\033[1;34m"
# define MAGENTA "\033[1;35m"
# define CYAN    "\033[1;36m"
# define WHITE   "\033[1;37m"
# define NC      "\033[0m"
#endif // !_COLORS

// Server declaration ----------------------------------------------------------

#ifndef _SERVER_HPP
# define _SERVER_HPP

#include <algorithm>
#include <sstream>
#include <vector>
#include <sys/socket.h>
#include <poll.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <Client.hpp>
// #include <Channel.hpp>

#define BUFF_SIZE 4096
#define QUEUE_SIZE 4096

enum
{
	KICK = 1,
	INVITE = 2,
	TOPIC = 3,
	MODE = 4,
};

template<class T> std::string	to_string(const T& value) {
	std::ostringstream oss;
	oss << value;
	return oss.str();
}

template<class T> int	to_int(const T& value) {
	std::stringstream ss;
	int val;
	ss << value;
	ss >> val;
	return val;
}

class Server
{
	private:
		int	_port;
		std::string	_password;

		char	_buff[BUFF_SIZE];

		size_t _clients_number;
		std::vector<struct pollfd> _pollfds;
		std::vector<Client> _clients;
		// std::vector<Channel> _channels;

		// METHODS AND MEMBER FUNCTIONS ----------------------------------------
		void init_server(void);
		void server_listen_loop(void);
		void server_accept(void);
		void server_read(size_t i);

	public:
		// CONSTRUCTOR AND DESTRUCTOR ------------------------------------------
		Server(int port, std::string password);
		~Server(void);


		// EXCEPTION CLASSES ---------------------------------------------------
		class ErrorExcept : public std::exception
		{
			private:
				const char *_msg;
			public:
				ErrorExcept(const char *msg): _msg(msg){};
				virtual const char * what() const throw ()
				{
					return (_msg);
				}
		};
};

#endif // !_SERVER_HPP
