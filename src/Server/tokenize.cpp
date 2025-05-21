#include <Server.hpp>

t_params	Server::tokenize(std::string params)
{
	t_params			result;
	size_t				pos;

	pos = params.find(' ');
	if (pos == std::string::npos)
		return result;
	result.dest_channel = params.substr(0, pos); // <-- Dest_channel
	pos = params.find(' ');
	if (pos == std::string::npos)
		return result;
	result.client = params.substr(0, pos); // <-- Client
	params.erase(0, pos + 1);
}
