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
#include <vector>
#include <algorithm>
#include <unistd.h>
#include <poll.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

class Client
{
	private:
		pollfd		_poll_data;
		sockaddr	_address;
		std::string	_password;
		std::string	_nick_name;
		std::string	_user_name;
		size_t		_client_id;
		uint32_t	_channel_id;
		uint32_t	_operator;
		bool	_registered;
		// uint32_t	_auth;

	public:
		Client(pollfd poll_data, size_t client_number, sockaddr address);
		~Client(void);
		Client(const Client &);
		Client& operator=(const Client &);

		void close_socket(void);

		size_t getId(void) const;
		std::string getNick(void) const;
		bool getReg(void) const;

		void	setPass(const std::string &);
		void	setNick(const std::string &);
		void	setUser(const std::string &);

		// bool	_register(const std::string &password, const std::vector<std::string> &client_nicks);
		bool	_register(const std::vector<std::string> &);
};

#endif // !_CLIENT_HPP

