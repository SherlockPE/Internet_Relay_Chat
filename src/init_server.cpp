#include <Server.hpp>
#include <sys/socket.h>


// To accept connections, the following steps are performed:

void	Server::init_server(void)
{
	int			fd_socket;
	sockaddr	address;

//    (1)  A socket is created with socket().
	fd_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (fd_socket == -1)
		throw ("Error trying to display the socket (system error)");

//    (2)  The socket is bound to a local address using bind(), so
//         that other sockets may be connected to it.
	if (bind(fd_socket, &address, sizeof(sockaddr)) == -1)
		throw ("Error trying to bind the socket (system error)");

//    (3)  A willingness to accept incoming connections and a queue
//         limit for incoming connections are specified with
//         listen().
	if (listen(fd_socket, 4000) == -1)
		throw ("Error trying to listen for socket (system error)");


//    (4)  Connections are accepted with accept(2).

}