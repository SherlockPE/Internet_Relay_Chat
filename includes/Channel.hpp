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


// Channel declaration --------------------------------------------------------

#ifndef _CHANNEL_HPP
# define _CHANNEL_HPP
# define DEFAULT_TOPIC "default_topic"
#include <string>
#include <vector>
#include <algorithm>
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
		std::vector<std::string>	_members;
		std::vector<std::string>	_operators;
		size_t	_user_limit;
		bool	_invite_mode;
		bool	_topic_mode;

	public:
		Channel(const std::string &channel_name, const std::string &channel_pass);
		Channel(const Channel & other);
		~Channel(void);

  		Channel& operator=(const Channel & other);


		std::string getName(void);
		std::string getPass(void);
		std::string getTopic(void);
		size_t getMemberNum(void);
		size_t getUserLimit(void);
		bool getInviteMode(void);
		bool getTopicMode(void);
		std::string	getModeString(void);
		
		void setPass(std::string);
		void setTopic(std::string);
		void setUserLimit(size_t);
		void setInviteMode(bool);
		void setTopicMode(bool);
		
		void addMember(std::string client_nick);
		void addOperator(std::string client_nick);
		
		bool erraseMember(std::string client_nick);
		bool erraseOperator(std::string client_nick);

		bool isMember(std::string client_nick);
		bool isOperator(std::string client_nick);
		bool isEmpty(void);
};

#endif // !_CHANNEL_HPP

