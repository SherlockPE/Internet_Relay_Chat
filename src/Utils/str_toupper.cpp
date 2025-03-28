#include <Server.hpp>
#include <cctype>

void str_toupper(std::string &str)
{
	for (size_t i = 0; i < str.length(); i++)
		str[i] = toupper(str[i]);
}