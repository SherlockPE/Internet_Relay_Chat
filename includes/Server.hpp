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

// Server declaration --------------------------------------------------------

#ifndef _SERVER_HPP
# define _SERVER_HPP

#include <iostream>
#include <sys/socket.h>


enum
{
	KICK = 1,
	INVITE = 2,
	TOPIC = 3,
	MODE = 4,
};

class Server
{
	private:
		int m_port;
		std::string m_password;

		int			_fd_socket;
		sockaddr	_address;
		socklen_t	_socket_len;



	public:
		// CONSTRUCTORS AND DESTRUCTORS---------------------------------------------
		Server(int argc, char **argv);
		// Server(void);
		Server(Server const& other);
		~Server(void);

		// OPERATORS----------------------------------------------------------------
		Server& operator=(Server const& other);

		// METHODS AND MEMBER FUNCTIONS---------------------------------------------
		void initial_parse(int argc, char **argv);
		void init_server(void);

		// EXCEPTION CLASSES -------------------------------------------------------
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

