#pragma once

#ifndef _COLORS
# define _COLORS
# define BLACK    "\033[1;30m"
# define RED      "\033[1;31m"
# define GREEN    "\033[1;32m"
# define YELLOW   "\033[1;33m"
# define BLUE     "\033[1;34m"
# define MAGENTA  "\033[1;35m"
# define CYAN     "\033[1;36m"
# define WHITE    "\033[1;37m"
# define BOLD	  "\033[1m"
# define BOLD_OFF "\033[22m"
# define ITALIC   "\033[3m"
# define NC       "\033[0m"
#endif // !_COLORS


// Server declaration ----------------------------------------------------------

#ifndef _SERVER_HPP
# define _SERVER_HPP

#include <string>
#include <iostream>
#include <ctime>
#include <sstream>
#include <algorithm>
#include <vector>
#include <map>
#include <sys/socket.h>
#include <poll.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <Client.hpp>
#include <Channel.hpp>

#define BUFF_SIZE 4096
#define QUEUE_SIZE 4096
#define HOSTNAME "42.irc"

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

typedef struct s_params
{
	std::string	dest_channel;
	std::string	client;
	std::string	client_target;
	std::string	other_params;
} t_params;


class Server;

typedef void (Server::*com_fn) (std::string command, std::string params, size_t client_i);

class Server
{
	private:
		int			_port;
		sockaddr_in	_address;
		time_t		_init_timer;
		struct tm	*_init_time;
		std::string	_time_str;
		std::string	_password;
		size_t		_clients_to_auth;
		char		_buff[BUFF_SIZE];

		std::vector<struct pollfd> _pollfds;
		std::map<std::string, Client> _clients;
		std::vector<Client> _clqwertyients;
		std::vector<std::string> _client_nicks;
		std::vector<Channel> _channels;

		std::map<std::string, com_fn>	_coms;

		// METHODS AND MEMBER FUNCTIONS ----------------------------------------
		void		init_server(void);
		void		server_listen_loop(void);
		void		server_accept(void);
		void		server_read(size_t poll_i);
		void		init_commands(void);
		void		select_command(std::string command, size_t client_i);
		void		parse_message(std::string msg, size_t client_i);
		void		register_clients(void);
		t_params	tokenize(std::string params);

		// Connection messages
		void	_PASS(std::string, std::string, size_t);
		void	_NICK(std::string, std::string, size_t);
		void	_USER(std::string, std::string, size_t);
		// void	_PING(std::string, std::string, size_t);
		// void	_PONG(std::string, std::string, size_t);
		void	_OPER(std::string, std::string, size_t);
		// void	_QUIT(std::string, std::string, size_t);
		// void	_ERROR(std::string, std::string, size_t);

		// Channel operations
		void	_JOIN(std::string, std::string, size_t);
		// void	_PART(std::string, std::string, size_t);
		void	_KICK(std::string, std::string, size_t);
		void	_INVITE(std::string, std::string, size_t);
		void	_TOPIC(std::string, std::string, size_t);
		void	_MODE(std::string, std::string, size_t);

		// Messages
		void	_PRIVMSG(std::string, std::string, size_t);
		// void	_NOTICE(std::string, std::string, size_t);

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


// UTILS
void str_toupper(std::string &str);

#endif // !_SERVER_HPP
