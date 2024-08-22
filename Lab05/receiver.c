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

	if(sock_server_connection_fd == -1) {
		printf("Socket creation failed\n");
		exit(1);
	} else {
		printf("Socket created successfully\n");
	}
	// ------------ socket created ----------------------------

	




	// -----------------------------------------------------------------------------------------------------------
	// creating a bind (need to do this in sever side as usually the port remains constant for the server!)

	// need to populate a struct of name sockaddr_in which is pre-defined as:
	// struct sockaddr_in {
    //            sa_family_t    sin_family; /* address family: AF_INET */
    //            in_port_t      sin_port;   /* port in network byte order */
    //            struct in_addr sin_addr;   /* internet address */
    //        };



	struct sockaddr_in send;
	send.sin_family = AF_INET;
	send.sin_port = htons(7000);     // host byte order to network byte order
	//send.sin_addr.s_addr = inet_addr("10.2.248.220");


	inet_aton("127.0.0.1", &send.sin_addr);

	socklen_t size_of_send_struct = sizeof(send);
	
	int server_bind_fd = bind(sock_server_connection_fd,     
							(const struct sockaddr *)&send, // expects a pointer of type `const struct sockaddr *` of the struct!
							size_of_send_struct
							);
	


	if(server_bind_fd == -1) {
		printf("Bind creation failed\n");
		exit(1);
	} else {
		printf("Bind created successfully\n");

	}
	printf("\n");

	// -----------------------------------------------------------------------------------------
	// calling listenapi, waiting for the connection request
	int listen_fd = listen(sock_server_connection_fd, 5);
	// -------------------------------------------------------------


	// doing accept, to process the `connect()` sent by the client ----------------------------

	struct sockaddr_in accept_conn1;    // this will be populated by the OS!

	socklen_t sizee = sizeof(accept_conn1);

	int connection1_fd = accept(sock_server_connection_fd, 
							(struct sockaddr *)&accept_conn1, 
							&sizee
							);
	
	// ---------------------------------------------------------------------------------------





	

	




	// while(1) {

		//receiving
	char recv_buff[100];
	// struct sockaddr_in recv_struct;/
	socklen_t size = sizeof(recv);


	ssize_t NumberOfBytesReceived = recv(connection1_fd, 
										recv_buff, 
										sizeof(recv_buff), 
										0);


										// (struct sockaddr *)(&recv), 
										// (&size)
										
	
	
	if(NumberOfBytesReceived == -1) {
		printf("API recv failed\n");
		exit(1);
	} else if(NumberOfBytesReceived > 0){
		recv_buff[NumberOfBytesReceived] = '\0';
		printf("Received msg: %s\n", recv_buff);
		// printf("Port number of sender = %d\n", ntohs(accept_conn1.sin_port));
		// printf("IP Address of sender = %s\n", inet_ntoa(accept_conn1.sin_addr));
		
		if(strcasecmp(recv_buff, "bye") == 0) {
			exit(1);
		}
	}



		// //sending
		// char send_buff[100];
		// printf("\nEnter the msg to send : \n");
		// fgets(send_buff, sizeof(send_buff), stdin);
		// printf("\n");
		// size_t len = strlen(send_buff);
        //   send_buff[len-1] = '\0';
		// struct sockaddr_in se;
		// se.sin_family = AF_INET;
		// se.sin_port = htons(5100);
		// //se.sin_addr.s_addr = inet_addr("10.2.248.220");
		// inet_aton("127.0.0.1", &se.sin_addr);
		// int NumberOfBytesSend = sendto(sock_server_connection_fd, send_buff, strlen(send_buff), 0, (const struct sockaddr *)&se, sizeof(se));
		// if(NumberOfBytesSend == -1) {
		// 	printf("Error\n");
		// 	exit(1);
		// } else {
		// 	if(strcasecmp(send_buff, "bye") == 0) {
		// 		exit(1);
		// 	}
		// }
	// }

}
