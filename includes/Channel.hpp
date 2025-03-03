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

// Channel declaration --------------------------------------------------------

#ifndef _CHANNEL_HPP
# define _CHANNEL_HPP

#include <string>
#include <vector>
#include <unistd.h>
#include <poll.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

class Channel
{
	private:
		std::string	_channel_name;
		std::string	_password;
		std::string	_topic;
		std::vector<uint32_t>	_members;
		std::vector<uint32_t>	_operators;
		uint32_t	_channel_id;
		uint32_t	_invite_type;
		uint32_t	_user_limit;

	public:
		Channel(void);
		Channel(Channel const& other);
		~Channel(void);

  		Channel& operator=(Channel const& other);
};

#endif // !_CHANNEL_HPP

