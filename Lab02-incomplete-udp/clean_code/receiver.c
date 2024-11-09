#include<stdio.h>
#include<stdlib.h>

#include<sys/types.h>
#include<sys/socket.h> 

#include<netinet/in.h>
#include<netinet/ip.h> 



int main()
{

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

	struct sockaddr_in server_struct;
	server_struct.sin_family = AF_INET;
	server_struct.sin_port = 5000;            // port in n/w byte order
	server_struct.sin_addr.s_addr  = INADDR_ANY;
	
	
	int bind_ret = bind(sock_fd, 
						(const struct sockaddr *)&server_struct, 
						sizeof(server_struct));

	if(bind_ret==-1)
	{
		printf("The bind was unsuccessful\n");
	}
	else
	{
		printf("The bind was succesful.\n");
		printf("Return value: %d\n", bind_ret);
	}
	
	// done with bind ---------------------------------
	
		
		
	return 0;
}
