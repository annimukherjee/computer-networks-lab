#include<stdio.h>
#include<stdlib.h>

#include<sys/types.h>
#include<sys/socket.h> 

#include<netinet/in.h>
#include<netinet/ip.h> 

/* superset of previous */


/* Internet address. */
// struct in_addr {
	// uint32_t s_addr;     /* address in network byte order */
// };


// struct sockaddr_in {
    // sa_family_t sin_family; /* address family: AF_INET */
   	// in_port_t sin_port;   /* port in network byte order */
	// struct in_addr sin_addr;   /* internet address */
// };



 
int main()
{
	// AF_INET is the macro for internet protocol

	// SOCK_DGRAM is the macro for the protocol used to pass the packet. Can be either SOCK_DGRAM or SOCK_STREAM....

	// 0 automatically assigns the UDP which is in the Transport layer.


	// ------ creating the socket file descriptor -------------------- 
	int sock_fd = socket(AF_INET, SOCK_DGRAM, 0);	
	if(sock_fd == -1)
	{
		printf("Socket creation FAILED!!!\n------------------\n");
		exit(1);
	}
	else
	{
		printf("Socket has been created successfully\n");
		printf("The socket's file descriptor is: %d\n", sock_fd);
	}
	// socket created --------------------------------------------------



	// creating a bind (to name the socket) ---------------------------------

	struct sockaddr_in s;
	s.sin_family = AF_INET;
	s.sin_port = 5000;
	s.sin_addr.s_addr  = INADDR_ANY;
	
	
	int name_bind = bind(sock_fd, 
						(const struct sockaddr *)&s, 
						sizeof(s));

	if(name_bind==-1)
	{
		printf("The bind was unsuccessful\n");
	}
	else
	{
		printf("The bind was succesful.\n");
		printf("Return value: %d\n", name_bind);
	}
	
	// done with bind ---------------------------------
	
		
		
	return 0;
}
