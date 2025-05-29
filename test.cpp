#include <iostream>
#include <cstring>
#include <sstream>

int main(int argc, char const *argv[])
{
    (void)argc;
    (void)argv;
    std::string channel_name, client_target, reason;
    std::string params = "42_irc unexistenuser :This is a test reason";
    std::istringstream iss(params);

    iss >> channel_name >> client_target;
    if (iss.fail())
    {
        std::cout << "Not enough parameters provided." << std::endl;
        return 1;
    }
    
    std::cout << "Original params: " << params << std::endl;
    
    std::cout << "Channel name: " << channel_name << std::endl;
    std::cout << "Client target: " << client_target << std::endl;
    std::getline(iss, reason);
    if (reason.empty())
        reason = "No reason specified";
    std::cout << "Reason: " << reason << std::endl;

    return 0;
}
