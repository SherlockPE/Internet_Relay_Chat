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

// Client declaration --------------------------------------------------------

#ifndef _CLIENT_HPP
# define _CLIENT_HPP

#include <string>
#include <unistd.h>
#include <poll.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

class Client
{
	private:
		struct pollfd	*_poll_data;
		sockaddr	_address;
		std::string	_nick_name;
		std::string	_user_name;
		size_t	_client_id;
		uint32_t	_auth;
		uint32_t	_channel_id;
		uint32_t	_operator;

	public:
		Client(struct pollfd &poll_data, size_t client_number, sockaddr address);
		~Client(void);
};

#endif // !_CLIENT_HPP

