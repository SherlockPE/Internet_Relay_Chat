#include "cstdlib"
#include <Server.hpp>


int main (int argc, char **argv)
{
	try
	{
		Server	main_serv(argc, argv);
		main_serv.init_server();
	}
	catch (std::exception &e)
	{
		std::cerr << RED << "Error\n" << e.what() << NC << std::endl;
	}


	return (EXIT_SUCCESS);
}
