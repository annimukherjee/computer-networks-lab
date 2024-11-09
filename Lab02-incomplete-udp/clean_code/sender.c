// UNSURE WHAT THIS IS. NOT SURE WHY I WROTE THIS CODE.


#include<stdio.h>
#include<stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include<netinet/in.h>
#include<netinet/ip.h> 
#include<arpa/inet.h>



// /* Internet address. */
// struct in_addr {
// 	uint32_t s_addr;     /* address in network byte order */
// };


// struct sockaddr_in {
//     sa_family_t sin_family; /* address family: AF_INET */
//    	in_port_t sin_port;   /* port in network byte order */
// 	struct in_addr sin_addr;   /* internet address */
// };




int main()
{
	struct sockaddr_in sent;
	sent.sin_family = AF_INET;
	sent.sin_addr.s_addr  = INADDR_ANY;
	
	
	int name_bind = bind(sent, (struct sockaddr *)&sent, sizeof(sent));

	if(name_bind==-1)
	{
		printf("The bind was unsuccessful\n");
	}
	else
	{
		printf("The bind was succesful.");
		printf("Return value: %d\n", name_bind);
	}
	

	
	return 0;
}
