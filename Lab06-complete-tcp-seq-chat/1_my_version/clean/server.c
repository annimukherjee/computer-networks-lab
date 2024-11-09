#include<stdio.h>
#include<stdlib.h>


#include<netinet/in.h>
#include<netinet/ip.h> 


#include<string.h>
#include<strings.h>


#include<arpa/inet.h>


#include<sys/types.h>          
#include<sys/socket.h>


int main() {


	// Creating a socket ---------------------------------------
	int sock_server_connection_fd = socket(AF_INET, 
											SOCK_STREAM, 
											0);

	if (sock_server_connection_fd == -1)
	{
		printf("Socket creation failed\n");
		exit(1);
	}
	else
	{
		printf("Socket created successfully\n");
	}
	// ------------ socket created ----------------------------





	// Creating a bind ---------------------------------------

	struct sockaddr_in send_msg;
	send_msg.sin_family = AF_INET;
	send_msg.sin_port = htons(7000);     
	inet_aton("127.0.0.1", &send_msg.sin_addr);
	
	int server_bind_fd = bind(sock_server_connection_fd,     
							(const struct sockaddr *)&send_msg, 
							sizeof(send_msg)
							);

	if (server_bind_fd == -1)
	{
		printf("Bind creation failed\n");
		exit(1);
	}
	else
		printf("Bind created successfully\n");
	printf("\n");
	// ------------ bind created ----------------------------



	// -----------------------------------------------------------------------------------------
	// calling listenapi, waiting for the connection request from sender...
	int listen_fd = listen(sock_server_connection_fd, 
							5);
	// -------------------------------------------------------------


	while(1) {


		struct sockaddr_in accept_conn1;    // this will be populated by the OS!

		socklen_t sizee = sizeof(accept_conn1);

		int connecn_fd[5];

		for (int i = 0; i < 2; i++)
		{
			connecn_fd[i] = accept(sock_server_connection_fd, 
								(struct sockaddr *)&accept_conn1, 
								&sizee
								);
		}
		

		for (int i = 0; i < 2; i++)
		{
			// //NEW SENDING CODE!!!!!!!!!!!!!!
			printf("Who do u want to send msg to?\nClient0\t[Enter 0] or Client1\t[Enter 1]?\n");
			int choice;
			scanf("%d", &choice);
			char buff;
			scanf("%c", &buff);

			char send_buff[100];
			printf("\nEnter the msg to send : \n");
			fgets(send_buff, sizeof(send_buff), stdin);
			printf("\n");

			size_t len = strlen(send_buff);
			
			send_buff[len-1] = '\0';

			ssize_t NumberOfBytesSend = send(connecn_fd[choice], 
											send_buff, 
											strlen(send_buff), 
											0);

			if(NumberOfBytesSend == -1) {
				printf("Error\n");
				exit(1);
			} else {
				if(strcasecmp(send_buff, "bye") == 0) {
					exit(1);
				}
			}
		}
	

		



	}

}
