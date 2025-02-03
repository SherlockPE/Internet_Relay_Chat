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


class Server
{
	private:
		int m_port;
		std::string m_password;

	public:
		// CONSTRUCTORS AND DESTRUCTORS---------------------------------------------
		Server(int port, std::string password);
		// Server(void);
		Server(Server const& other);
		~Server(void);

		// OPERATORS----------------------------------------------------------------
		Server& operator=(Server const& other);

		void initial_parse();
		// METHODS AND MEMBER FUNCTIONS---------------------------------------------

		// class ErrorClass()
		// {

		// }
};

#endif // !_SERVER_HPP

