#include "cstdlib"
#include <Server.hpp>


int main (int argc, char **argv)
{
	try
	{
		Server	main_serv(argc, argv);
	}
	catch (std::exception &e)
	{
		std::cout << RED << "Error\n" << e.what() << NC << std::endl;
	}


	return (EXIT_SUCCESS);
}
